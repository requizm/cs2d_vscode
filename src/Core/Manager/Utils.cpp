#include "Utils.hpp"

#ifdef WIN32
#include <dirent/dirent.h>
#endif  // WIN32
#ifdef LINUX
#include <dirent.h>
#endif  // LINUX
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>

#include "../../CS2D/Other/GameParameters.hpp"
#include "../Manager/Logger.hpp"

int Utils::curIndex = 1;

Vector2<int> Utils::ScreenToWorld(const Vector2<int> &view, const Vector2<int> &point)
{
    Vector2<int> viewN = view;
    Vector2<int> pointN = point;
    return (viewN + pointN);
}

Vector2<int> Utils::WorldToScreen(const Vector2<int> &view, const Vector2<int> &point)
{
    Vector2<int> viewN = view;
    Vector2<int> pointN = point;
    Vector2<int> screen = Vector2<int>(GameParameters::SCREEN_WIDTH,
                                       GameParameters::SCREEN_HEIGHT);
    Vector2<int> res = screen - (viewN + screen - pointN);
    res.x = abs(res.x);
    res.y = abs(res.y);
    return res;
}

Vector2<int> Utils::PositionToCell(const Vector2<int> &pos)
{
    //ASSERT_ERROR(pos >= 0);
    float resX = static_cast<float>(pos.x) / static_cast<float>(GameParameters::SIZE_TILE);
    float resY = static_cast<float>(pos.y) / static_cast<float>(GameParameters::SIZE_TILE);
    if (resX < 0 && pos.x < GameParameters::SIZE_TILE)
    {
        resX = -1;
    }
    if (resY < 0 && pos.y < GameParameters::SIZE_TILE)
    {
        resY = -1;
    }
    return Vector2<int>(static_cast<int>(resX), static_cast<int>(resY));
}

Vector2<int> Utils::CellToPosition(const Vector2<int> &cell)
{
    //ASSERT_ERROR(cell >= 0);
    return Vector2<int>(cell.x * GameParameters::SIZE_TILE,
                        cell.y * GameParameters::SIZE_TILE);
}

int Utils::GenerateID() { return curIndex++; }

bool Utils::TryStringToInt(std::string &s)
{
    const char *sC = s.c_str();
    if (sC == NULL || *sC == '\0') return false;

    bool negate = (sC[0] == '-');
    if (*sC == '+' || *sC == '-') ++sC;

    if (*sC == '\0') return false;

    int result = 0;
    while (*sC)
    {
        if (*sC >= '0' && *sC <= '9')
        {
            result = result * 10 - (*sC - '0');  // assume negative number
        }
        else
            return false;
        ++sC;
    }
    return true;
}

int Utils::StringToInt(std::string &s)
{
    const char *sC = s.c_str();

    bool negate = (sC[0] == '-');
    if (*sC == '+' || *sC == '-') ++sC;

    int result = 0;
    while (*sC)
    {
        if (*sC >= '0' && *sC <= '9')
        {
            result = result * 10 - (*sC - '0');  // assume negative number
        }
        else
            return false;
        ++sC;
    }
    return negate ? result : -result;
}
std::vector<std::string> Utils::GetFileNames(const std::string &path)
{
    std::vector<std::string> maps;

    DIR *dir;
    struct dirent *ent;
    std::string str = path;
    if ((dir = opendir(str.c_str())) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] == '.') continue;
            std::string mapName(ent->d_name);
            if (mapName.substr(mapName.size() - 4) == ".xml")
            {
                std::string a = mapName.substr(0, mapName.size() - 4);
                maps.push_back(a);
            }
        }
        closedir(dir);
    }
    else
    {
        perror("could not open directory");
    }
    return maps;
}
