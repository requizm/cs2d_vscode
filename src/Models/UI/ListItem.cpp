#include "ListItem.hpp"
#include "../../Scenes/Editor/Editor.hpp"

ListItem::ListItem(Panel *panel) : UIObject(panel->getPosition(), panel->getScale(), *(panel->rend))
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
    for (auto &item : items)
    {
        delete item;
    }
    UIObject::removeParent();;
}

void ListItem::AddItem(std::string &text)
{
    Button *bt = new Button(text, Vector2<int>(0.0F, static_cast<int>(i++ * 20)), Vector2<int>(panel->getSize().x, 20.0F), *(panel->rend), Vector3<float>(0.21F), Vector3<float>(0.58F), 1.0F, UIObjectType::LISTITEM);
    bt->setMouseClickColor(Vector3<float>(0.35F));
    bt->setMouseHoverColor(Vector3<float>(0.25F));
    bt->setLabelMouseHoverColor(Vector3<float>(1.0F));
    bt->setLabelClickColor(Vector3<float>(1.0F));
    bt->setOutline(false);
    bt->setParent(panel, true);
    bt->independent = true;
    bt->center = false;
    items.push_back(bt);
}

void ListItem::Clear()
{
    items.clear();
    i = 0;
}

void ListItem::AddListener(std::function<void(Button *, Button *)> func)
{
    listeners.push_back(std::move(func));
}

void ListItem::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (panel->isEnable())
    {
        for (auto &item : items)
        {
            item->Draw(spriteRenderer, squareRenderer);
        }
    }
}

void ListItem::ProcessInput()
{
    if (panel->isMouseEvents() && panel->isEnable())
    {
        for (std::vector<int>::size_type i = 0; i != items.size(); i++)
        {
            items[i]->ProcessInput();
            if (items[i]->isMouseDown() && items[i]->isRenderable() && i != selectedIndex)
            {
                int old = selectedIndex;
                if (selectedIndex != -1)
                {
                    items[selectedIndex]->setButtonColor(Vector3<float>(0.21F));
                    items[selectedIndex]->setMouseHoverColor(Vector3<float>(0.25F));
                    items[selectedIndex]->setLabelColor(Vector3<float>(0.58F));
                }
                items[i]->setButtonColor(Vector3<float>(0.35F));
                items[i]->setMouseHoverColor(Vector3<float>(0.35F));
                items[i]->setLabelColor(Vector3<float>(1.0F));
                selectedIndex = i;

                for (auto &f : listeners)
                {
                    try
                    {
                        f(items[old], items[selectedIndex]);
                    }
                    catch (const std::exception &e)
                    {
                        f(nullptr, items[selectedIndex]);
                    }
                }
                break;
            }
        }
    }
}

void ListItem::Update()
{
    if (panel->isMouseEvents() && panel->isEnable())
    {
        for (std::vector<int>::size_type i = 0; i != items.size(); i++)
        {
            items[i]->Update();
        }
        if (InputManager::scrollYPressed && panel->isScrollable())
        {
            if (!items.empty())
            {
                bool check_1 = items.at(0)->getLocalPosition().y == 0 && InputManager::scroll.y > 0;
                bool check_2 = items.at(items.size() - 1)->getLocalPosition().y + 20.0F <= panel->getSize().y && InputManager::scroll.y < 0;

                if (!check_1 && !check_2)
                {
                    for (auto &tile : items)
                    {
                        tile->setPosition(tile->getLocalPosition().x, tile->getLocalPosition().y + InputManager::scroll.y * 20);
                    }
                }
            }
            InputManager::scrollYPressed = false;
        }
    }
}

int ListItem::getSelectedIndex()
{
    return selectedIndex;
}
