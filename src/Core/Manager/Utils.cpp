#include "Utils.hpp"

int Utils::curIndex = 1;

Utils::Utils() {}

Utils::~Utils() = default;

Vector2<int> Utils::ScreenToWorld(Vector2<int> view, Vector2<int> point) {
    return (view + point);
}

Vector2<int> Utils::WorldToScreen(Vector2<int> view, Vector2<int> point) {
    Vector2<int> screen = Vector2<int>(GameParameters::SCREEN_WIDTH,
                                       GameParameters::SCREEN_HEIGHT);
    Vector2<int> res = screen - (view + screen - point);
    res.x = abs(res.x);
    res.y = abs(res.y);
    return res;
}

Vector2<int> Utils::PositionToCell(Vector2<int> pos) {
    if (pos.x >= 0 && pos.y >= 0) {
        return Vector2<int>(pos.x / GameParameters::SIZE_TILE,
                            pos.y / GameParameters::SIZE_TILE);
    }
    return Vector2<int>(-1, -1);  // gereksiz
}

Vector2<int> Utils::CellToPosition(Vector2<int> cell) {
    return Vector2<int>(cell.x * GameParameters::SIZE_TILE,
                        cell.y * GameParameters::SIZE_TILE);
}

int Utils::GenerateID() { return curIndex++; }

bool Utils::TryStringToInt(std::string s) {
    const char *sC = s.c_str();
    if (sC == NULL || *sC == '\0') return false;

    bool negate = (sC[0] == '-');
    if (*sC == '+' || *sC == '-') ++sC;

    if (*sC == '\0') return false;

    int result = 0;
    while (*sC) {
        if (*sC >= '0' && *sC <= '9') {
            result = result * 10 - (*sC - '0');  // assume negative number
        } else
            return false;
        ++sC;
    }
    return true;
}

int Utils::StringToInt(std::string s) {
    const char *sC = s.c_str();

    bool negate = (sC[0] == '-');
    if (*sC == '+' || *sC == '-') ++sC;

    int result = 0;
    while (*sC) {
        if (*sC >= '0' && *sC <= '9') {
            result = result * 10 - (*sC - '0');  // assume negative number
        } else
            return false;
        ++sC;
    }
    return negate ? result : -result;
}