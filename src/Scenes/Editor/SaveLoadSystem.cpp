#include "SaveLoadSystem.hpp"
#include "Editor.hpp"
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

SaveLoadSystem::SaveLoadSystem()
{
}

SaveLoadSystem::~SaveLoadSystem()
{
}

void SaveLoadSystem::Start()
{
}
void SaveLoadSystem::ProcessInput()
{
    savePanel->ProcessInput();
    loadPanel->ProcessInput();

    if (savePanel->isEnable())
    {
        if (!save_mapsUI.empty())
        {
            for (std::vector<int>::size_type i = 0; i != save_mapsUI.size(); i++)
            {
                save_mapsUI[i]->ProcessInput();
            }
            for (std::vector<int>::size_type i = 0; i != save_mapsUI.size(); i++)
            {
                if (save_mapsUI[i]->isMouseDown() && save_mapsUI[i]->isRenderable())
                {
                    if (selectedMap != -1)
                    {
                        save_mapsUI.at(selectedMap)->setButtonColor(Vector3<float>(0.21F));
                        save_mapsUI.at(selectedMap)->setMouseHoverColor(Vector3<float>(0.25F));
                        save_mapsUI.at(selectedMap)->setLabelColor(Vector3<float>(0.58F));
                    }
                    save_mapsUI[i]->setButtonColor(Vector3<float>(0.35F));
                    save_mapsUI[i]->setMouseHoverColor(Vector3<float>(0.35F));
                    save_mapsUI[i]->setLabelColor(Vector3<float>(1.0F));
                    t_save->setText(save_mapsUI[i]->getText());
                    selectedMap = i;
                    break;
                }
            }
        }
    }

    if (loadPanel->isEnable())
    {
        if (!load_mapsUI.empty())
        {
            for (std::vector<int>::size_type i = 0; i != load_mapsUI.size(); i++)
            {
                load_mapsUI[i]->ProcessInput();
            }
            for (std::vector<int>::size_type i = 0; i != load_mapsUI.size(); i++)
            {
                if (load_mapsUI[i]->isMouseDown() && load_mapsUI[i]->isRenderable())
                {
                    if (selectedMap != -1)
                    {
                        load_mapsUI.at(selectedMap)->setButtonColor(Vector3<float>(0.21F));
                        load_mapsUI.at(selectedMap)->setMouseHoverColor(Vector3<float>(0.25F));
                        load_mapsUI.at(selectedMap)->setLabelColor(Vector3<float>(0.58F));
                    }
                    load_mapsUI[i]->setButtonColor(Vector3<float>(0.35F));
                    load_mapsUI[i]->setMouseHoverColor(Vector3<float>(0.35F));
                    load_mapsUI[i]->setLabelColor(Vector3<float>(1.0F));
                    t_load->setText(load_mapsUI[i]->getText());
                    selectedMap = i;
                    break;
                }
            }
        }
    }
}

void SaveLoadSystem::Update()
{
    savePanel->Update();
    loadPanel->Update();

    if (savePanel->isEnable() && !save_mapsUI.empty())
    {
        for (std::vector<int>::size_type i = 0; i != save_mapsUI.size(); i++)
        {
            save_mapsUI[i]->Update();
        }
    }
    if (loadPanel->isEnable() && !load_mapsUI.empty())
    {
        for (std::vector<int>::size_type i = 0; i != load_mapsUI.size(); i++)
        {
            load_mapsUI[i]->Update();
        }
    }
    if (InputManager::scrollYPressed)
    {
        if (savePanel->isEnable() && save_mapsPanel->isScrollable())
        {
            if (!save_mapsUI.empty())
            {
                bool check_1 = save_mapsUI.at(0)->getLocalPosition().y == 0 && InputManager::scroll.y > 0;
                bool check_2 = save_mapsUI.at(save_mapsUI.size() - 1)->getLocalPosition().y == save_mapsPanel->getSize().y && InputManager::scroll.y < 0;

                if (!check_1 && !check_2)
                {
                    for (auto &tile : save_mapsUI)
                    {
                        tile->setPosition(tile->getLocalPosition().x, tile->getLocalPosition().y + InputManager::scroll.y * 20);
                    }
                }
            }
            InputManager::scrollYPressed = false;
        }
        if (loadPanel->isEnable() && load_mapsPanel->isScrollable())
        {
            if (!load_mapsUI.empty())
            {
                bool check_1 = load_mapsUI.at(0)->getLocalPosition().y == 0 && InputManager::scroll.y > 0;
                bool check_2 = load_mapsUI.at(load_mapsUI.size() - 1)->getLocalPosition().y == load_mapsPanel->getSize().y && InputManager::scroll.y < 0;

                if (!check_1 && !check_2)
                {
                    for (auto &tile : load_mapsUI)
                    {
                        tile->setPosition(tile->getLocalPosition().x, tile->getLocalPosition().y + InputManager::scroll.y * 20);
                    }
                }
            }
            InputManager::scrollYPressed = false;
        }
    }
}
void SaveLoadSystem::Render(SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer)
{
    savePanel->Draw(menuRenderer, squareRenderer);
    loadPanel->Draw(menuRenderer, squareRenderer);
    if (savePanel->isEnable())
    {
        if (!save_mapsUI.empty())
        {
            for (std::vector<int>::size_type i = 0; i != save_mapsUI.size(); i++)
            {
                save_mapsUI[i]->Draw(menuRenderer, squareRenderer);
            }
        }
    }
    if (loadPanel->isEnable())
    {
        if (!load_mapsUI.empty())
        {
            for (std::vector<int>::size_type i = 0; i != load_mapsUI.size(); i++)
            {
                load_mapsUI[i]->Draw(menuRenderer, squareRenderer);
            }
        }
    }
}

