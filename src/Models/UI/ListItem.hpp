#ifndef LISTITEM_H
#define LISTITEM_H

#include <functional>

#include "Panel.hpp"

class ListItemElement : public Button
{
public:
    ListItemElement(Button *btn);
    ~ListItemElement();

    void Update() override;

    bool selected = false;

protected:
    void onMouseDown() override;
    void onMouseUp() override;
};

class ListItem : public UIObject
{
public:
    ListItem(Panel *panel);
    ListItem();
    ~ListItem();

    void AddItem(std::string &text);
    void Clear();

    void AddListener(std::function<void(Button *, Button *)> func);

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) override;
    void ProcessInput() override;
    void Update() override;

    int getSelectedIndex();

private:
    Panel *panel = nullptr;
    std::vector<ListItemElement *> items;
    int selectedIndex = -1;

    int i = 0;

    std::vector<std::function<void(Button *, Button *)>> listeners;
};

#endif // LISTITEM_H