#include "CheckersScene.h"
#include "../input/Input.h"

namespace DEngine{

    float heuristic(float ai, float aj, float bi, float bj){
        return std::abs(ai-bi) +std::abs(aj-bj);
    }
    int find_index(int i, int j)
    {
        int index = ROW_SIZE * i + j;
        return index;
    }
    CheckersScene::CheckersScene()
    {
    }
    CheckersScene::~CheckersScene()
    {
    }

    void CheckersScene::OnInit()
    {

        auto &window = App::Get().GetWindow();
        auto [winWidth, winHeight] = window.GetWindowSize();
        m_camera.SetCamera((static_cast<float>(winWidth) / static_cast<float>(winHeight)), 10.0f);
        m_camera.SetCameraSpeed(20.0f);

        testShader = Shader::Create("../../resources/shaders/ColorShader.glsl");
        testTexture = Texture::Create("../../resources/textures/woodwall.png");
        spriteSheetTexture = Texture::Create("../../resources/textures/sheet.png");

        window.SetVSync(true);


        grid.start = find_index(0, 0);
        grid.end = find_index(4, 4);

        for (int i = 0; i < ROW_SIZE; i++)
        {
            for (int j = 0; j < COLUMN_SIZE; j++)
            {
                int index = find_index(i, j);
                grid.nodes[index].previous = -100;
                grid.nodes[index].i=i;
                grid.nodes[index].j=j;

                grid.nodes[index].Fcost=0.0f;
                grid.nodes[index].Hcost=0.0f;
                grid.nodes[index].Gcost=0.0f;
                if(i % 2 ==0 && j % 2 !=0 ){
                    grid.nodes[index].passable =false;
                }else{
                    grid.nodes[index].passable = true;
                }
                grid.nodes[index].ID = index;
                

                for (int i = 0; i < 4; i++)
                {
                    grid.nodes[index].neighbours[i] =-1;
                } 
                
                if(i<ROW_SIZE-1){
                grid.nodes[index].neighbours[0] = find_index(i+1,j);
                }
                if(i>0){
                grid.nodes[index].neighbours[1] = find_index(i-1,j);
                }
                if(j<COLUMN_SIZE-1){
                grid.nodes[index].neighbours[2] = find_index(i,j+1);
                }
                if(j>0){
                grid.nodes[index].neighbours[3] = find_index(i,j-1);
                }
            }
        }

        for(int i=0;i<GRID_SIZE;i++){
            openSet[i] =-100;
            closedSet[i] =-100;
        }

        openSet[0] = grid.start;
        openSetSize++;


        while( openSetSize>0){
            int winner =0;
            for(int i=0;i<openSetSize;i++){
                if(grid.nodes[openSet[i]].Fcost < grid.nodes[winner].Fcost){
                    winner = i;
                }
            }
            int current = openSet[winner];
            //APP_ERROR(current);
            if (current == grid.end){

                APP_ERROR("DONE!");
                //for(int x = 0 ;x<GRID_SIZE;x++){
                //    APP_ERROR(grid.nodes[x].previous);
                //}
                break;
            }else{
                

                //Remove
                openSet[openSetSize-1] =-1;
                openSetSize--;

                //Add
                closedSet[closedSetSize-1]=current;
                closedSetSize++;
                if(current==0){
                    closedSetSize--;
                }

                for(int i=0;i<4;i++){
                    int neighbour = grid.nodes[current].neighbours[i];
                    if(neighbour!=-1){
                 
                    bool foundInCloseSet = false;
                    for(int j = 0;j<closedSetSize;j++){
                        if(neighbour == closedSet[j]){
                            foundInCloseSet = true;
                        }
                    }
                    bool foundInOpenSet = false;
                    if(!foundInCloseSet){
                        float tempG = grid.nodes[current].Gcost+1.0f;

                        for(int k=0;k<openSetSize;k++){
                            if(openSet[k] == neighbour){
                                foundInOpenSet = true;
                            }
                        }

                        if(foundInOpenSet){
                            if(tempG<grid.nodes[neighbour].Gcost){

                                grid.nodes[neighbour].Gcost =tempG;;
                            }
                        }else{
                            grid.nodes[neighbour].Gcost = tempG;
                            openSetSize++;
                            openSet[openSetSize-1] = neighbour;
                        }

                        grid.nodes[neighbour].Hcost = heuristic(grid.nodes[neighbour].i, grid.nodes[neighbour].j, 4, 4);
                        grid.nodes[neighbour].Fcost = grid.nodes[neighbour].Gcost + grid.nodes[neighbour].Hcost;
                        grid.nodes[neighbour].previous =current;
                    }
                    }
                }

            }
        }

    }
    void CheckersScene::OnEvent()
    {
    }
    void CheckersScene::OnUpdate(float dt)
    {
        auto &window = App::Get().GetWindow();
        auto [width, height] = window.GetWindowSize();

        m_camera.OnUpdate(dt);
    
        Renderer::Clear(glm::vec4(0.7, 0.5, 0.3, 1.0f));
        Renderer::BeginScene(m_camera);

        for (int i = 0; i < ROW_SIZE; i++)
        {
           
            for (int j = 0; j < COLUMN_SIZE; j++)
            {
                int index = find_index(i, j);
               
                if (grid.nodes[index].passable)
                    Renderer::DrawRect({i * 1.5f, j * 1.5f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
                else
                    Renderer::DrawRect({i * 1.5f, j * 1.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});

                if (grid.start == index)
                {
                    Renderer::DrawRect({i * 1.5f, j * 1.5f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
                }
                if(grid.end == index){
                    Renderer::DrawRect({i * 1.5f, j * 1.5f}, {1.0f, 1.0f}, {1.0f, 0.5f, 0.0f, 1.0f});
                }
            }
        }
        
        Renderer::EndScene();
    }
    void CheckersScene::OnShutdown()
    {
        Renderer::Shutdown();
    }
}