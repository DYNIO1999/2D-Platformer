#include "TestScene.h"

namespace LightInDarkness
{
    TestScene::TestScene(){

    }
    TestScene::~TestScene()
    {
    }

    void TestScene::OnInit(){

    }
    void TestScene::OnEvent(){

    }
    void TestScene::OnUpdate(float dt){

        std::cout<<dt<<'\n';
        std::cout<<"FROM TEST SCENE"<<"\n";
    }
    void TestScene::OnShutdown(){

    }
} 

