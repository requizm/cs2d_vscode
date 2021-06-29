#include "NewMapSystem.hpp"

#include "Editor.hpp"

#if defined(WIN32) && defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

NewMapSystem::NewMapSystem() {}

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
        Vector2<int>(0 - Editor::instance().buildPanel->getSize().x, 0);

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
        TileButtonScreen *button = new TileButtonScreen(tile);
        button->independent = true;
        button->setParent(Editor::instance().tilePanel, true);
        res.tilesUI.push_back(button);
    }

    for (int i = 0; i < Editor::instance().mapLimit.x; i++)
    {
        for (int j = 0; j < Editor::instance().mapLimit.y; j++)
        {
            ButtonTile *t = new ButtonTile(Vector2<int>(i, j));
            t->button->getTile().frame = 0;
            t->button->getTile().setType(TileTypes::FLOOR);
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