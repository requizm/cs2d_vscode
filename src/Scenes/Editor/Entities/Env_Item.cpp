#include "Env_Item.h"
#include "../../../Others/Game_Parameters.h"

Env_Item::Env_Item(int id)
{
    this->id = id;
    sp = Sprite(ResourceManager::GetTexture("bulb"));
}

Env_Item::Env_Item()
{
}

Env_Item::~Env_Item()
{
}

void Env_Item::ProcessInput()
{
}
void Env_Item::Update(const float dt)
{
}
void Env_Item::Render(SpriteRenderer &worldRenderer, SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer, float dt)
{
    worldRenderer.DrawSprite(sp, Vector2<float>(Game_Parameters::SIZE_TILE / 2 - Game_Parameters::SIZE_TILE / 4), Vector2<float>(Game_Parameters::SIZE_TILE / 2),
                             Vector3<float>(0.5F, 1.0F, 0.0F), false, 0.0F, 0.15F, true, dt);
    p_panel->Draw(menuRenderer, squareRenderer);
}

int Env_Item::getId()
{
    return id;
}
void Env_Item::SetId(int id)
{
    this->id = id;
}