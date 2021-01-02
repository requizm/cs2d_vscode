#ifndef BUTTONTILE_H
#define BUTTONTILE_H

#include "../../Models/UI/Button.hpp"
#include "Entities/Env_Item.hpp"
#include "../../Others/Utils.hpp"

struct ButtonTile
{
    Button button;
    Vector2<int> cell;
    std::shared_ptr<Env_Item> item;

    ButtonTile(Vector2<int> cell)
    {
        this->cell = cell;
        item = std::make_shared<Env_Item>(0, Utils::CellToPosition(cell));
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
        item = std::make_shared<Env_Item>(item_id, button.getPosition());
    }
};

#endif