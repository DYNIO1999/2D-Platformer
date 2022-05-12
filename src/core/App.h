#ifndef _SRC_CORE_APP_H
#define _SRC_CORE_APP_H

#include <iostream>

namespace LightInDarkness{
class App
{
public:
    App();
    ~App();
    void Run();

    static float GetDeltaTime(){return s_deltaTime;}
private:

    void OnEvent();
    void OnUpdate();
    
    void Initialize();
    void Shutdown();
    bool m_isRunning;
    static float s_deltaTime;
};
}
#endif