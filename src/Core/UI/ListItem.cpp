#include "ListItem.hpp"

ListItem::ListItem(Panel *panel)
    : UIObject(panel->GetPosition(), panel->GetSize(), panel->GetScale(), *(panel->rend))
{
    this->panel = panel;
}

ListItem::ListItem() : UIObject()
{
}

ListItem::~ListItem()
{
    for (auto &item : items)
    {
        if (item != nullptr) delete item;
    }
    RemoveParent();
}

void ListItem::AddItem(const std::string &text)
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    const Vector2<int> pos = Vector2<int>(panel->GetPosition().x, panel->GetPosition().y + static_cast<int>(i * 20));
    const Vector2<int> size = Vector2<int>(panel->GetSize().x, 20);
    TextButton *bt =
        new TextButton(text, pos,
                       size, *(panel->rend), panel,
                       Vector3<float>(0.21F), Vector3<float>(0.58F), 1.0F,
                       UIObjectType::LISTITEM);
    bt->setButtonClickColor(Vector3<float>(0.35F));
    bt->setButtonHoverColor(Vector3<float>(0.25F));
    bt->setTextHoverColor(Vector3<float>(1.0F));
    bt->setTextClickColor(Vector3<float>(1.0F));
    bt->setHaveOutline(false);
    bt->independent = true;
    bt->setTextAlign(TextAlign::T_LEFT);

    items.push_back(new ListItemElement(bt, i++, this));
}

void ListItem::Clear()
{
    for (auto &item : items)
    {
        if (item != nullptr) delete item;
    }
    
    items.clear();
    i = 0;
}

void ListItem::AddListener(std::function<void(TextButton *, TextButton *)> func)
{
    listeners.push_back(std::move(func));
}

void ListItem::Draw(SquareRenderer &squareRenderer)
{
    if (panel->IsEnable())
    {
        for (auto &item : items)
        {
            item->bt->Draw(squareRenderer);
        }
    }
}

void ListItem::Update()
{
    if (panel->IsMouseEvents() && panel->IsEnable())
    {
        for (std::vector<int>::size_type i = 0; i != items.size(); i++)
        {
            items[i]->bt->Update();
        }
        if (InputManager::scrollYPressed && panel->IsScrollable())
        {
            if (!items.empty())
            {
                bool check_1 = items.at(0)->bt->GetLocalPosition().y == 0 &&
                               InputManager::scroll.y > 0;
                bool check_2 =
                    items.at(items.size() - 1)->bt->GetLocalPosition().y + 20.0F <=
                        panel->GetSize().y &&
                    InputManager::scroll.y < 0;

                if (!check_1 && !check_2)
                {
                    for (auto &tile : items)
                    {
                        tile->bt->SetPosition(Vector2<int>(tile->bt->GetLocalPosition().x,
                                                           tile->bt->GetLocalPosition().y +
                                                               InputManager::scroll.y * 20));
                    }
                }
            }
            InputManager::scrollYPressed = false;
        }
    }
}

void ListItem::Select(int i)
{
    if (i < 0 || i > items.size())
    {
        WRITE_ERROR("Boyle bir list item indexi yok" + i);
        exit(EXIT_FAILURE);
    }
    int old = selectedIndex;
    if (selectedIndex != -1)
    {
        items[selectedIndex]->bt->setButtonColor(Vector3<float>(0.21F));
        items[selectedIndex]->bt->setButtonHoverColor(Vector3<float>(0.25F));
        items[selectedIndex]->bt->setTextColor(Vector3<float>(0.58F));
        items[selectedIndex]->selected = false;
    }
    items[i]->bt->setButtonColor(Vector3<float>(0.35F));
    items[i]->bt->setButtonHoverColor(Vector3<float>(0.35F));
    items[i]->bt->setTextColor(Vector3<float>(1.0F));
    items[i]->selected = true;
    selectedIndex = i;

    for (auto &f : listeners)
    {
        if (old != -1)
        {
            f(items[old]->bt, items[selectedIndex]->bt);
        }
        else
        {
            f(nullptr, items[selectedIndex]->bt);
        }
    }
}

int ListItem::getSelectedIndex() { return selectedIndex; }

ListItemElement *ListItem::getIndex(int i)
{
    if (i < 0 || i > items.size())
    {
        WRITE_ERROR("Boyle bir list item indexi yok" + i);
        exit(EXIT_FAILURE);
    }
    return items.at(i);
}

ListItemElement::ListItemElement(TextButton *btn, int i, ListItem *listItem) : UIObject(UIObjectType::LISTITEMELEMENT)
{
    bt = btn;
    btn->addListenerDown(std::bind(&ListItemElement::MouseDown, this));
    this->listItem = listItem;
    index = i;
}

ListItemElement::ListItemElement(TextButton *btn, int i, ListItem *listItem, Object *par) : UIObject(UIObjectType::LISTITEMELEMENT, par)
{
    bt = btn;
    btn->addListenerDown(std::bind(&ListItemElement::MouseDown, this));
    this->listItem = listItem;
    index = i;
}

ListItemElement::~ListItemElement()
{
    delete bt;
    RemoveParent();
}

void ListItemElement::MouseDown()
{
    if (IsEnable() && IsMouseEvents())
    {
        if (!selected && IsRenderable())
        {
            listItem->Select(index);
        }
    }
}
