#ifndef _SRC_CORE_SCENE_MANAGER_H_
#define _SRC_CORE_SCENE_MANAGER_H_
#include <vector>
#include <memory>
#include "Scene.h"

namespace LightInDarkness
{
    class SceneManager
    {
    public:
        SceneManager(SceneManager const &) = delete;
        void operator=(SceneManager const &) = delete;

        static SceneManager &Get()
        {
            static SceneManager instance;

            return instance;
        }
        void PushScene(std::unique_ptr<Scene> scene)
        {
            scene->OnInit();
            m_scenes.emplace_back(scene);
        }
        void PopScene()
        {
            m_scenes.back()->OnShutdown();
            m_scenes.pop_back();
        }
        void ChangeScene(std::unique_ptr<Scene> scene)
        {
            m_scenes.back()->OnShutdown();
            m_scenes.pop_back();
            scene->OnInit();
            m_scenes.emplace_back(scene);
        }
        auto begin() { return m_scenes.begin(); }
        auto end() { return m_scenes.end(); }

    private:
        std::vector<std::unique_ptr<Scene>> m_scenes;

        ~SceneManager()
        {
        }
        SceneManager()
        {
        }
    };
}
#endif