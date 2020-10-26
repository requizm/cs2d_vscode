#include "Utils.h"
#include <GL/glew.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game_Parameters.h"
#include "../Core/Math/Vector2.h"

int Utils::curIndex = 1;

Utils::Utils()
{
}

Utils::~Utils() = default;

glm::vec2 Utils::WorldToScreen(glm::mat4 viewMatrix,
                               glm::mat4 projectionMatrix, glm::vec3 point)
{
    glm::mat4 mvpmatrix = projectionMatrix * viewMatrix;
    const float *pSource = (const float *)glm::value_ptr(mvpmatrix);
    glm::vec4 clipCoords;
    clipCoords.x = point.x * pSource[0] + point.y * pSource[4] + point.z * pSource[8] + pSource[12];
    clipCoords.y = point.x * pSource[1] + point.y * pSource[5] + point.z * pSource[9] + pSource[13];
    clipCoords.z = point.x * pSource[2] + point.y * pSource[6] + point.z * pSource[10] + pSource[14];
    clipCoords.w = point.x * pSource[3] + point.y * pSource[7] + point.z * pSource[11] + pSource[15];

    glm::vec3 normalizedDeviceCoordinates;
    normalizedDeviceCoordinates.x = clipCoords.x / clipCoords.w;
    normalizedDeviceCoordinates.y = clipCoords.y / clipCoords.w;
    normalizedDeviceCoordinates.z = clipCoords.z / clipCoords.w;

    GLint viewport[4] = {0};
    glGetIntegerv(GL_VIEWPORT, viewport); // viewport = (0, 0, width, height)
    glm::vec3 winPos;
    winPos.x = (viewport[2] / 2 * normalizedDeviceCoordinates.x) + (normalizedDeviceCoordinates.x + viewport[2] / 2);
    winPos.y = -(viewport[3] / 2 * normalizedDeviceCoordinates.y) + (normalizedDeviceCoordinates.y + viewport[3] / 2);
    winPos.z = 0;

    return winPos;
}

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