#include "Camera.hpp"

#include "../Math/Projection.hpp"

Camera::Camera(int width, int height, Vector2<int> pos)
{
    view = pos;
    this->width = width;
    this->height = height;

    cameraMatrix =
        Projection::ortho(0.0f, static_cast<float>(width),
                          static_cast<float>(height), 0.0f, -1.0f, 1.0f);
};

void Camera::setPosition(Vector2<int> newPos)
{
    needX = static_cast<float>(newPos.x - view.x);
    needY = static_cast<float>(newPos.y - view.y);
    view.x += static_cast<int>(needX);
    view.y += static_cast<int>(needY);


    const Vector3<float> translation(-needX, -needY, 0.0F);
    cameraMatrix = Projection::translate(cameraMatrix, translation);
}