void SaveLoadSystem::SaveMap()
{
    if (!Editor::instance().tiles.empty() && !t_save->getText().empty())
    {
        
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<> *node_map = doc.allocate_node(rapidxml::node_element, "map");
        Logger::WriteLog("xml_node olusturuldu");
        //int i = 0;
        for (auto &tile : Editor::instance().tiles)
        {
            //Logger::WriteLog("tile: " + std::to_string(i) + "  basladi");
            rapidxml::xml_node<> *node_tile = doc.allocate_node(rapidxml::node_element, "tile");
            char *cellX = doc.allocate_string(std::to_string(tile.cell.x).c_str());
            char *cellY = doc.allocate_string(std::to_string(tile.cell.y).c_str());
            char *frame = doc.allocate_string(std::to_string(tile.button.getTile()->frame).c_str());
            char *type = doc.allocate_string(std::to_string((int)tile.button.getTile()->getType()).c_str());
            char *itemId = doc.allocate_string(std::to_string(tile.item.getId()).c_str());

            rapidxml::xml_node<> *node_tile_texture;

            node_tile_texture = doc.allocate_node(rapidxml::node_element, "tileTexture", frame);

            rapidxml::xml_node<> *node_cellX = doc.allocate_node(rapidxml::node_element, "cellX", cellX);
            rapidxml::xml_node<> *node_cellY = doc.allocate_node(rapidxml::node_element, "cellY", cellY);
            rapidxml::xml_node<> *node_tile_type = doc.allocate_node(rapidxml::node_element, "tileType", type);
            rapidxml::xml_node<> *node_item_id = doc.allocate_node(rapidxml::node_element, "itemID", itemId);

            node_tile->append_node(node_tile_texture);
            node_tile->append_node(node_cellX);
            node_tile->append_node(node_cellY);
            node_tile->append_node(node_tile_type);
            node_tile->append_node(node_item_id);
            node_map->append_node(node_tile);
            

            //delete[] cellX;
            //delete[] cellY;
            //delete[] frame;
            //delete[] type;
        }

        char *limitX = doc.allocate_string(std::to_string(Editor::instance().mapLimit.x).c_str());
        char *limitY = doc.allocate_string(std::to_string(Editor::instance().mapLimit.y).c_str());
        char *tile = doc.allocate_string(Editor::instance().currentTileSet.c_str());
        char *name = doc.allocate_string(t_save->getText().c_str());
        rapidxml::xml_node<> *node_info = doc.allocate_node(rapidxml::node_element, "info");
        rapidxml::xml_node<> *node_name = doc.allocate_node(rapidxml::node_element, "name", name);
        rapidxml::xml_node<> *node_tileset = doc.allocate_node(rapidxml::node_element, "tileSet", tile);
        rapidxml::xml_node<> *node_maplimitx = doc.allocate_node(rapidxml::node_element, "mapLimitX", limitX);
        rapidxml::xml_node<> *node_maplimity = doc.allocate_node(rapidxml::node_element, "mapLimitY", limitY);
        node_info->append_node(node_name);
        node_info->append_node(node_tileset);
        node_info->append_node(node_maplimitx);
        node_info->append_node(node_maplimity);
        doc.append_node(node_map);
        doc.append_node(node_info);
        std::ofstream fileC;
        std::string a("../resources/levels/" + t_save->getText() + ".xml");
        fileC.open(a.c_str());
        if (!fileC)
        {
            std::string str = a + "dosyasi acilamadi";
            Logger::DebugLog(str);
            Logger::WriteLog(str);
            exit(EXIT_FAILURE);
        }
        fileC << doc;
        fileC.close();
        delete[] limitX;
        delete[] limitY;
        delete[] name;
        delete[] tile;
        //delete[] node_map;
        savePanel->setEnable(false);
    }
}
void SaveLoadSystem::B_SaveMap()
{
    save_mapsUI.clear();
    save_mapsPanel->childs.clear();
    selectedMap = -1;

    std::vector<std::string> maps = getMapNames();

    for (std::vector<int>::size_type i = 0; i != maps.size(); i++)
    {
        Button *bt = new Button(maps[i], Vector2<float>(0.0F, static_cast<float>(i * 20)), Vector2<float>(save_mapsPanel->getSize().x, 20.0F), *Editor::instance().textRenderer, Vector3<float>(0.21F), Vector3<float>(0.58F), 1.0F);
        bt->setMouseClickColor(Vector3<float>(0.35F));
        bt->setMouseHoverColor(Vector3<float>(0.25F));
        bt->setLabelMouseHoverColor(Vector3<float>(1.0F));
        bt->setLabelClickColor(Vector3<float>(1.0F));
        bt->setOutline(false);
        bt->setParent(save_mapsPanel.get(), false);
        bt->independent = true;
        bt->center = false;
        save_mapsUI.push_back(std::make_shared<Button>(*bt));
    }
    this->savePanel->setEnable(true);
}

