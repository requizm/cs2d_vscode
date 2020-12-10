#ifndef ENVITEM_H
#define ENVITEM_H

#include "../../../Models/UI/Panel.h"
#include "../../../Models/UI/TextBox.h"

class Env_Item
{
private:
    int item_id = 0; // 0=ak47   1=m4a1 ..
    int obj_id = 0;
    Vector2<float> position;
    Vector2<float> size;

public:
    Env_Item();
    Env_Item(Panel &tilePanel, Panel &controlPanel, TextRenderer &textRenderer);
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