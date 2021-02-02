#ifndef UTILS_H
#define UTILS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game_Parameters.hpp"
#include "../Core/Math/Vector2.hpp"
#include "../Core/Math/Vector2.hpp"

class Utils
{
public:
    Utils();
    virtual ~Utils();

    static Vector2<int> ScreenToWorld(Vector2<int> view, Vector2<int> point);
    static Vector2<int> PositionToCell(Vector2<int> pos);
    static Vector2<int> CellToPosition(Vector2<int> cell);
    static int GenerateID();
    static bool TryStringToInt(const char *s);
    static int StringToInt(const char *s);

    static int curIndex;
};

#endif