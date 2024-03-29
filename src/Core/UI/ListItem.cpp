#include "ListItem.hpp"

#include "../Manager/InputManager.hpp"
#include "../Manager/Logger.hpp"
#include "../Manager/MemoryOverride/MemoryOverride.hpp"


ListItem::ListItem(std::shared_ptr<Panel> panel)
    : UIObject(panel->getPosition(), panel->getScale(), *(panel->rend))
{
    this->panel = panel;
}

ListItem::ListItem() : UIObject()
{
    this->position = Vector2<int>(0);
    this->scale = 0.0F;
}

ListItem::~ListItem()
{
    this->Clear();
}

void ListItem::AddItem(const std::string &text)
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    const Vector2<int> pos = Vector2<int>(0, static_cast<int>(i * 20));
    const Vector2<int> size = Vector2<int>(panel->getSize().x, 20);
    auto bt =
        std::make_shared<TextButton>(text, pos,
                                     size, *(panel->rend),
                                     Vector3<float>(0.21F), Vector3<float>(0.58F), 1.0F, true,
                                     UIObjectType::LISTITEM);
    bt->setButtonClickColor(Vector3<float>(0.35F));
    bt->setButtonHoverColor(Vector3<float>(0.25F));
    bt->setTextHoverColor(Vector3<float>(1.0F));
    bt->setTextClickColor(Vector3<float>(1.0F));
    bt->setHaveOutline(false);
    bt->setParent(panel, true);
    bt->independent = true;
    bt->setDrawCenter(false);

    items.push_back(std::make_shared<ListItemElement>(std::move(bt), i++, std::move(shared_from_this())));
}

void ListItem::Clear()
{
    for (auto &item : items)
    {
        item.reset();
    }
    items.clear();
    removeParent();
    i = 0;
}

void ListItem::AddListener(std::function<void(TextButton *, TextButton *)> func)
{
    listeners.push_back(std::move(func));
}

void ListItem::Draw(SquareRenderer &squareRenderer)
{
    if (panel->isEnable())
    {
        for (auto &item : items)
        {
            item->bt->Draw(squareRenderer);
        }
    }
}

void ListItem::Update()
{
    if (panel->isMouseEvents() && panel->isEnable())
    {
        for (std::vector<int>::size_type i = 0; i != items.size(); i++)
        {
            items[i]->bt->Update();
        }
        if (InputManager::scrollYPressed && panel->isScrollable())
        {
            if (!items.empty())
            {
                bool check_1 = items.at(0)->bt->getLocalPosition().y == 0 &&
                               InputManager::scroll.y > 0;
                bool check_2 =
                    items.at(items.size() - 1)->bt->getLocalPosition().y + 20.0F <=
                        panel->getSize().y &&
                    InputManager::scroll.y < 0;

                if (!check_1 && !check_2)
                {
                    for (auto &tile : items)
                    {
                        tile->bt->setLocalPosition(Vector2<int>(tile->bt->getLocalPosition().x, tile->bt->getLocalPosition().y + InputManager::scroll.y * 20));
                    }
                }
            }
            InputManager::scrollYPressed = false;
        }
    }
}

void ListItem::Select(int i)
{
    ASSERTM_ERROR(i >= 0 && i < items.size(), "boyle bir item indexi yok");

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
            f(items[old]->bt.get(), items[selectedIndex]->bt.get());
        }
        else
        {
            f(nullptr, items[selectedIndex]->bt.get());
        }
    }
}

int ListItem::getSelectedIndex() { return selectedIndex; }

ListItemElement *ListItem::getIndex(int i)
{
    ASSERTM_ERROR(i >= 0 && i < items.size(), "boyle bir item indexi yok");
    return items.at(i).get();
}

ListItemElement::ListItemElement(std::shared_ptr<TextButton> btn, int i, std::shared_ptr<UIObject> listItem) : UIObject(UIObjectType::LISTITEMELEMENT)
{
    bt = btn;
    btn->addListenerDown(std::bind(&ListItemElement::MouseDown, this));
    this->listItem = listItem;
    index = i;
}

ListItemElement::~ListItemElement()
{
    removeParent();
}

void ListItemElement::MouseDown()
{
    if (isEnable() && isMouseEvents())
    {
        if (!selected && isRenderable())
        {
            ListItem *listItem = reinterpret_cast<ListItem *>(this->listItem.lock().get());
            listItem->Select(index);
        }
    }
}
