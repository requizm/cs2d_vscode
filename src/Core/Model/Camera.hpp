#ifndef CAMERA_H
#define CAMERA_H

#include "../Math/Matrix4.hpp"
#include "../Math/Vector2.hpp"


// An abstract camera class that processes input and calculates the
// corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
   public:
    Camera() = default;
    Camera(int width, int height, Vector2<int> pos = Vector2<int>(0));

    void setPosition(Vector2<int> newPos);

    Matrix4<float> cameraMatrix = Matrix4<float>(1.0F);
    Vector2<int> view = Vector2<int>(0);

   private:
    int height = 0;
    int width = 0;
    float needX = 0;
    float needY = 0;
};
#endif