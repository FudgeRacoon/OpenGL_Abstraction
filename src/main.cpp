#include <iostream>

#include "glm/glm.hpp"
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_sdl.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/Shader.h"
#include "Core/VertexBuffer.h"
#include "Core/Mesh.h"
using namespace std;

SDL_Event event;

void ImGui_Init(Window* window)
{
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window->GetWindow(), window->GetContext());
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();
}
void ImGui_CreateNewFrame(Window* window)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window->GetWindow());
    ImGui::NewFrame();
}
void ImGui_Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void ImGui_ShutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

int main(int argc, char* argv[])
{
    Window* window = new Window("OpenGL program", 800, 600, SDL_WINDOW_SHOWN, false);

    float squareVertices[] = 
    {
        -1.0, -1.0,  1.0,
         1.0, -1.0,  1.0,
         1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        
        -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,
         1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0
    };

    float squareTexCoordinates[] = 
    {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f, 

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0
    };

    unsigned int squareIndicies[] = 
    {
       	// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
    };

    Mesh square(squareVertices, sizeof(squareVertices), squareIndicies, sizeof(squareIndicies));
    square.AddTexture("res\\assets\\textures\\woodenCrate.png", squareTexCoordinates, sizeof(squareTexCoordinates));

    Renderer renderer;
    Shader shader("res\\shaders\\vertex.shader", "res\\shaders\\fragment.shader");

    ImGui_Init(window);

    while(window->IsRunning())
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                delete window;
        }
        
        renderer.ClearBuffers();

        ImGui_CreateNewFrame(window);

        bool runAnimation;

        float counter = 0.0f;

        float position[3];
        float rotation[3];
        float scale[3];
        float color[3];

        ImGui::Begin("Transform Component");
            if(!runAnimation)
            {
                ImGui::SliderFloat3("Position", position, -10.0f, 10.0f);
                ImGui::SliderFloat3("Rotation", rotation, 0.0f, 360);
                ImGui::SliderFloat3("Scale", scale, 0.0f, 1.0f);
                ImGui::ColorEdit3("Color", color);
            }
            ImGui::Checkbox("Run Animation", &runAnimation);
        ImGui::End();
        
        if(!runAnimation)
        {
            square.position.x = position[0];
            square.position.y = position[1];
            square.position.z = position[2];

            square.rotation.x = rotation[0];
            square.rotation.y = rotation[1];
            square.rotation.z = rotation[2];

            square.scale.x = scale[0];
            square.scale.y = scale[1];
            square.scale.z = scale[2];

            square.color.x = color[0];
            square.color.y = color[1];
            square.color.z = color[2];
        }
        else
        {
            counter += 0.0005f;
            square.rotation += sin(counter);
        }
        
        renderer.Render(square, shader);
        
        ImGui_Render();

        renderer.SwapBuffers(window);
    }

    ImGui_ShutDown();

    return EXIT_SUCCESS;
}