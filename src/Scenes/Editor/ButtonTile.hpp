#ifndef BUTTONTILE_H
#define BUTTONTILE_H

#include "../../Models/UI/Button.hpp"
#include "Entities/Env_Item.hpp"

struct ButtonTile
{
    Button button;
    Vector2<int> cell;
    Env_Item item;
    ButtonTile(Vector2<int> cell)
    {
        this->cell = cell;
    }

    ButtonTile(Button &button, Vector2<int> cell)
    {
        this->button = button;
        this->cell = cell;
    }

    ButtonTile(int item_id, Button &button, Vector2<int> cell)
    {
        this->button = button;
        this->cell = cell;
        item = Env_Item(item_id, button.getPosition());
    }
};

#endif