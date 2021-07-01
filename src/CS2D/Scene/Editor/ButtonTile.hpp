#ifndef BUTTONTILE_H
#define BUTTONTILE_H

#include "../../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../Model/TileButton.hpp"
#include "Entities/Env_Item.hpp"


class ButtonTile
{
   public:
    TileButtonWorld *button = nullptr;
    Vector2<int> cell;
    Env_Item *item = nullptr;
    bool init = false;

    ButtonTile() = default;

    explicit ButtonTile(Vector2<int> cell)
    {
        this->cell = cell;
        this->button = new TileButtonWorld();
    }

    ButtonTile(TileButtonWorld *button, Vector2<int> cell)
    {
        this->cell = cell;
        this->button = button;
    }

    ButtonTile(int item_id, TileButtonWorld *button, Vector2<int> cell)
    {
        this->item = new Env_Item(item_id, button->getPosition());
        this->cell = cell;
        this->button = button;
    }

    ~ButtonTile() { delete button; }

    void SetButton(TileButtonWorld *bt)
    {
        if (this->button != nullptr)
        {
            delete this->button;
        }
        this->button = bt;
    }

    void SetItem(Env_Item *item)
    {
        if (this->item != nullptr)
        {
            delete this->item;
        }
        this->item = item;
    }
};


#endif