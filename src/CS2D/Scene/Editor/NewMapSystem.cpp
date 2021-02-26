#include "NewMapSystem.hpp"

#include "Editor.hpp"

#if defined(WIN32) && defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

NewMapSystem::NewMapSystem()
{
    newPanel = new Panel(
        Vector2<int>(Editor::instance().tilePanel->GetSize().x + 20, Editor::instance().controlPanel->GetSize().y),
        "New Map", Vector2<int>(400, 135), *(Editor::instance().textRenderer), true, true, 1.0F,
        Vector3<float>(0.21F), 0.8F);
    newPanel->setMovable(false);
    newPanel->SetEnable(false);

    Vector2<int> pos;
    pos = Vector2<int>(180, 40) + newPanel->GetPosition();
    t_mapSizeX =
        new TextBox(pos, *(Editor::instance().textRenderer), Vector2<int>(60, 20), newPanel,
                    true, 1.0F, Vector3<float>(0.58F));

    pos = Vector2<int>(250, 40) + newPanel->GetPosition();
    t_mapSizeY =
        new TextBox(pos, *(Editor::instance().textRenderer), Vector2<int>(60, 20),
                    true, 1.0F, Vector3<float>(0.58F));
    t_mapSizeY->SetParent(newPanel);

    pos = Vector2<int>(180, 65) + newPanel->GetPosition();
    t_tile =
        new TextBox(pos, *(Editor::instance().textRenderer), Vector2<int>(120, 20),
                    true, 1.0F, Vector3<float>(0.58F));
    t_tile->SetParent(newPanel);

    pos = Vector2<int>(40, 40) + newPanel->GetPosition();
    l_mapSize = new Label(
        "Map Size", pos, *(Editor::instance().textRenderer), newPanel, 1.0F,
        Vector3<float>(0.58F), UIObjectType::LABEL, LabelType::NOT_CLICKABLE);
    l_mapSize->SetMouseEvent(false);

    pos = Vector2<int>(240, 40) + newPanel->GetPosition();
    l_x = new Label("x", pos, *(Editor::instance().textRenderer), newPanel, 1.0F,
                    Vector3<float>(0.58F), UIObjectType::LABEL,
                    LabelType::NOT_CLICKABLE);
    l_x->SetMouseEvent(false);

    pos = Vector2<int>(40, 65) + newPanel->GetPosition();
    l_tile = new Label("Tileset", pos, *(Editor::instance().textRenderer), newPanel,
                       1.0F, Vector3<float>(0.58F), UIObjectType::LABEL,
                       LabelType::NOT_CLICKABLE);
    l_tile->SetMouseEvent(false);


    b_okey = new TextButton(
        "Okay", Vector2<int>(50, 105), Vector2<int>(60, 20), *(Editor::instance().textRenderer), newPanel,
        Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    b_okey->setButtonClickColor(Vector3<float>(0.30F));
    b_okey->setButtonHoverColor(Vector3<float>(0.30F));
    b_okey->setTextHoverColor(Vector3<float>(0.58F));
    b_okey->setTextClickColor(Vector3<float>(1.0F));
    b_okey->setHaveOutline(true);
    b_okey->setOutlineColor(Vector3<float>(1.0F));
}

NewMapSystem::~NewMapSystem()
{
    delete l_tile;
    delete l_mapSize;
    delete l_x;
    delete t_tile;
    delete t_mapSizeX;
    delete t_mapSizeY;
    delete b_okey;
    delete newPanel;
}

void NewMapSystem::Start() {}
void NewMapSystem::ProcessInput() { newPanel->ProcessInput(); }
void NewMapSystem::Update() { newPanel->Update(); }
void NewMapSystem::Render(SpriteRenderer &menuRenderer,
                          SquareRenderer &squareRenderer)
{
    newPanel->Draw(menuRenderer, squareRenderer);
}

bool NewMapSystem::isPressedOrHover()
{
    return newPanel->isPressed || newPanel->isMouseHover(false);
}
bool NewMapSystem::isEditMode()
{
    return t_mapSizeX->editMode || t_mapSizeY->editMode || t_tile->editMode;
}

bool NewMapSystem::isMouseHover() { return newPanel->isMouseHover(false); }

NewMapResult NewMapSystem::NewMap(std::string tileSet, Vector2<int> mapSize)
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    NewMapResult res = NewMapResult();

    Editor::instance().time = 0.0F;
    Editor::instance().position =
        Vector2<int>(0 - Editor::instance().buildPanel->GetSize().x, 0);

    Editor::instance().firstSelect = false;
    Editor::instance().mapLimit = mapSize;

    Editor::instance().texture.x =
        ResourceManager::GetTexture(tileSet).Width / 32;
    Editor::instance().texture.y =
        ResourceManager::GetTexture(tileSet).Height / 32;
    Editor::instance().tileCount =
        Editor::instance().texture.x * Editor::instance().texture.y;

    InputManager::scroll.y = 0.0F;

    int curIndex = 0;
    for (int i = 0; i < Editor::instance().tileCount; i++)
    {
        const int xPos = 32 * (curIndex % Editor::instance().maxCellInColumn);
        const int yPos = 32 * (curIndex / Editor::instance().maxCellInColumn);
        const Vector2<int> pos(xPos, yPos);
        const Vector2<int> size(Vector2<int>(32, 32));
        const int xoffset =
            curIndex % (ResourceManager::GetTexture(tileSet).Width / 32);
        const int yoffset =
            curIndex / (ResourceManager::GetTexture(tileSet).Width / 32);
        const Sprite sprite = Sprite(ResourceManager::GetTexture(tileSet),
                                     (xoffset)*32, yoffset * 32, 32, 32);
        Tile tile = Tile(pos, sprite, size, TileTypes::FLOOR, curIndex++);
        TileButtonScreen *button = new TileButtonScreen(tile, Editor::instance().tilePanel);
        button->independent = true;
        res.tilesUI.push_back(button);
    }

    for (int i = 0; i < Editor::instance().mapLimit.x; i++)
    {
        for (int j = 0; j < Editor::instance().mapLimit.y; j++)
        {
            ButtonTile *t = new ButtonTile();
            t->tileButton->SetPosition(Utils::CellToPosition(Vector2<int>(i, j)));
            t->tileButton->getTile().frame = 0;
            t->tileButton->getTile().setType(TileTypes::FLOOR);
            res.tiles.push_back(t);
        }
    }

    return res;
}
NewMapResult NewMapSystem::B_NewMap()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    std::string sizeX = t_mapSizeX->getText();
    std::string sizeY = t_mapSizeY->getText();
    std::string tileSet = t_tile->getText();
    if (sizeX.empty() || sizeY.empty() || tileSet.empty())
    {
        WRITE_ERROR("BOS");
        return (NewMapResult());
    }
    if (ResourceManager::GetTexture(tileSet).Width == 0)
    {
        WRITE_ERROR("BOYLE BIR TEXTURE YOK");
        return (NewMapResult());
    }
    if (!Utils::TryStringToInt(sizeX) || !Utils::TryStringToInt(sizeY))
    {
        WRITE_ERROR("BUNLAR SAYI DEGIL");
        return (NewMapResult());
    }

    int isizeX = Utils::StringToInt(sizeX);
    int isizeY = Utils::StringToInt(sizeY);

    if (isizeX <= 0 || isizeY <= 0)
    {
        WRITE_ERROR("BUNLAR NEGATIF");
        return (NewMapResult());
    }
    return NewMap(tileSet, Vector2<int>(isizeX, isizeY));
}