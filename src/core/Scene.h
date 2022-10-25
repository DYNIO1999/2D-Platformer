#ifndef _SRC_CORE_SCENE_H_
#define _SRC_CORE_SCENE_H_

namespace DEngine{
class Scene
{    
public:
    virtual ~Scene(){
        
    }
    virtual void OnInit() =0;
    virtual void OnEvent() =0;
    virtual void OnUpdate(float dt) =0;
    virtual void OnShutdown() =0;
};
}

#endif

