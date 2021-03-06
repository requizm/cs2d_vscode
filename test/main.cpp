#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "../src/Core/Window.hpp"
#include "ResourceManager.hpp"
#include "../src/CS2D/Other/GameParameters.hpp"
#include "SquareRenderer.hpp"

#include "../tracy/Tracy.hpp"

class TestClass
{
public:
	TestClass()
	{
	}
	int a;

	void SetA(int a)
	{
		ZoneScoped;
		this->a = a;
	}
};

void initShader();
void TestFunc();

int main(int argc, char *argv[])
{
	GameParameters::LoadParameters();
	Window window("CS2D Test", GameParameters::SCREEN_WIDTH, GameParameters::SCREEN_HEIGHT);
	initShader();
	InputManager::InitKeyboardKeys();

	TestClass testClass;

	SquareRenderer renderer = SquareRenderer(true);

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		ZoneScopedN("mainLoop");
		InputManager::UpdateMouse(window.GetWindow());
		InputManager::UpdateKeyboard(window.GetWindow());
		//processinput
		//update
		TestFunc();
		testClass.SetA(2);

		window.Clear();
		renderer.ui_RenderEmptySquare(Vector2<int>(300, 300), Vector2<int>(300, 300), Vector3<float>(1.0F, 1.0F, 1.0F));

		window.Update();
		FrameMark;
	}
	window.Destroy();
	ResourceManager::Destroy();
	Logger::StopApp();
	return 0;
}

void initShader()
{
	ResourceManager::LoadShader(GameParameters::resDirectory + "shaders/textVertex.txt", GameParameters::resDirectory + "shaders/textFragment.txt", "", "text");
	ResourceManager::LoadShader(GameParameters::resDirectory + "shaders/spriteVertex.txt", GameParameters::resDirectory + "shaders/spriteFragment.txt", "", "sprite");
	ResourceManager::LoadShader(GameParameters::resDirectory + "shaders/spriteVertex.txt", GameParameters::resDirectory + "shaders/spriteFragment.txt", "", "menu");

	ResourceManager::GetShader("sprite").Use();
	ResourceManager::GetShader("sprite").SetInteger("image", 0);
	ResourceManager::GetShader("sprite").UnUse();
	ResourceManager::GetShader("menu").Use();
	ResourceManager::GetShader("menu").SetMatrix4("projection", Projection::ortho(0.0f, static_cast<float>(GameParameters::SCREEN_WIDTH), static_cast<float>(GameParameters::SCREEN_HEIGHT), 0.0f), GL_TRUE);
	ResourceManager::GetShader("menu").SetInteger("image", 0);
	ResourceManager::GetShader("menu").UnUse();
}

void TestFunc()
{
	ZoneScoped;
	int b = 2;
	int a = 5;
}