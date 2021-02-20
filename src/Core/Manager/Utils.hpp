#ifndef UTILS_H
#define UTILS_H

#include "../../CS2D/Other/GameParameters.hpp"
#include "../Math/Vector2.hpp"


class Utils
{
   public:
    Utils();
    virtual ~Utils();

    static Vector2<int> ScreenToWorld(Vector2<int> view, Vector2<int> point);
    static Vector2<int> WorldToScreen(Vector2<int> view, Vector2<int> point);
    static Vector2<int> PositionToCell(Vector2<int> pos);
    static Vector2<int> CellToPosition(Vector2<int> cell);
    static int GenerateID();
    static bool TryStringToInt(std::string s);
    static int StringToInt(std::string s);

    static int curIndex;
};

#endif