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

int main(int argc, char* argv[])
{
    Window* window = new Window("OpenGL program", 800, 600, SDL_WINDOW_SHOWN, false);

    float squareVertices[] = 
    {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f
    };

    float squareTexCoordinates[] = 
    {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    unsigned int squareIndicies[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    Mesh square(squareVertices, sizeof(squareVertices), squareIndicies, sizeof(squareIndicies));
    square.AddTexture("res\\assets\\textures\\woodenCrate.png", squareTexCoordinates, sizeof(squareTexCoordinates));

    Renderer renderer;
    Shader shader("res\\shaders\\vertex.shader", "res\\shaders\\fragment.shader");


    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window->GetWindow(), window->GetContext());
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    while(window->IsRunning())
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                delete window;
        }
        
        renderer.ClearBuffers();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window->GetWindow());
        ImGui::NewFrame();

        square.position.z = -3.0f;

        renderer.Render(square, shader);


        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        renderer.SwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return EXIT_SUCCESS;
}