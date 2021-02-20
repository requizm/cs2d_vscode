#ifndef BUTTONTILE_H
#define BUTTONTILE_H

#include "../../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../../Core/Manager/Utils.hpp"
#include "../../../Core/UI/Button.hpp"
#include "Entities/Env_Item.hpp"


class ButtonTile {
   public:
    Button *button = nullptr;
    Vector2<int> cell;
    Env_Item *item = nullptr;
    bool init = false;

    ButtonTile() = default;

    ButtonTile(Vector2<int> cell) {
        this->cell = cell;
        this->button = new Button();
    }

    ButtonTile(Button *button, Vector2<int> cell) {
        this->cell = cell;
        this->button = button;
    }

    ButtonTile(int item_id, Button *button, Vector2<int> cell) {
        this->item = new Env_Item(item_id, button->getPosition());
        this->cell = cell;
        this->button = button;
    }

    ~ButtonTile() { delete button; }

    void SetButton(Button *bt) {
        if (this->button != nullptr) {
            delete this->button;
        }
        this->button = bt;
    }

    void SetItem(Env_Item *item) {
        if (this->item != nullptr) {
            delete this->item;
        }
        this->item = item;
    }
};

#endif