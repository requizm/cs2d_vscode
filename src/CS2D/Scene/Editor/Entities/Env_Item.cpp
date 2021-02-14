#include "Env_Item.hpp"
#include "../Editor.hpp"

Env_Item::Env_Item()
{
}

Env_Item::Env_Item(int id, Vector2<int> position)
{
    this->item_id = id;
    this->position = position;
    this->Initialize();
}

Env_Item::~Env_Item()
{
    button->removeParent();
    delete button;
}

void Env_Item::Initialize()
{
    sp = Sprite(ResourceManager::GetTexture("bulb"));
    this->obj_id = Utils::GenerateID();

    Tile t = Tile(position, sp, Vector2<int>(GameParameters::SIZE_TILE));
    button = new Button(t, 1.0F, UIObjectType::ENV_ITEM);
    button->setType(ButtonType::ENV_OBJ);

    if (item_id != 0)
    {
        Editor::instance().env_items.push_back(this);
    }
}

void Env_Item::ProcessInput()
{
}
void Env_Item::Update()
{
    //button.Update();
}
void Env_Item::Render(SpriteRenderer &worldRenderer, SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer, float time)
{
    button->Draw(worldRenderer, squareRenderer);
    /*worldRenderer.DrawSprite(sp, Vector2<float>(position + GameParameters::SIZE_TILE / 4), Vector2<float>(GameParameters::SIZE_TILE / 2), Vector3<float>(0.5F, 1.0F, 0.0F), false, 0.0F, 0.15F, true, time);*/
}

int Env_Item::getItemID()
{
    return item_id;
}
void Env_Item::setItemID(int id)
{
    this->item_id = id;
}

int Env_Item::getObjID()
{
    return this->obj_id;
}

Vector2<int> Env_Item::getPosition()
{
    return position;
}

Env_Item_Manager::Env_Item_Manager()
{
    p_panel = new Panel(Vector2<int>(Editor::instance().tilePanel->getSize().x + 20, Editor::instance().controlPanel->getSize().y), "Entity Options", Vector2<int>(400, 200), *(Editor::instance().textRenderer), true, true, 1.0F, Vector3<float>(0.21F), 0.8F);
    p_panel->setMovable(false);
    p_panel->setEnable(false);

    b_okay = new Button("Okay", Vector2<int>(330, 170), Vector2<int>(60, 20), *(Editor::instance().textRenderer), Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    b_okay->setMouseClickColor(Vector3<float>(0.30F));
    b_okay->setMouseHoverColor(Vector3<float>(0.30F));
    b_okay->setLabelMouseHoverColor(Vector3<float>(0.58F));
    b_okay->setLabelClickColor(Vector3<float>(1.0F));
    b_okay->setOutline(true);
    b_okay->setOutlineColor(Vector3<float>(1.0F));
    b_okay->setParent(p_panel);

    b_cancel = new Button("Cancel", Vector2<int>(230, 170), Vector2<int>(60, 20), *(Editor::instance().textRenderer), Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    b_cancel->setMouseClickColor(Vector3<float>(0.30F));
    b_cancel->setMouseHoverColor(Vector3<float>(0.30F));
    b_cancel->setLabelMouseHoverColor(Vector3<float>(0.58F));
    b_cancel->setLabelClickColor(Vector3<float>(1.0F));
    b_cancel->setOutline(true);
    b_cancel->setOutlineColor(Vector3<float>(1.0F));
    b_cancel->setParent(p_panel);

    b_delete = new Button("Delete", Vector2<int>(0, 170), Vector2<int>(60, 20), *(Editor::instance().textRenderer), Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    b_delete->setMouseClickColor(Vector3<float>(0.30F));
    b_delete->setMouseHoverColor(Vector3<float>(0.30F));
    b_delete->setLabelMouseHoverColor(Vector3<float>(0.58F));
    b_delete->setLabelClickColor(Vector3<float>(1.0F));
    b_delete->setOutline(true);
    b_delete->setOutlineColor(Vector3<float>(1.0F));
    b_delete->setParent(p_panel);

    t_id = new TextBox(Vector2<int>(300, 40), *(Editor::instance().textRenderer), Vector2<int>(60, 20), true, 1.0F, Vector3<float>(0.58F));
    t_id->setParent(p_panel);
}

Env_Item_Manager::~Env_Item_Manager()
{
    delete t_id;
    delete b_cancel;
    delete b_okay;
    delete b_delete;
    delete p_panel;
}

void Env_Item_Manager::Update()
{
    p_panel->Update();
}

void Env_Item_Manager::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    p_panel->Draw(spriteRenderer, squareRenderer);
}

void Env_Item_Manager::ProcessInput()
{
    p_panel->ProcessInput();
}

bool Env_Item_Manager::isPressedOrHover()
{
    return p_panel->isPressed || p_panel->isMouseHover(false);
}