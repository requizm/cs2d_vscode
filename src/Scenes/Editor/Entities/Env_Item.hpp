#ifndef ENVITEM_H
#define ENVITEM_H

#include "../../../Models/UI/Panel.hpp"
#include "../../../Models/UI/TextBox.hpp"

class Env_Item
{
private:
    int item_id = 0; // 0=null  1=ak47   2=m4a1 ..
    int obj_id = 0;
    Vector2<float> position;
    Vector2<float> size;
    Sprite sp;

    std::shared_ptr<Button> button;

public:
    Env_Item();
    Env_Item(int id, Vector2<float> position);
    ~Env_Item();

    void Initialize();

    void ProcessInput();
    void Update();
    void Render(SpriteRenderer &worldRenderer, SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer, float time);

    int getId();
    void SetId(int id);

    Vector2<float> getPosition();

    bool isPressedOrHover();

    std::shared_ptr<Panel> p_panel;
    std::shared_ptr<Button> b_okay, b_tile;
    std::shared_ptr<TextBox> t_id;
};

#endif