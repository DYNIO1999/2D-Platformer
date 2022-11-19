#include "CheckersScene.h"
#include "../input/Input.h"

namespace DEngine{
    int calculateDistance(int ax, int ay, int bx, int by){
        return ((bx-ax)*(bx-ax)) + ((by-ay)*(by-ay));
    }
    int find_index(int i, int j){
        return (ROW_SIZE*i)+j; 
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
                grid.nodes[index].previous = -1;
                grid.nodes[index].i = i;
                grid.nodes[index].j = j;
                grid.nodes[index].ID = index;
                
                grid.nodes[index].Fcost = 0.0f;
                grid.nodes[index].Hcost = 0.0f;
                grid.nodes[index].Gcost = 0.0f;
                
                if (i % 2 == 0 && j % 2 != 0)
                {
                    grid.nodes[index].passable = false;
                }
                else
                {
                    grid.nodes[index].passable = true;
                }
               

                for (int i = 0; i < 4; i++)
                {
                    grid.nodes[index].neighbours[i] = -1;
                }

                if (i < ROW_SIZE - 1)
                {
                    grid.nodes[index].neighbours[0] = find_index(i + 1, j);
                }
                if (i > 0)
                {
                    grid.nodes[index].neighbours[1] = find_index(i - 1, j);
                }
                if (j < COLUMN_SIZE - 1)
                {
                    grid.nodes[index].neighbours[2] = find_index(i, j + 1);
                }
                if (j > 0)
                {
                    grid.nodes[index].neighbours[3] = find_index(i, j - 1);
                }
            }
        }
        //Pathfinding
    }   
    void CheckersScene::OnEvent()
    {


    }
    void CheckersScene::OnUpdate(float dt)
    {
        auto &window = App::Get().GetWindow();
        auto [width, height] = window.GetWindowSize();
        m_camera.OnUpdate(dt);
        if (Input::IsKeyPressedOnce(GLFW_KEY_P))
        {
            grid.start = find_index(0, 0);
            grid.end = find_index(4, 2);
            changed= !changed;
            done = false;
        }
        if(Input::IsKeyPressedOnce(GLFW_KEY_Q)){
            grid.start = find_index(0, 0);
            grid.end = find_index(1, 4);
            changed= !changed;
            done = false;
        }
        if(changed && !done)
            CalculatePathfinding();    
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
                if (grid.end == index)
                {
                    Renderer::DrawRect({i * 1.5f, j * 1.5f}, {1.0f, 1.0f}, {1.0f, 0.5f, 0.0f, 1.0f});
                }

                for (auto &it : path)
                {
                    if(index ==it){
                        Renderer::DrawRect({i * 1.5f, j * 1.5f}, {1.0f, 1.0f}, {0.3f, 0.5f, 0.2f, 1.0f});   
                    }
                }
                
            }
        }

        Renderer::EndScene();
    }
    void CheckersScene::OnShutdown()
    {
        Renderer::Shutdown();
    }
    void CheckersScene::CalculatePathfinding()
    {

        std::vector<int> toSearchNodes = {grid.start};
        std::vector<int> processedNodes;

        while (!toSearchNodes.empty())
        {
            int currentNode = toSearchNodes[0];
            for (size_t i = 0; i < toSearchNodes.size(); i++)
            {
                if ((grid.nodes[toSearchNodes[i]].Fcost < grid.nodes[currentNode].Fcost) && (grid.nodes[toSearchNodes[i]].Hcost < grid.nodes[currentNode].Hcost))
                {
                    currentNode = toSearchNodes[i];
                }
            }

            auto toBeRemoved = std::find(toSearchNodes.begin(), toSearchNodes.end(), currentNode);
            toSearchNodes.erase(toBeRemoved);
            processedNodes.push_back(currentNode);

            if (currentNode == grid.end)
            {
                path.clear();
                int currentIDBack = grid.end;

                while ((currentIDBack != -1) && (currentIDBack != grid.start))
                {
                    path.push_back(currentIDBack);
                    currentIDBack = grid.nodes[currentIDBack].previous;
                }
                path.erase(path.begin());
                break;
            }

            for (int i = 0; i < 4; i++)
            {
                int neighbour = grid.nodes[currentNode].neighbours[i];

                bool foundInProcessed = false;
                auto checkProcessed = std::find(processedNodes.begin(), processedNodes.end(), neighbour);
                if (checkProcessed != processedNodes.end())
                {
                    foundInProcessed = true;
                }

                if ((neighbour != -1) && (!foundInProcessed) && grid.nodes[neighbour].passable)
                {

                    int costToNeighbour = grid.nodes[currentNode].Gcost + 1;

                    bool found = false;
                    auto check = std::find(toSearchNodes.begin(), toSearchNodes.end(), neighbour);
                    if (check != toSearchNodes.end())
                    {
                        found = true;
                    }

                    if ((costToNeighbour < grid.nodes[neighbour].Gcost) || (!found))
                    {
                        grid.nodes[neighbour].Gcost = costToNeighbour;
                        grid.nodes[neighbour].previous = currentNode;
                        grid.nodes[neighbour].Hcost = calculateDistance(grid.nodes[neighbour].i, grid.nodes[neighbour].j, grid.nodes[grid.end].i, grid.nodes[grid.end].j);
                        grid.nodes[neighbour].Fcost = grid.nodes[neighbour].Gcost + grid.nodes[neighbour].Hcost;

                        if (!found)
                        {
                            toSearchNodes.push_back(neighbour);
                        }
                    }
                }
            }
        }
        //

        std::reverse(path.begin(), path.end());
        done =true;
    }
}