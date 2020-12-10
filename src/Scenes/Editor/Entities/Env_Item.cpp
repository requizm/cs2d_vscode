#include "Env_Item.h"
#include "../../../Others/Game_Parameters.h"
#include "../../../Others/Utils.h"

Env_Item::Env_Item(Panel &tilePanel, Panel &controlPanel, TextRenderer &textRenderer)
{
    sp = Sprite(ResourceManager::GetTexture("bulb"));
    this->obj_id = Utils::GenerateID();

    p_panel = std::make_shared<Panel>(Vector2<float>(tilePanel.getSize().x + 20, controlPanel.getSize().y), "Entity Options", Vector2<float>(400, 200), textRenderer, true, true, 1.0F, Vector3<float>(0.21F), 0.8F);
	p_panel->setMovable(false);
	p_panel->setEnable(true);

	b_okay = std::make_shared<Button>("Okay", Vector2<float>(50.0F, 105.0F), Vector2<float>(60.0F, 20.0F), textRenderer, Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
	b_okay->setMouseClickColor(Vector3<float>(0.30F));
	b_okay->setMouseHoverColor(Vector3<float>(0.30F));
	b_okay->setLabelMouseHoverColor(Vector3<float>(0.58F));
	b_okay->setLabelClickColor(Vector3<float>(1.0F));
	b_okay->setOutline(true);
	b_okay->setOutlineColor(Vector3<float>(1.0F));
	b_okay->setParent(p_panel.get());
}

Env_Item::Env_Item()
{

}

Env_Item::~Env_Item()
{
}

void Env_Item::ProcessInput()
{
    p_panel->ProcessInput();
}
void Env_Item::Update()
{
    p_panel->Update();
}
void Env_Item::Render(SpriteRenderer &worldRenderer, SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer, float time)
{
    worldRenderer.DrawSprite(sp, Vector2<float>(Game_Parameters::SIZE_TILE / 2 - Game_Parameters::SIZE_TILE / 4), Vector2<float>(Game_Parameters::SIZE_TILE / 2),
                             Vector3<float>(0.5F, 1.0F, 0.0F), false, 0.0F, 0.15F, true, time);
    p_panel->Draw(menuRenderer, squareRenderer);
}

int Env_Item::getId()
{
    return item_id;
}
void Env_Item::SetId(int id)
{
    this->item_id = id;
}