#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <GL/glew.h>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "../src/Core/Manager/Logger.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no
// public constructor is defined.

typedef union PixelInfo
{
	std::uint32_t Colour;
	struct
	{
		std::uint8_t B, G, R, A;
	};
} * PPixelInfo;

class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;
	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader LoadShader(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile, std::string name);
	// Retrieves a stored sader
	static Shader GetShader(std::string name);
	// Loads (and generates) a texture from file
	static Texture2D LoadTexture(std::string file, GLboolean alpha, std::string name);
	// Retrieves a stored texture
	static Texture2D GetTexture(std::string name);
	// Properly de-allocates all loaded resources
	static void Destroy();

private:
	// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	ResourceManager() = default;
	// Loads and generates a shader from file
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	// Loads a single texture from file
	static Texture2D loadTextureFromFile(const char* file, GLboolean alpha);
};

#endif