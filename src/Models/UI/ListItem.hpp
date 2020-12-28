#ifndef LISTITEM_H
#define LISTITEM_H

#include "Panel.hpp"

#include <functional>

class ListItem : UIObject
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

private:
    Panel *panel;
    std::vector<Button *> items;
    int selectedIndex = -1;

    int i = 0;

    std::vector<std::function<void(Button *, Button *)>> listeners;
};

#endif // !LISTITEM_H