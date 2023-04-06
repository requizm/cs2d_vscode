#ifndef BUTTONTILE_H
#define BUTTONTILE_H

#include "../../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../Model/TileButton.hpp"
#include "Entities/Env_Item.hpp"


class ButtonTile
{
   public:
    TileButtonWorld button;
    Vector2<int> cell;
    std::shared_ptr<Env_Item> item = nullptr;
    bool init = false;

    ButtonTile() = default;

    explicit ButtonTile(const Vector2<int> &cell)
    {
        this->cell = cell;
    }

    ButtonTile(TileButtonWorld &button, const Vector2<int> &cell)
    {
        this->cell = cell;
        this->button = button;
    }

    ButtonTile(int item_id, TileButtonWorld &button, const Vector2<int> &cell)
    {
        this->item = std::make_shared<Env_Item>(item_id, button.getPosition());
        this->item->Initialize();
        this->cell = cell;
        this->button = button;
    }

    ~ButtonTile() = default;

    void SetButton(TileButtonWorld &bt)
    {
        this->button = bt;
    }

    void SetItem(std::shared_ptr<Env_Item> item)
    {
        this->item = item;
    }
};


#endif