#include "Utils.hpp"
#include <GL/glew.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game_Parameters.hpp"
#include "../Core/Math/Vector2.hpp"

int Utils::curIndex = 1;

Utils::Utils()
{
}

Utils::~Utils() = default;


Vector2<float> Utils::ScreenToWorld(Vector2<float> view, Vector2<float> point)
{
    return (view + point);
}

Vector2<int> Utils::PositionToCell(Vector2<float> pos)
{
    if (pos.x >= 0 && pos.y >= 0)
    {
        return Vector2<int>((int)pos.x / Game_Parameters::SIZE_TILE, (int)pos.y / Game_Parameters::SIZE_TILE);
    }
    return Vector2<int>(-1, -1); //gereksiz
}

Vector2<float> Utils::CellToPosition(Vector2<int> cell)
{
    return Vector2<float>((int)cell.x * Game_Parameters::SIZE_TILE, (int)cell.y * Game_Parameters::SIZE_TILE);
}

int Utils::GenerateID()
{
    return curIndex++;
}

bool Utils::TryStringToInt(char const *s)
{
    if (s == NULL || *s == '\0')
        return false;

    bool negate = (s[0] == '-');
    if (*s == '+' || *s == '-')
        ++s;

    if (*s == '\0')
        return false;

    int result = 0;
    while (*s)
    {
        if (*s >= '0' && *s <= '9')
        {
            result = result * 10 - (*s - '0'); //assume negative number
        }
        else
            return false;
        ++s;
    }
    return true;
}

int Utils::StringToInt(char const *s)
{
    bool negate = (s[0] == '-');
    if (*s == '+' || *s == '-')
        ++s;

    int result = 0;
    while (*s)
    {
        if (*s >= '0' && *s <= '9')
        {
            result = result * 10 - (*s - '0'); //assume negative number
        }
        else
            return false;
        ++s;
    }
    return negate ? result : -result;
}