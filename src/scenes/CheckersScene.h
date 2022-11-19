#ifndef _SRC_SCENES_CHECKERS_SCENE_H_
#define _SRC_SCENES_CHECKERS_SCENE_H_
#include "core/SceneManager.h"
#include "camera/OrtoCamera.h"
#include "renderer/Renderer.h"


namespace DEngine{


constexpr int ROW_SIZE =5;
constexpr int COLUMN_SIZE = 5;
constexpr int GRID_SIZE = ROW_SIZE * COLUMN_SIZE;

class CheckersScene: public Scene
{
private:
    
public:
    CheckersScene();
    ~CheckersScene();

    void OnInit() override;
    void OnEvent() override;
    void OnUpdate(float dt) override;
    void OnShutdown() override;

    std::shared_ptr<Shader> testShader;
    std::shared_ptr<Texture> testTexture;
    std::shared_ptr<Texture> spriteSheetTexture;

    OrtoCamera m_camera;

private:
};
}


#endif