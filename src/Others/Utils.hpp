#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Utils
{
public:
    Utils();
    virtual ~Utils();

    static Vector2<float> ScreenToWorld(Vector2<float> view, Vector2<float> point);
    static Vector2<int> PositionToCell(Vector2<float> pos);
    static Vector2<float> CellToPosition(Vector2<int> cell);
    static int GenerateID();
    static bool TryStringToInt(const char *s);
    static int StringToInt(const char *s);

    static int curIndex;
};

#endif