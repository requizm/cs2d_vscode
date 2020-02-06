#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Utils
{
public:
    Utils();
    virtual ~Utils();

    static glm::vec2 WorldToScreen(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 point);
    static glm::vec2 ScreenToWorld(glm::vec2 view, glm::vec2 point);
    static glm::ivec2 PositionToCell(glm::vec2 pos);
    static glm::vec2 CellToPosition(glm::ivec2 cell);
};

#endif