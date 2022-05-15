#ifndef _SRC_SCENES_TEST_SCENE_H_
#define _SRC_SCENES_TEST_SCENE_H_
#include <iostream>

#include "core/SceneManager.h"

namespace LightInDarkness
{
    class TestScene : public Scene
    {
    public:
        TestScene();
        ~TestScene();

        void OnInit()override;
        void OnEvent() override;
        void OnUpdate(float dt) override;
        void OnShutdown() override;

    private:
    };
}
#endif
