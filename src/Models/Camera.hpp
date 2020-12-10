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
	Vector2<float> view;

	Camera() : view(0, 0), height(0), width(0), needX(0), needY(0), cameraMatrix(Matrix4(1.0F)){};
	Camera(int width, int height, Vector2<float> pos = Vector2(0.0F))
	{
		needX = 0;
		needY = 0;
		view = pos;
		this->width = width;
		this->height = height;

		//cameraMatrix = glm::ortho(0.0f, static_cast<float>(width),
		//						  static_cast<float>(height), 0.0f, -1.0f, 1.0f);

		cameraMatrix = Projection::ortho(0.0f, static_cast<float>(width),
										   static_cast<float>(height), 0.0f, -1.0f, 1.0f);

		//matrix = Projection::translate(matrix, Vector3(150.0F, 150.0F, 0.0F));
		//cameraMatrix = glm::translate(cameraMatrix, glm::vec3(150.0F, 150.0F, 0.0F));

		//matrix = Projection::rotate(matrix, 0.5F, Vector3(0.0F, 0.F, 1.0F));
		//cameraMatrix = glm::rotate(cameraMatrix,  0.5F, glm::vec3(0.0F, 0.0F, 1.0F));

		/*matrix = Projection::scale(matrix, Vector3(1.5F, 0.6F, 0.0F));
		cameraMatrix = glm::scale(cameraMatrix, glm::vec3(1.5F, 0.6F, 0.0F));

		Logger::DebugLog(glm::to_string(cameraMatrix));

		Logger::DebugLog("ikinciye bakalim");
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Logger::DebugLog(std::to_string(matrix.Get(i + 1, j + 1)));
			}
		}
		bool b = true;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if(matrix.Get(i + 1, j + 1) != cameraMatrix[i][j])
				{
					b = false;
				}
			}
		}

		if(b)
			Logger::DebugLog("tamamen ayni!");
		else
		{
			Logger::DebugLog("farkli!");
		}*/
		

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

	void setPosition(Vector2<float> newPos)
	{
		needX = newPos.x - view.x;
		needY = newPos.y - view.y;
		needUpdate = true;
		view.x += needX;
		view.y += needY;

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