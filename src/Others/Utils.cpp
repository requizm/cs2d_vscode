#include "Utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game_Parameters.h"

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

glm::vec2 Utils::ScreenToWorld(glm::vec2 view, glm::vec2 point)
{
    return (view + point);
}

glm::ivec2 Utils::PositionToCell(glm::vec2 pos)
{
    if (pos.x >= 0 && pos.y >= 0)
    {
        return glm::ivec2((int)pos.x / Game_Parameters::SIZE_TILE, (int)pos.y / Game_Parameters::SIZE_TILE);
    }
    return glm::ivec2(-1, -1); //gereksiz
}

glm::vec2 Utils::CellToPosition(glm::ivec2 cell)
{
    return glm::vec2((int)cell.x * Game_Parameters::SIZE_TILE, (int)cell.y * Game_Parameters::SIZE_TILE);
}