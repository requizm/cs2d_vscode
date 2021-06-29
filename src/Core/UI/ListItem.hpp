#ifndef LISTITEM_H
#define LISTITEM_H

#include <functional>

#include "../Manager/MemoryOverride/MemoryOverride.hpp"
#include "Panel.hpp"
#include "TextButton.hpp"

class ListItem;


class ListItemElement : public UIObject
{
   public:
    explicit ListItemElement(TextButton *btn, int i, ListItem *listItem);
    ~ListItemElement() final;

    bool selected = false;
    TextButton *bt = nullptr;

   private:
    ListItem *listItem = nullptr;


    int index = -1;

    void MouseDown();
};

class ListItem : public UIObject
{
   public:
    ListItem(Panel *panel);
    ListItem();
    ~ListItem() final;

    void AddItem(const std::string &text);
    void Clear();

    void AddListener(std::function<void(TextButton *, TextButton *)> func);

    void Draw(SquareRenderer &squareRenderer) final;
    void Update() final;
    void Select(int i);

    int getSelectedIndex();
    ListItemElement *getIndex(int i);

   private:
    Panel *panel = nullptr;
    std::vector<ListItemElement *> items;
    int selectedIndex = -1;

    int i = 0;

    std::vector<std::function<void(TextButton *, TextButton *)>> listeners;
};

#endif  // LISTITEM_H