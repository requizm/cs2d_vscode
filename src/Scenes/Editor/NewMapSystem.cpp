#include "NewMapSystem.hpp"
#include "../../Others/Utils.hpp"

NewMapSystem::NewMapSystem(/* args */)
{
}

NewMapSystem::~NewMapSystem()
{
}

void NewMapSystem::Start()
{
}
void NewMapSystem::ProcessInput()
{
    newPanel->ProcessInput();
}
void NewMapSystem::Update()
{
    newPanel->Update();
}
void NewMapSystem::Render(SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer)
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

bool NewMapSystem::isMouseHover()
{
    return newPanel->isMouseHover(false);
}

NewMapResult *NewMapSystem::NewMap(std::string tileSet, Vector2<int> mapSize, float &dt, Vector2<int> &pos, bool &fSelect,
                                   Vector2<int> &mLimit, Vector2<int> &texture, int &tCount, std::shared_ptr<Panel> &tPanel,
                                   std::shared_ptr<Panel> &bPanel, Tile &sTile, int maxCell)
{
    NewMapResult *res = new NewMapResult();

    dt = 0.0F;
    pos = Vector2<int>(0 - bPanel->getSize().x, 0);

    fSelect = false;
    mLimit = mapSize;

    texture.x = ResourceManager::GetTexture(tileSet).Width / 32;
    texture.y = ResourceManager::GetTexture(tileSet).Height / 32;
    tCount = texture.x * texture.y;

    InputManager::scroll.y = 0.0F;

    int curIndex = 0;
    for (int i = 0; i < tCount; i++)
    {
        const int xPos = 32 * (curIndex % maxCell);
        const int yPos = 32 * (curIndex / maxCell);
        const Vector2<int> pos(xPos, yPos);
        const Vector2<int> size(Vector2<int>(32, 32));
        const int xoffset = curIndex % (ResourceManager::GetTexture(tileSet).Width / 32);
        const int yoffset = curIndex / (ResourceManager::GetTexture(tileSet).Width / 32);
        const Sprite sprite = Sprite(ResourceManager::GetTexture(tileSet), (xoffset)*32, yoffset * 32, 32, 32);
        Tile tile = Tile(pos, sprite, size, TileTypes::FLOOR, curIndex++);
        Button *button = new Button(tile);
        button->independent = true;
        button->setParent(tPanel.get(), true);
        res->tilesUI.push_back(std::make_shared<Button>(*button));
    }

    for (int i = 0; i < mLimit.x; i++)
    {
        for (int j = 0; j < mLimit.y; j++)
        {
            ButtonTile t = ButtonTile(Vector2<int>(i, j));
            t.button.getTile()->frame = 0;
            t.button.getTile()->setType(TileTypes::FLOOR);
            res->tiles.push_back(t);
        }
    }

    return res;
}
NewMapResult *NewMapSystem::B_NewMap(float &dt, Vector2<int> &pos, bool &fSelect, Vector2<int> &mLimit, Vector2<int> &texture,
                                     int &tCount, std::shared_ptr<Panel> &tPanel, std::shared_ptr<Panel> &bPanel, Tile &sTile,
                                     int maxCell)
{
    std::string sizeX = t_mapSizeX->getText();
    std::string sizeY = t_mapSizeY->getText();
    std::string tileSet = t_tile->getText();
    Logger::DebugLog(tileSet);
    Logger::DebugLog(sizeX);
    Logger::DebugLog(sizeY);
    if (sizeX.empty() || sizeY.empty() || tileSet.empty())
    {
        Logger::DebugLog("BOS");
        return new NewMapResult();
    }
    if (ResourceManager::GetTexture(tileSet).Width == 0)
    {
        Logger::DebugLog("BOYLE BIR TEXTURE YOK");
        return new NewMapResult();
    }
    if (!Utils::TryStringToInt(sizeX.c_str()) || !Utils::TryStringToInt(sizeY.c_str()))
    {
        Logger::DebugLog("BUNLAR SAYI DEGIL");
        return new NewMapResult();
    }

    int isizeX = Utils::StringToInt(sizeX.c_str());
    int isizeY = Utils::StringToInt(sizeY.c_str());

    if (isizeX <= 0 || isizeY <= 0)
    {
        Logger::DebugLog("BUNLAR NEGATIF");
        return new NewMapResult();
    }
    return NewMap(tileSet, Vector2<int>(isizeX, isizeY), dt, pos, fSelect, mLimit, texture, tCount, tPanel, bPanel, sTile, maxCell);
}