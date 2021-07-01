#ifndef ENVITEM_H
#define ENVITEM_H

#include "../../../../Core/UI/Panel.hpp"
#include "../../../../Core/UI/TextBox.hpp"
#include "../../../../Core/UI/TextButton.hpp"
#include "../../../Model/TileButton.hpp"


class Env_Item
{
   private:
    int item_id = 0;  // 0=null  1=ak47   2=m4a1 ..

    Vector2<int> position;
    Vector2<int> size;
    Sprite sp;

    TileButtonWorld *button;

   public:
    int obj_id = 0;
    Env_Item() = default;
    Env_Item(int id, Vector2<int> position);
    ~Env_Item();

    void Initialize();

    void ProcessInput();
    void Update();
    void Render(SpriteRenderer &worldRenderer, SpriteRenderer &menuRenderer,
                SquareRenderer &squareRenderer, float time);

    /**
     * @brief Get Item ID
     *
     * @return int
     */
    int getItemID();

    /**
     * @brief Set Item ID
     *
     * @param id
     */
    void setItemID(int id);

    /**
     * @brief Get Obj ID
     *
     * @return int
     */
    int getObjID();

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
    TextButton *b_okay, *b_cancel, *b_delete;
    TextBox *t_id;

    bool isPressedOrHover();
};

#endif