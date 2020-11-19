#ifndef BUTTONTILE_H
#define BUTTONTILE_H

#include "../../Models/UI/Button.h"
#include "Entities/Env_Item.h"

struct ButtonTile
{
    Button button;
    bool exist;
    Vector2<int> cell;
    ButtonTile(Vector2<int> cell)
    {
        this->cell = cell;
        this->exist = false;
    }

    ButtonTile(Button &button, Vector2<int> cell)
    {
        this->button = button;
        this->cell = cell;
        this->exist = true;
    }
};

#endif