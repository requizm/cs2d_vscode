#ifndef BUTTONTILE_H
#define BUTTONTILE_H

#include "../../Models/UI/Button.h"
#include "Entities/Env_Item.h"

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
};

#endif