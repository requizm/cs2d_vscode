#ifndef UTILS_H
#define UTILS_H

#include <vector>

#include "../Math/Vector2.hpp"


class Utils
{
   public:
    Utils() = default;
    ~Utils() = default;

    static Vector2<int> ScreenToWorld(const Vector2<int> &view, const Vector2<int> &point);
    static Vector2<int> WorldToScreen(const Vector2<int> &view, const Vector2<int> &point);
    static Vector2<int> PositionToCell(const Vector2<int> &pos);
    static Vector2<int> CellToPosition(const Vector2<int> &cell);
    static int GenerateID();
    static bool TryStringToInt(std::string &s);
    static int StringToInt(std::string &s);
    static std::vector<std::string> GetFileNames(const std::string &path);

    static int curIndex;
};

#endif