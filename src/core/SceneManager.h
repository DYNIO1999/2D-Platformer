#ifndef _SRC_CORE_SCENE_MANAGER_H_
#define _SRC_CORE_SCENE_MANAGER_H_
#include <vector>
#include <memory>
#include "Scene.h"

namespace DEngine
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
        void PushScene(std::shared_ptr<Scene> &&scene)
        {
            scene->OnInit();
            m_scenes.emplace_back(std::move(scene));
        }
        void PopScene()
        {
            m_scenes.back()->OnShutdown();
            m_scenes.pop_back();
        }
        void ChangeScene(std::shared_ptr<Scene> &&scene)
        {
            m_scenes.back()->OnShutdown();
            m_scenes.pop_back();
            scene->OnInit();
            m_scenes.emplace_back(std::move(scene));
        }
        auto begin() { return m_scenes.begin(); }
        auto end() { return m_scenes.end(); }
        auto Current() const{
            return m_scenes.back();
        }

        auto IsEmpty() const
        {
            return m_scenes.empty();
        }
    private:
        std::vector<std::shared_ptr<Scene>> m_scenes;

        ~SceneManager()
        {
        }
        SceneManager()
        {
        }
    };
}
#endif