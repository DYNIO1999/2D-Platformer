#include "CheckersScene.h"
#include "../input/Input.h"
#include <cmath>
namespace DEngine{
    int calculateDistance(int ax, int ay, int bx, int by){
        int dx = std::abs(ax - bx);
        int dy = std::abs(ay - by);
        if(dx>dy)
            return 14*dy+10*(dx-dy);
        return 14*dx+10*(dy-dx);
    }

    int calculateGCost(int ax, int ay, int bx, int by)
    {
        int dx = std::abs(ax - bx);
        int dy = std::abs(ay - by);
        if (dx > dy)
            return 14 * dy + 10 * (dx - dy);
        return 14 * dx + 10 * (dy - dx);
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
        m_camera.SetCamera((static_cast<float>(winWidth) / static_cast<float>(winHeight)), 7.0f);
        m_camera.SetCameraSpeed(20.0f);
        m_camera.SetPosition(glm::vec3(6.5f*m_camera.AspectRatio(),3.6f*m_camera.AspectRatio(),0.0f));
        

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
               

                for (int i = 0; i < 8; i++)
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

                if ((i < ROW_SIZE - 1) && (j < COLUMN_SIZE - 1))
                {
                    grid.nodes[index].neighbours[4] = find_index(i + 1, j+1);
                }

                if ((i < ROW_SIZE - 1) && (j>0))
                {
                    grid.nodes[index].neighbours[5] = find_index(i + 1, j - 1);
                }

                if ((i>0) && (j > 0))
                {
                    grid.nodes[index].neighbours[6] = find_index(i - 1, j - 1);
                }

                if ((i>0) && (j < COLUMN_SIZE - 1))
                {
                    grid.nodes[index].neighbours[7] = find_index(i - 1, j + 1);
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
        //m_camera.OnUpdate(dt);
        auto [x,y] = Input::GetMousePosition();
        int sizeX = ((width-75)/2)/ROW_SIZE;
        int sizeY = ((height+500)/2)/COLUMN_SIZE;
        
            
        if(Input::IsMouseButtonPressedOnce(GLFW_MOUSE_BUTTON_RIGHT)){
            int i =(int)x / sizeX;
            int j = std::abs((int)(y - height) / sizeY);
            grid.end = find_index(i, j);
           
            changed = !changed;
            done = false;
        }

        if(Input::IsKeyPressedOnce(GLFW_KEY_SPACE)){
            int i = (int)x / sizeX;
            int j = std::abs((int)(y - height) / sizeY);
        
            grid.nodes[find_index(i,j)].passable =!grid.nodes[find_index(i,j)].passable;
            path.clear();
        }

        if (Input::IsMouseButtonPressedOnce(GLFW_MOUSE_BUTTON_LEFT))
        {
            int i = (int)x / sizeX;
            int j = std::abs((int)(y - height) / sizeY);
            grid.start = find_index(i, j);
            path.clear();
        }

        if(changed && !done){
            APP_ERROR("WORKING");
            CalculatePathfinding();
        }    
        Renderer::Clear(glm::vec4(0.7, 0.5, 0.3, 1.0f));
        Renderer::BeginScene(m_camera);

        for (int i = 0; i < ROW_SIZE; i++)
        {

            for (int j = 0; j < COLUMN_SIZE; j++)
            {
                int index = find_index(i, j);

                if (grid.nodes[index].passable)
                    Renderer::DrawRect({i * 1.1f, j * 1.1f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
                else
                    Renderer::DrawRect({i * 1.1f, j * 1.1f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});

                if (grid.start == index)
                {
                    Renderer::DrawRect({i * 1.1f, j * 1.1f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
                }
                if (grid.end == index)
                {
                    Renderer::DrawRect({i * 1.1f, j * 1.1f}, {1.0f, 1.0f}, {1.0f, 0.5f, 0.0f, 1.0f});
                }
                for (auto &it : path)
                {
                    if(index ==it){
                        Renderer::DrawRect({i * 1.1f, j * 1.1f}, {1.0f, 1.0f}, {0.3f, 0.5f, 0.2f, 1.0f});   
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

            for (int i = 0; i < 8; i++)
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

                    int costToNeighbour = grid.nodes[currentNode].Gcost + calculateGCost(grid.nodes[currentNode].i, grid.nodes[currentNode].j, grid.nodes[neighbour].i, grid.nodes[neighbour].j);

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
        for (int i = 0; i < ROW_SIZE; i++)
        {
            for (int j = 0; j < COLUMN_SIZE; j++)
            {
                grid.nodes[find_index(i,j)].Fcost=0.0f;
                grid.nodes[find_index(i,j)].Gcost=0.0f;
                grid.nodes[find_index(i,j)].Hcost=0.0f;
                grid.nodes[find_index(i,j)].previous=-1;
            }
        }

        done =true;
    }
}