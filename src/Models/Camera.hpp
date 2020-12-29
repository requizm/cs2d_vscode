#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Others/Logger.hpp"
#include "../Core/Math/Projection.hpp"
#include "../Core/Math/Vector2.hpp"
#include <../include/glm/gtx/string_cast.hpp>

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	Vector2<int> view;

	Camera() : view(0, 0), height(0), width(0), needX(0), needY(0), cameraMatrix(Matrix4(1.0F)){};
	Camera(int width, int height, Vector2<int> pos = Vector2(0))
	{
		needX = 0;
		needY = 0;
		view = pos;
		this->width = width;
		this->height = height;

		cameraMatrix = Projection::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	};
	Matrix4<float> cameraMatrix;

	void update()
	{
		if (needUpdate)
		{
			const Vector3 translation(-needX, -needY, 0.0f);

			cameraMatrix = Projection::translate(cameraMatrix, translation);
			needUpdate = false;
		}
	}

	void incPosition(Vector2<float> newPos) const
	{
		/*needX = x - newPos.x;
		needY = y - newPos.y;
		needUpdate = true;*/
	}

	void setPosition(Vector2<int> newPos)
	{
		needX = static_cast<float>(newPos.x - view.x);
		needY = static_cast<float>(newPos.y - view.y);
		needUpdate = true;
		view.x += static_cast<int>(needX);
		view.y += static_cast<int>(needY);

		update();
	}

private:
	bool needUpdate = false;
	int height;
	int width;
	float needX;
	float needY;
};
#endif