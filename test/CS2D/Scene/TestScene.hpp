#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "../../../src/CS2D/Model/Scene.hpp"
#include "../../../src/Core/Renderer/SpriteRenderer.hpp"
#include "../../../src/Core/Renderer/SquareRenderer.hpp"
#include "../../../src/Core/Renderer/TextRenderer.hpp"
#include "../../Core/Renderer/BatchRenderer.hpp"

class TestScene : public Scene
{
   public:
    TestScene();
    ~TestScene() final;

    void Initialize();

    void Unload() final;
    void Load() final;
    void Update() final;
    void ProcessInput() final;
    void Render() final;

    TextRenderer *textRenderer;

    SpriteRenderer *menuRenderer;
    SquareRenderer *squareRenderer;
    BatchRenderer *batchRenderer;
};

#endif  // TESTSCENE_H