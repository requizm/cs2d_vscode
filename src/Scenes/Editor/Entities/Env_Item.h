#ifndef ENVITEM_H
#define ENVITEM_H

#include "../../../Models/UI/Panel.h"
#include "../../../Models/UI/TextBox.h"

class Env_Item
{
private:
    int id; //item'in id numarası. objelerin unique id'si ile karistirmayin
    Vector2<float> position;
    Vector2<float> size;

public:
    Env_Item();
    Env_Item(int id);
    ~Env_Item();

    Sprite sp;

    void ProcessInput();
    void Update();
    void Render(SpriteRenderer &worldRenderer, SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer, float time);

    int getId();
    void SetId(int id);

    std::shared_ptr<Panel> p_panel;
    std::shared_ptr<Button> b_okay, b_tile;
    std::shared_ptr<TextBox> t_id;
};

#endif