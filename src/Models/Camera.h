#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	float x, y;

	Camera() : x(0), y(0), height(0), width(0), needX(0), needY(0), cameraMatrix(glm::mat4(1.0f))
	{
	}
	;
	Camera(int width, int height, glm::vec2 pos = glm::vec2(0.0f))
	{
		needX = 0;
		needY = 0;
		x = pos.x;
		y = pos.y;
		this->width = width;
		this->height = height;

		cameraMatrix = glm::ortho(0.0f, static_cast<float>(width),
			static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	};
	bool asds = false;
	glm::mat4 cameraMatrix;
	bool needUpdate = false;
	void update()
	{
		if (needUpdate)
		{
			const glm::vec3 translation(-needX, -needY, 0.0f);

			cameraMatrix = glm::translate(cameraMatrix, translation);
			needUpdate = false;
		}
	}

	void incPosition(glm::vec2 newPos) const
	{
		/*needX = x - newPos.x;
		needY = y - newPos.y;
		needUpdate = true;*/
	}

	void setPosition(glm::vec2 newPos)
	{
		needX = newPos.x - x;
		needY = newPos.y - y;
		needUpdate = true;
		x += needX;
		y += needY;
	}

private:
	int height;
	int width;
	float needX;
	float needY;
};
#endif