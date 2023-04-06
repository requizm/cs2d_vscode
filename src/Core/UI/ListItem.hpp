#ifndef LISTITEM_H
#define LISTITEM_H

#include <functional>

#include "Panel.hpp"
#include "TextButton.hpp"

class ListItem;

class ListItemElement : public UIObject
{
   public:
    explicit ListItemElement(std::shared_ptr<TextButton> btn, int i, std::shared_ptr<UIObject> listItem);
    ~ListItemElement() final;

    bool selected = false;
    std::shared_ptr<TextButton> bt = nullptr;

   private:
    std::weak_ptr<UIObject> listItem;


    int index = -1;

    void MouseDown();
};

class ListItem : public UIObject
{
   public:
    explicit ListItem(std::shared_ptr<Panel> panel);
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
    std::shared_ptr<Panel> panel;
    std::vector<std::shared_ptr<ListItemElement>> items;
    int selectedIndex = -1;

    int i = 0;

    std::vector<std::function<void(TextButton *, TextButton *)>> listeners;
};

#endif  // LISTITEM_H