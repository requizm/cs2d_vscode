#ifndef ENVITEM_H
#define ENVITEM_H

#include "../../../Models/UI/Panel.hpp"
#include "../../../Models/UI/TextBox.hpp"

class Env_Item
{
private:
    int item_id = 0; // 0=null  1=ak47   2=m4a1 ..
    int obj_id = 0;
    Vector2<int> position;
    Vector2<int> size;
    Sprite sp;

    Button *button;

public:
    Env_Item();
    Env_Item(int id, Vector2<int> position);
    ~Env_Item();

    void Initialize();

    void ProcessInput();
    void Update();
    void Render(SpriteRenderer &worldRenderer, SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer, float time);

    int getId();
    void SetId(int id);

    Vector2<int> getPosition();
};

class Env_Item_Manager
{
public:
    Env_Item_Manager();
    ~Env_Item_Manager();

    void Update();
    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer);
    void ProcessInput();

    Panel *p_panel;
    Button *b_okay, *b_cancel;
    TextBox *t_id;

    bool isPressedOrHover();
};

#endif