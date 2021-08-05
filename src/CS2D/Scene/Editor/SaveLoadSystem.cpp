#include "SaveLoadSystem.hpp"

#include <rapidxml-1.13/rapidxml.hpp>
#include <rapidxml-1.13/rapidxml_print.hpp>

#include "../../../Core/Loader/XMLLoader.hpp"
#include "../../../Core/Manager/InputManager.hpp"
#include "../../../Core/Manager/Logger.hpp"
#include "../../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../../Core/Manager/ResourceManager.hpp"
#include "../../../Core/Manager/Utils.hpp"
#include "../../Other/GameParameters.hpp"
#include "../../Other/SceneManager.hpp"
#include "Editor.hpp"


#if defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

SaveLoadSystem::~SaveLoadSystem()
{
    delete load_mapsPanel;
    delete save_mapsPanel;

    delete b_map_load;
    delete b_map_save;

    delete t_load;
    delete t_save;

    delete load_listMaps;
    delete save_listMaps;

    delete loadPanel;
    delete savePanel;
}

void SaveLoadSystem::Load()
{
    Editor *editor = SceneManager::instance().GetActiveScene<Editor>();
    this->loadPanel = new Panel(
        Vector2<int>(editor->tilePanel->getSize().x + 20, editor->controlPanel->getSize().y),
        "Load Panel", Vector2<int>(400, 200), *editor->textRenderer, true, true, 1.0F,
        Vector3<float>(0.21F), 0.8F);
    this->loadPanel->setMovable(false);
    this->loadPanel->setEnable(false);
    this->load_mapsPanel = new Panel(
        Vector2<int>(20, 60), "Map Panel", Vector2<int>(300, 100),
        *editor->textRenderer, true, false, 1.0F, Vector3<float>(0.21F), 0.6F);
    this->load_mapsPanel->setMovable(false);
    this->load_mapsPanel->setEnable(false);
    this->load_mapsPanel->setScrollable(true);
    this->load_mapsPanel->setOutline(true);
    this->load_mapsPanel->setVisible(true);
    this->load_mapsPanel->setOutlineColor(Vector3<float>(0.47F));
    this->load_mapsPanel->setParent(this->loadPanel, true);
    this->load_mapsPanel->setParentCenterPos();
    this->load_listMaps =
        new ListItem(this->load_mapsPanel);
    // this->load_listMaps->setParent(this->load_mapsPanel,
    // true);
    this->t_load =
        new TextBox(Vector2<int>(20, 170), *editor->textRenderer, Vector2<int>(120, 20),
                    true, 1.0F, Vector3<float>(0.58F));
    this->t_load->setParent(this->loadPanel);
    this->t_load->editable = false;
    this->b_map_load = new TextButton(
        "Load", Vector2<int>(180, 170), Vector2<int>(60, 20), *editor->textRenderer,
        Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    this->b_map_load->setButtonClickColor(Vector3<float>(0.30F));
    this->b_map_load->setButtonHoverColor(Vector3<float>(0.30F));
    this->b_map_load->setTextHoverColor(Vector3<float>(0.58F));
    this->b_map_load->setTextClickColor(Vector3<float>(1.0F));
    this->b_map_load->setHaveOutline(true);
    this->b_map_load->setOutlineColor(Vector3<float>(1.0F));
    this->b_map_load->setParent(this->loadPanel);
    std::function<void(TextButton *, TextButton *)> loadListChanged =
        std::bind(&SaveLoadSystem::LoadListChanged, this,
                  std::placeholders::_1, std::placeholders::_2);
    this->load_listMaps->AddListener(loadListChanged);

    // harita save paneli
    this->savePanel = new Panel(
        Vector2<int>(editor->tilePanel->getSize().x + 20, editor->controlPanel->getSize().y),
        "Save Panel", Vector2<int>(400, 200), *editor->textRenderer, true, true, 1.0F,
        Vector3<float>(0.21F), 0.8F);
    this->savePanel->setMovable(false);
    this->savePanel->setEnable(false);
    this->save_mapsPanel = new Panel(
        Vector2<int>(20, 60), "Map Panel", Vector2<int>(300, 100),
        *editor->textRenderer, true, false, 1.0F, Vector3<float>(0.21F), 0.6F);
    this->save_mapsPanel->setMovable(false);
    this->save_mapsPanel->setEnable(false);
    this->save_mapsPanel->setScrollable(true);
    this->save_mapsPanel->setOutline(true);
    this->save_mapsPanel->setVisible(true);
    this->save_mapsPanel->setOutlineColor(Vector3<float>(0.47F));
    this->save_mapsPanel->setParent(this->savePanel, true);
    this->save_mapsPanel->setParentCenterPos();
    this->save_listMaps =
        new ListItem(this->save_mapsPanel);
    // this->save_listMaps->setParent(this->save_mapsPanel,
    // true);
    this->t_save =
        new TextBox(Vector2<int>(20, 170), *editor->textRenderer, Vector2<int>(120, 20),
                    true, 1.0F, Vector3<float>(0.58F));
    this->t_save->setParent(this->savePanel);
    this->b_map_save = new TextButton(
        "Save", Vector2<int>(180, 170), Vector2<int>(60, 20), *editor->textRenderer,
        Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    this->b_map_save->setButtonClickColor(Vector3<float>(0.30F));
    this->b_map_save->setButtonHoverColor(Vector3<float>(0.30F));
    this->b_map_save->setTextHoverColor(Vector3<float>(0.58F));
    this->b_map_save->setTextClickColor(Vector3<float>(1.0F));
    this->b_map_save->setHaveOutline(true);
    this->b_map_save->setOutlineColor(Vector3<float>(1.0F));
    this->b_map_save->setParent(this->savePanel);
    std::function<void(TextButton *, TextButton *)> saveListChanged =
        std::bind(&SaveLoadSystem::SaveListChanged, this,
                  std::placeholders::_1, std::placeholders::_2);
    this->save_listMaps->AddListener(saveListChanged);
}
void SaveLoadSystem::ProcessInput()
{
    savePanel->ProcessInput();
    loadPanel->ProcessInput();

    save_listMaps->ProcessInput();
    load_listMaps->ProcessInput();
}

void SaveLoadSystem::Update()
{
    savePanel->Update();
    loadPanel->Update();

    save_listMaps->Update();
    load_listMaps->Update();
}
void SaveLoadSystem::Render(SpriteRenderer &menuRenderer,
                            SquareRenderer &squareRenderer)
{
    savePanel->Draw(menuRenderer, squareRenderer);
    loadPanel->Draw(menuRenderer, squareRenderer);

    save_listMaps->Draw(squareRenderer);
    load_listMaps->Draw(squareRenderer);
}

void SaveLoadSystem::SaveMap()
{
    Editor *editor = SceneManager::instance().GetActiveScene<Editor>();
    if (!t_save->getText().empty())
    {
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<> *node_map =
            doc.allocate_node(rapidxml::node_element, "map");
        // int i = 0;
        for (int i = 0; i < editor->mapLimit.x * editor->mapLimit.y; i++)
        {
            rapidxml::xml_node<> *node_tile =
                doc.allocate_node(rapidxml::node_element, "tile");
            char *cellX =
                doc.allocate_string(std::to_string(editor->tils->tiles[i].cell.x).c_str());
            char *cellY =
                doc.allocate_string(std::to_string(editor->tils->tiles[i].cell.y).c_str());
            char *frame = doc.allocate_string(
                std::to_string(editor->tils->tiles[i].button.getTile().frame).c_str());
            char *type = doc.allocate_string(
                std::to_string((int)editor->tils->tiles[i].button.getTile().getType())
                    .c_str());
            int item_id = editor->tils->tiles[i].item != nullptr ? editor->tils->tiles[i].item->getItemID() : 0;
            char *itemId = doc.allocate_string(std::to_string(item_id).c_str());

            rapidxml::xml_node<> *node_tile_texture;

            node_tile_texture =
                doc.allocate_node(rapidxml::node_element, "tileTexture", frame);

            rapidxml::xml_node<> *node_cellX =
                doc.allocate_node(rapidxml::node_element, "cellX", cellX);
            rapidxml::xml_node<> *node_cellY =
                doc.allocate_node(rapidxml::node_element, "cellY", cellY);
            rapidxml::xml_node<> *node_tile_type =
                doc.allocate_node(rapidxml::node_element, "tileType", type);
            rapidxml::xml_node<> *node_item_id =
                doc.allocate_node(rapidxml::node_element, "itemID", itemId);

            node_tile->append_node(node_tile_texture);
            node_tile->append_node(node_cellX);
            node_tile->append_node(node_cellY);
            node_tile->append_node(node_tile_type);
            node_tile->append_node(node_item_id);
            node_map->append_node(node_tile);
        }

        char *limitX = doc.allocate_string(
            std::to_string(editor->mapLimit.x).c_str());
        char *limitY = doc.allocate_string(
            std::to_string(editor->mapLimit.y).c_str());
        char *tile =
            doc.allocate_string(editor->currentTileSet.c_str());
        char *name = doc.allocate_string(t_save->getText().c_str());
        rapidxml::xml_node<> *node_info =
            doc.allocate_node(rapidxml::node_element, "info");
        rapidxml::xml_node<> *node_name =
            doc.allocate_node(rapidxml::node_element, "name", name);
        rapidxml::xml_node<> *node_tileset =
            doc.allocate_node(rapidxml::node_element, "tileSet", tile);
        rapidxml::xml_node<> *node_maplimitx =
            doc.allocate_node(rapidxml::node_element, "mapLimitX", limitX);
        rapidxml::xml_node<> *node_maplimity =
            doc.allocate_node(rapidxml::node_element, "mapLimitY", limitY);
        node_info->append_node(node_name);
        node_info->append_node(node_tileset);
        node_info->append_node(node_maplimitx);
        node_info->append_node(node_maplimity);
        doc.append_node(node_map);
        doc.append_node(node_info);
        std::ofstream fileC;
        std::string a(GameParameters::resDirectory + "levels/" +
                      t_save->getText() + ".xml");
        fileC.open(a.c_str());
        ASSERTM_ERROR(fileC, a + "dosyasi acilamadi");
        fileC << doc;
        fileC.close();

        savePanel->setEnable(false);
    }
}
void SaveLoadSystem::B_SaveMap()
{
    save_listMaps->Clear();

    std::vector<std::string> maps = Utils::GetFileNames(GameParameters::resDirectory + "levels");

    for (std::vector<int>::size_type i = 0; i != maps.size(); i++)
    {
        save_listMaps->AddItem(maps[i]);
    }
    this->savePanel->setEnable(true);
}

NewMapResult *SaveLoadSystem::LoadMap(const std::string &mapName)
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    NewMapResult *res = new NewMapResult();
    Editor *editor = SceneManager::instance().GetActiveScene<Editor>();

    InputManager::scroll.y = 0.0F;
    this->loadPanel->setEnable(false);

    std::string mapNameN = GameParameters::resDirectory + "levels/" + mapName + ".xml";
    XMLLoader loader = XMLLoader(mapNameN);

    this->t_save->setText(
        loader.GetDoc().first_node("info")->first_node("name")->value());
    editor->currentTileSet =
        loader.GetDoc().first_node("info")->first_node("tileSet")->value();
    char *mapx =
        loader.GetDoc().first_node("info")->first_node("mapLimitX")->value();
    char *mapy =
        loader.GetDoc().first_node("info")->first_node("mapLimitY")->value();
    editor->texture.x =
        ResourceManager::GetTexture(editor->currentTileSet).Width / 32;
    editor->texture.y =
        ResourceManager::GetTexture(editor->currentTileSet).Height / 32;
    editor->tileCount =
        editor->texture.x * editor->texture.y;
    editor->mapLimit.x = atoi(mapx);
    editor->mapLimit.y = atoi(mapy);
    rapidxml::xml_node<> *node = loader.GetDoc().first_node("map");

    res->tilesUILength = editor->tileCount;
    res->tilesLength = editor->mapLimit.x * editor->mapLimit.y;

    res->tilesUI = (TileButtonScreen *)malloc(sizeof(TileButtonScreen) * editor->tileCount);
    res->tiles = (ButtonTile *)malloc(sizeof(ButtonTile) * (editor->mapLimit.x * editor->mapLimit.y));
#if defined(TRACY_ENABLE)
    TracyAlloc(res->tilesUI, sizeof(TileButtonScreen) * editor->tileCount);
    TracyAlloc(res->tiles, sizeof(ButtonTile) * (editor->mapLimit.x * editor->mapLimit.y));
#endif
    int i = 0;
    for (rapidxml::xml_node<> *child = node->first_node(); child;
         child = child->next_sibling())
    {
        // std::cout << child->first_node("cellY")->value() << std::endl;
        // tile.SetSize(Vector2<int>(Game::Width / 26.5, Game::Width / 26.5));
        char *x = child->first_node("cellX")->value();
        char *y = child->first_node("cellY")->value();
        char *tIndex = child->first_node("tileTexture")->value();
        char *tType = child->first_node("tileType")->value();
        char *tItemId = child->first_node("itemID")->value();
        int cellX = atoi(x);
        int cellY = atoi(y);
        int textureIndex = atoi(tIndex);
        int tileType = atoi(tType);
        int itemId = atoi(tItemId);
        const Vector2<int> pos(GameParameters::SIZE_TILE * cellX,
                               GameParameters::SIZE_TILE * cellY);
        const Vector2<int> size(
            Vector2<int>(GameParameters::SIZE_TILE, GameParameters::SIZE_TILE));
        const int xoffset =
            textureIndex %
            (ResourceManager::GetTexture(editor->currentTileSet)
                 .Width /
             32);
        const int yoffset =
            textureIndex /
            (ResourceManager::GetTexture(editor->currentTileSet)
                 .Width /
             32);
        const Sprite sprite = Sprite(
            ResourceManager::GetTexture(editor->currentTileSet),
            (xoffset)*32, yoffset * 32, 32, 32);
        Tile tile = Tile(pos, sprite, size, TileTypes(tileType), textureIndex);
        TileButtonWorld b = TileButtonWorld(tile);
        if (itemId == 0)
        {
            new (res->tiles + i) ButtonTile(b, Vector2<int>(cellX, cellY));
        }
        else
        {
            new (res->tiles + i) ButtonTile(itemId, b, Vector2<int>(cellX, cellY));
        }
        i += 1;
    }

    int curIndex = 0;
    for (int i = 0; i < editor->tileCount; i++)
    {
        const int xPos = 32 * (curIndex % editor->maxCellInColumn);
        const int yPos = 32 * (curIndex / editor->maxCellInColumn);
        const Vector2<int> pos(xPos, yPos);
        const Vector2<int> size(Vector2<int>(32, 32));
        const int xoffset =
            curIndex % (ResourceManager::GetTexture(editor->currentTileSet).Width / 32);
        const int yoffset =
            curIndex / (ResourceManager::GetTexture(editor->currentTileSet).Width / 32);
        const Sprite sprite = Sprite(ResourceManager::GetTexture(editor->currentTileSet),
                                     (xoffset)*32, yoffset * 32, 32, 32);
        Tile tile = Tile(pos, sprite, size, TileTypes::FLOOR, curIndex++);
        new (res->tilesUI + i) TileButtonScreen(tile);
        res->tilesUI[i].independent = true;
        res->tilesUI[i].setParent(editor->tilePanel, true);
    }

    return res;
}
void SaveLoadSystem::B_LoadMap()
{
    load_listMaps->Clear();

    std::vector<std::string> maps = Utils::GetFileNames(GameParameters::resDirectory + "levels");

    for (std::vector<int>::size_type i = 0; i != maps.size(); i++)
    {
        load_listMaps->AddItem(maps[i]);
    }
    load_listMaps->Select(0);
    this->loadPanel->setEnable(true);
}

bool SaveLoadSystem::isPressedOrHover()
{
    return loadPanel->isPressed || savePanel->isPressed ||
           loadPanel->isMouseHover(false) || savePanel->isMouseHover(false);
}

bool SaveLoadSystem::isEditMode()
{
    return t_load->editMode || t_save->editMode;
}

bool SaveLoadSystem::isMouseHover()
{
    return loadPanel->isMouseHover(false) || savePanel->isMouseHover(false);
}

void SaveLoadSystem::SaveListChanged(TextButton *old, TextButton *n)
{
    t_save->setText(n->getText());
}

void SaveLoadSystem::LoadListChanged(TextButton *old, TextButton *n)
{
    t_load->setText(n->getText());
}