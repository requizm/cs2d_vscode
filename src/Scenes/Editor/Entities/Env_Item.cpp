#include "Env_Item.hpp"
#include "../../../Others/Game_Parameters.hpp"
#include "../../../Others/Utils.hpp"
#include "../Editor.hpp"

Env_Item::Env_Item()
{
}

Env_Item::Env_Item(int id, Vector2<float> position)
{
    this->item_id = id;
    this->position = position;
    this->Initialize();
}

Env_Item::~Env_Item()
{
}

void Env_Item::Initialize()
{
    sp = Sprite(ResourceManager::GetTexture("bulb"));
    this->obj_id = Utils::GenerateID();

    p_panel = std::make_shared<Panel>(Vector2<float>(Editor::instance().tilePanel->getSize().x + 20, Editor::instance().controlPanel->getSize().y), "Entity Options", Vector2<float>(400, 200), *(Editor::instance().textRenderer), true, true, 1.0F, Vector3<float>(0.21F), 0.8F);
    p_panel->setMovable(false);
    p_panel->setEnable(false);

    b_okay = std::make_shared<Button>("Okay", Vector2<float>(330.0F, 170.0F), Vector2<float>(60.0F, 20.0F), *(Editor::instance().textRenderer), Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    b_okay->setMouseClickColor(Vector3<float>(0.30F));
    b_okay->setMouseHoverColor(Vector3<float>(0.30F));
    b_okay->setLabelMouseHoverColor(Vector3<float>(0.58F));
    b_okay->setLabelClickColor(Vector3<float>(1.0F));
    b_okay->setOutline(true);
    b_okay->setOutlineColor(Vector3<float>(1.0F));
    b_okay->setParent(p_panel.get());

    b_cancel = std::make_shared<Button>("Cancel", Vector2<float>(260.0F, 170.0F), Vector2<float>(60.0F, 20.0F), *(Editor::instance().textRenderer), Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    b_cancel->setMouseClickColor(Vector3<float>(0.30F));
    b_cancel->setMouseHoverColor(Vector3<float>(0.30F));
    b_cancel->setLabelMouseHoverColor(Vector3<float>(0.58F));
    b_cancel->setLabelClickColor(Vector3<float>(1.0F));
    b_cancel->setOutline(true);
    b_cancel->setOutlineColor(Vector3<float>(1.0F));
    b_cancel->setParent(p_panel.get());

    t_id = std::make_shared<TextBox>(Vector2<float>(300.0F, 40.0F), *(Editor::instance().textRenderer), Vector2<float>(60.0F, 20.0F), true, 1.0F, Vector3<float>(0.58F));
    t_id->setParent(p_panel.get());

    Tile t = Tile(position, sp, Vector2<float>(Game_Parameters::SIZE_TILE));
    button = std::make_shared<Button>(t);
    button->setType(ButtonType::ENV_OBJ);

    if (item_id != 0)
    {
        Editor::instance().env_items.push_back(this);
    }
}

void Env_Item::ProcessInput()
{
    p_panel->ProcessInput();

    if (Editor::instance().selectedMode == SelectedMode::OBJECT_MOD && InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT))
    {
        Vector2<float> sw = Utils::ScreenToWorld(Editor::instance().camera->view, InputManager::mousePos);
        Vector2<int> c = Utils::PositionToCell(position);
        Vector2<int> d = Utils::PositionToCell(sw);
        if (d == c)
        {
            p_panel->setEnable(true);
            t_id->setText(std::to_string(item_id));
        }
    }
    if (b_okay->isMouseDown())
    {
        item_id = atoi(t_id->getText().c_str());
        p_panel->setEnable(false);
    }
    else if (b_cancel->isMouseDown())
    {
        p_panel->setEnable(false);
    }
}
void Env_Item::Update()
{
    p_panel->Update();
    //button.Update();
}
void Env_Item::Render(SpriteRenderer &worldRenderer, SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer, float time)
{
    button->Draw(worldRenderer, squareRenderer);
    /*worldRenderer.DrawSprite(sp, Vector2<float>(position + Game_Parameters::SIZE_TILE / 4), Vector2<float>(Game_Parameters::SIZE_TILE / 2), Vector3<float>(0.5F, 1.0F, 0.0F), false, 0.0F, 0.15F, true, time);*/
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

Vector2<float> Env_Item::getPosition()
{
    return position;
}

bool Env_Item::isPressedOrHover()
{
    return p_panel->isPressed || p_panel->isMouseHover(false);
}