#ifndef BUTTONTILE_H
#define BUTTONTILE_H

#include "../../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../../Core/Manager/Utils.hpp"
#include "../../Model/TileButton.hpp"
#include "Entities/Env_Item.hpp"


class ButtonTile
{
   public:
    TileButtonWorld *tileButton = nullptr;
    Env_Item *item = nullptr;

    ButtonTile()
    {
        tileButton = new TileButtonWorld();
    }

    ButtonTile(TileButtonWorld *button)
    {
        this->tileButton = button;
    }

    ButtonTile(int item_id, TileButtonWorld *button)
    {
        this->item = new Env_Item(item_id, button->GetPosition());
        this->tileButton = button;
    }

    ~ButtonTile() { delete tileButton; }

    void SetButton(TileButtonWorld *bt)
    {
        if (this->tileButton != nullptr)
        {
            delete this->tileButton;
        }
        this->tileButton = bt;
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