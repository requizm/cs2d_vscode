#include "SaveLoadSystem.hpp"

#include "Editor.hpp"

#if defined(WIN32) && defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

SaveLoadSystem::SaveLoadSystem() {}

SaveLoadSystem::~SaveLoadSystem() {
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

void SaveLoadSystem::Start() {}
void SaveLoadSystem::ProcessInput() {
    savePanel->ProcessInput();
    loadPanel->ProcessInput();

    save_listMaps->ProcessInput();
    load_listMaps->ProcessInput();
}

void SaveLoadSystem::Update() {
    savePanel->Update();
    loadPanel->Update();

    save_listMaps->Update();
    load_listMaps->Update();
}
void SaveLoadSystem::Render(SpriteRenderer &menuRenderer,
                            SquareRenderer &squareRenderer) {
    savePanel->Draw(menuRenderer, squareRenderer);
    loadPanel->Draw(menuRenderer, squareRenderer);

    save_listMaps->Draw(menuRenderer, squareRenderer);
    load_listMaps->Draw(menuRenderer, squareRenderer);
}

void SaveLoadSystem::SaveMap() {
    if (!Editor::instance().tils->tiles.empty() && !t_save->getText().empty()) {
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<> *node_map =
            doc.allocate_node(rapidxml::node_element, "map");
        // int i = 0;
        for (auto &tile : Editor::instance().tils->tiles) {
            rapidxml::xml_node<> *node_tile =
                doc.allocate_node(rapidxml::node_element, "tile");
            char *cellX =
                doc.allocate_string(std::to_string(tile->cell.x).c_str());
            char *cellY =
                doc.allocate_string(std::to_string(tile->cell.y).c_str());
            char *frame = doc.allocate_string(
                std::to_string(tile->button->getTile()->frame).c_str());
            char *type = doc.allocate_string(
                std::to_string((int)tile->button->getTile()->getType())
                    .c_str());
            int item_id = tile->item != nullptr ? tile->item->getItemID() : 0;
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
            std::to_string(Editor::instance().mapLimit.x).c_str());
        char *limitY = doc.allocate_string(
            std::to_string(Editor::instance().mapLimit.y).c_str());
        char *tile =
            doc.allocate_string(Editor::instance().currentTileSet.c_str());
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
        if (!fileC) {
            std::string str = a + "dosyasi acilamadi";
            WRITE_ERROR(str);
            exit(EXIT_FAILURE);
        }
        fileC << doc;
        fileC.close();

        savePanel->setEnable(false);
    }
}
void SaveLoadSystem::B_SaveMap() {
    save_listMaps->Clear();

    std::vector<std::string> maps = getMapNames();

    for (std::vector<int>::size_type i = 0; i != maps.size(); i++) {
        save_listMaps->AddItem(maps[i]);
    }
    this->savePanel->setEnable(true);
}

std::vector<ButtonTile *> SaveLoadSystem::LoadMap(std::string &mapName) {
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    std::vector<ButtonTile *> tiles;

    InputManager::scroll.y = 0.0F;
    this->loadPanel->setEnable(false);

    mapName = GameParameters::resDirectory + "levels/" + mapName + ".xml";
    XMLLoader loader = XMLLoader(mapName);

    this->t_save->setText(
        loader.GetDoc().first_node("info")->first_node("name")->value());
    Editor::instance().currentTileSet =
        loader.GetDoc().first_node("info")->first_node("tileSet")->value();
    char *mapx =
        loader.GetDoc().first_node("info")->first_node("mapLimitX")->value();
    char *mapy =
        loader.GetDoc().first_node("info")->first_node("mapLimitY")->value();
    Editor::instance().mapLimit.x = atoi(mapx);
    Editor::instance().mapLimit.y = atoi(mapy);
    rapidxml::xml_node<> *node = loader.GetDoc().first_node("map");
    // std::cout <<
    // node->first_node("tile")->first_node("cellX")->next_sibling()->name() <<
    // std::endl;
    int i = 0;
    for (rapidxml::xml_node<> *child = node->first_node(); child;
         child = child->next_sibling()) {
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
            (ResourceManager::GetTexture(Editor::instance().currentTileSet)
                 .Width /
             32);
        const int yoffset =
            textureIndex /
            (ResourceManager::GetTexture(Editor::instance().currentTileSet)
                 .Width /
             32);
        const Sprite sprite = Sprite(
            ResourceManager::GetTexture(Editor::instance().currentTileSet),
            (xoffset)*32, yoffset * 32, 32, 32);
        Tile tile = Tile(pos, sprite, size, TileTypes(tileType), textureIndex);
        Button *b = new Button(tile);
        ButtonTile *t = nullptr;
        if (itemId == 0) {
            t = new ButtonTile(b, Vector2<int>(cellX, cellY));
        } else {
            t = new ButtonTile(itemId, b, Vector2<int>(cellX, cellY));
        }

        tiles.push_back(t);
    }

    return tiles;
}
void SaveLoadSystem::B_LoadMap() {
    load_listMaps->Clear();

    std::vector<std::string> maps = getMapNames();

    for (std::vector<int>::size_type i = 0; i != maps.size(); i++) {
        load_listMaps->AddItem(maps[i]);
    }
    load_listMaps->Select(0);
    this->loadPanel->setEnable(true);
}

bool SaveLoadSystem::isPressedOrHover() {
    return loadPanel->isPressed || savePanel->isPressed ||
           loadPanel->isMouseHover(false) || savePanel->isMouseHover(false);
}

bool SaveLoadSystem::isEditMode() {
    return t_load->editMode || t_save->editMode;
}

bool SaveLoadSystem::isMouseHover() {
    return loadPanel->isMouseHover(false) || savePanel->isMouseHover(false);
}

std::vector<std::string> SaveLoadSystem::getMapNames() {
    std::vector<std::string> maps;

    DIR *dir;
    struct dirent *ent;
    std::string str = GameParameters::resDirectory + "levels";
    if ((dir = opendir(str.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] == '.') continue;
            std::string mapName(ent->d_name);
            if (mapName.substr(mapName.size() - 4) == ".xml") {
                std::string a = mapName.substr(0, mapName.size() - 4);
                maps.push_back(a);
            }
        }
        closedir(dir);
    } else {
        perror("could not open directory");
    }
    return maps;
}

void SaveLoadSystem::SaveListChanged(Button *old, Button *n) {
    t_save->setText(n->getText());
}

void SaveLoadSystem::LoadListChanged(Button *old, Button *n) {
    t_load->setText(n->getText());
}