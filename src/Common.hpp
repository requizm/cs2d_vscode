#ifndef _COMMON_H
#define _COMMON_H

#include "Core/Math/Vector2.cpp"
#include "Core/Math/Vector3.cpp"
#include "Core/Math/Matrix4.cpp"
#include "Core/Math/Projection.cpp"

#include "Models/GameObject.cpp"
#include "Models/Player.cpp"
#include "Models/Shader.cpp"
#include "Models/Sprite.cpp"
#include "Models/Map.cpp"
#include "Models/Tile.cpp"
#include "Models/Texture.cpp"
#include "Models/Camera.cpp"
#include "Models/Weapon.cpp"
#include "Models/Mag.cpp"

#include "Models/UI/Label.cpp"
#include "Models/UI/UIObject.cpp"
#include "Models/UI/Button.cpp"
#include "Models/UI/Square.cpp"
#include "Models/UI/Circle.cpp"
#include "Models/UI/TextBox.cpp"
#include "Models/UI/Outline.cpp"
#include "Models/UI/Panel.cpp"
#include "Models/UI/RadioButton.cpp"
#include "Models/UI/ListItem.cpp"

#include "Renderers/SpriteRenderer.cpp"
#include "Renderers/TextRenderer.cpp"
#include "Renderers/SquareRenderer.cpp"

#include "Managers/ResourceManager.cpp"
#include "Managers/InputManager.cpp"
#include "Managers/ObjectManager.cpp"
#include "Managers/Input/InputStructs.cpp"

#include "Others/Game_Parameters.cpp"
#include "Others/Logger.cpp"
#include "Others/Utils.cpp"
#include "Others/Timer.cpp"

#include "Scenes/StartGame.cpp"
#include "Scenes/Menu.cpp"
#include "Scenes/Editor/Editor.cpp"
#include "Scenes/Editor/SaveLoadSystem.cpp"
#include "Scenes/Editor/NewMapSystem.cpp"
#include "Scenes/Editor/ButtonTile.cpp"
#include "Scenes/Editor/Entities/Env_Item.cpp"

#include "Game.cpp"
#include "Window.cpp"

#endif