#include "Env_Item.hpp"

#include "../Editor.hpp"
#include "../../../Model/Scene.hpp"
#include "../../../Other/SceneManager.hpp"

#if defined(WIN32) && defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

Env_Item::Env_Item() {}

Env_Item::Env_Item(int id, Vector2<int> position)
{
    this->item_id = id;
    this->position = position;
    this->Initialize();
}

Env_Item::~Env_Item()
{
    button->removeParent();
    if (button != nullptr) delete button;
    button = nullptr;
}

void Env_Item::Initialize()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    sp = Sprite(ResourceManager::GetTexture("bulb"));
    this->obj_id = Utils::GenerateID();

    Tile t = Tile(position, sp, Vector2<int>(GameParameters::SIZE_TILE));
    button = new TileButtonWorld(t, 1.0F);
    //button->setType(ButtonType::ENV_OBJ);

    if (item_id != 0)
    {
        SceneManager::instance().GetActiveScene<Editor>()->env_items.push_back(this);
    }
}

void Env_Item::ProcessInput() {}
void Env_Item::Update()
{
    // button.Update();
}
void Env_Item::Render(SpriteRenderer &worldRenderer,
                      SpriteRenderer &menuRenderer,
                      SquareRenderer &squareRenderer, float time)
{
    button->Draw(worldRenderer, squareRenderer);
    /*worldRenderer.DrawSprite(sp, Vector2<float>(position +
     * GameParameters::SIZE_TILE / 4), Vector2<float>(GameParameters::SIZE_TILE
     * / 2), Vector3<float>(0.5F, 1.0F, 0.0F), false, 0.0F, 0.15F, true,
     * time);*/
}

int Env_Item::getItemID() { return item_id; }
void Env_Item::setItemID(int id) { this->item_id = id; }

int Env_Item::getObjID() { return this->obj_id; }

Vector2<int> Env_Item::getPosition() { return position; }

Env_Item_Manager::Env_Item_Manager()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    p_panel =
        new Panel(Vector2<int>(SceneManager::instance().GetActiveScene<Editor>()->tilePanel->getSize().x + 20,
                               SceneManager::instance().GetActiveScene<Editor>()->controlPanel->getSize().y),
                  "Entity Options", Vector2<int>(400, 200),
                  *(SceneManager::instance().GetActiveScene<Editor>()->textRenderer), true, true, 1.0F,
                  Vector3<float>(0.21F), 0.8F);
    p_panel->setMovable(false);
    p_panel->setEnable(false);

    b_okay = new TextButton("Okay", Vector2<int>(330, 170), Vector2<int>(60, 20),
                        *(SceneManager::instance().GetActiveScene<Editor>()->textRenderer),
                        Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    b_okay->setButtonClickColor(Vector3<float>(0.30F));
    b_okay->setButtonHoverColor(Vector3<float>(0.30F));
    b_okay->setTextHoverColor(Vector3<float>(0.58F));
    b_okay->setTextClickColor(Vector3<float>(1.0F));
    b_okay->setHaveOutline(true);
    b_okay->setOutlineColor(Vector3<float>(1.0F));
    b_okay->setParent(p_panel);

    b_cancel =
        new TextButton("Cancel", Vector2<int>(230, 170), Vector2<int>(60, 20),
                   *(SceneManager::instance().GetActiveScene<Editor>()->textRenderer), Vector3<float>(0.15F),
                   Vector3<float>(0.58F), 1.0F);
    b_cancel->setButtonClickColor(Vector3<float>(0.30F));
    b_cancel->setButtonHoverColor(Vector3<float>(0.30F));
    b_cancel->setTextHoverColor(Vector3<float>(0.58F));
    b_cancel->setTextClickColor(Vector3<float>(1.0F));
    b_cancel->setHaveOutline(true);
    b_cancel->setOutlineColor(Vector3<float>(1.0F));
    b_cancel->setParent(p_panel);

    b_delete = new TextButton("Delete", Vector2<int>(0, 170), Vector2<int>(60, 20),
                          *(SceneManager::instance().GetActiveScene<Editor>()->textRenderer),
                          Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    b_delete->setButtonClickColor(Vector3<float>(0.30F));
    b_delete->setButtonHoverColor(Vector3<float>(0.30F));
    b_delete->setTextHoverColor(Vector3<float>(0.58F));
    b_delete->setTextClickColor(Vector3<float>(1.0F));
    b_delete->setHaveOutline(true);
    b_delete->setOutlineColor(Vector3<float>(1.0F));
    b_delete->setParent(p_panel);

    t_id =
        new TextBox(Vector2<int>(300, 40), *(SceneManager::instance().GetActiveScene<Editor>()->textRenderer),
                    Vector2<int>(60, 20), true, 1.0F, Vector3<float>(0.58F));
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

void Env_Item_Manager::Update() { p_panel->Update(); }

void Env_Item_Manager::Draw(SpriteRenderer &spriteRenderer,
                            SquareRenderer &squareRenderer)
{
    p_panel->Draw(spriteRenderer, squareRenderer);
}

void Env_Item_Manager::ProcessInput() { p_panel->ProcessInput(); }

bool Env_Item_Manager::isPressedOrHover()
{
    return p_panel->isPressed || p_panel->isMouseHover(false);
}