std::vector<ButtonTile> SaveLoadSystem::LoadMap(std::string mapName)
{
    std::vector<ButtonTile> tiles;

    InputManager::scroll.y = 0.0F;
    this->loadPanel->setEnable(false);

    mapName = "../resources/levels/" + mapName + ".xml";
    std::string codeString;
    std::ifstream fileC(mapName.c_str());
    if (!fileC)
    {
        std::string str = "dosya acilamadi: ";
        str += mapName.c_str();
        Logger::DebugLog(str);
        Logger::WriteLog(str);
        exit(EXIT_FAILURE);
    }

    std::stringstream fileStream;
    fileStream << fileC.rdbuf();
    fileC.close();
    codeString = fileStream.str();
    rapidxml::xml_document<> doc;
    char *codeChar = new char[codeString.length() + 1];
    strcpy(codeChar, codeString.c_str());
    doc.parse<0>(codeChar);
    this->t_save->setText(doc.first_node("info")->first_node("name")->value());
    Editor::instance().currentTileSet = doc.first_node("info")->first_node("tileSet")->value();
    char *mapx = doc.first_node("info")->first_node("mapLimitX")->value();
    char *mapy = doc.first_node("info")->first_node("mapLimitY")->value();
    Editor::instance().mapLimit.x = atoi(mapx);
    Editor::instance().mapLimit.y = atoi(mapy);
    rapidxml::xml_node<> *node = doc.first_node("map");
    //std::cout << node->first_node("tile")->first_node("cellX")->next_sibling()->name() << std::endl;
    int i = 0;
    for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
    {
        //std::cout << child->first_node("cellY")->value() << std::endl;
        //tile.SetSize(Vector2<float>(Game::Width / 26.5, Game::Width / 26.5));
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
        const Vector2<float> pos(Game_Parameters::SIZE_TILE * cellX, Game_Parameters::SIZE_TILE * cellY);
        const Vector2<float> size(Vector2<float>(Game_Parameters::SIZE_TILE, Game_Parameters::SIZE_TILE));
        const int xoffset = textureIndex % (ResourceManager::GetTexture(Editor::instance().currentTileSet).Width / 32);
        const int yoffset = textureIndex / (ResourceManager::GetTexture(Editor::instance().currentTileSet).Width / 32);
        const Sprite sprite = Sprite(ResourceManager::GetTexture(Editor::instance().currentTileSet), (xoffset)*32, yoffset * 32, 32, 32);
        Tile tile = Tile(pos, sprite, size, TileTypes(tileType), textureIndex);
        Button b = Button(tile);
        ButtonTile t = ButtonTile(itemId, b, Vector2<int>(cellX, cellY));
        tiles.push_back(t);

        delete[] x;
        delete[] y;
        delete[] tIndex;
        delete[] tType;
    }

    delete[] codeChar;
    delete[] mapx;
    delete[] mapy;

    return tiles;
}
void SaveLoadSystem::B_LoadMap()
{
    load_mapsUI.clear();
    load_mapsPanel->childs.clear();
    selectedMap = -1;

    std::vector<std::string> maps = getMapNames();

    for (std::vector<int>::size_type i = 0; i != maps.size(); i++)
    {
        Button *bt = new Button(maps[i], Vector2<float>(0.0F, static_cast<float>(i * 20)), Vector2<float>(load_mapsPanel->getSize().x, 20.0F), *Editor::instance().textRenderer, Vector3<float>(0.21F), Vector3<float>(0.58F), 1.0F);
        bt->setMouseClickColor(Vector3<float>(0.35F));
        bt->setMouseHoverColor(Vector3<float>(0.25F));
        bt->setLabelMouseHoverColor(Vector3<float>(1.0F));
        bt->setLabelClickColor(Vector3<float>(1.0F));
        bt->setOutline(false);
        bt->setParent(load_mapsPanel.get(), false);
        bt->independent = true;
        bt->center = false;
        load_mapsUI.push_back(std::make_shared<Button>(*bt));
    }
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

std::vector<std::string> SaveLoadSystem::getMapNames()
{
    std::vector<std::string> maps;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("../resources/levels")) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] == '.')
                continue;
            std::string mapName(ent->d_name);
            if (mapName.substr(mapName.size() - 4) == ".xml")
            {
                std::string a = mapName.substr(0, mapName.size() - 4);
                maps.push_back(a);
            }
        }
        closedir(dir);
        return maps;
    }
    else
    {
        perror("could not open directory");
    }
}