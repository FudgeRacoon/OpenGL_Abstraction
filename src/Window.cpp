#include "Core/Window.h"

Window::Window(const char* name, uint32_t width, uint32_t height, uint32_t windowFlags, bool isFullScreen)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Failed to initialize SDL2" << '\n';
        return;
    }   

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_DisplayMode displayMode;
    if(isFullScreen)
    {
        SDL_GetCurrentDisplayMode(0, &displayMode);
        this->name = name;
        this->width = displayMode.w;
        this->height = displayMode.h;
    }
    else
    {
        this->name = name;
        this->width = width;
        this->height = height;
    }

    this->window = SDL_CreateWindow
    (
        name,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL | windowFlags
    );

    if(this->window == nullptr)
    {
        std::cerr << "Failed to create window" << '\n';
        return;
    }

    this->isRunning = true;
    this->context = SDL_GL_CreateContext(this->window);

    glewExperimental = GL_TRUE;

    if(glewInit() != 0)
    {
        std::cerr << "Failed to initialize glew" << '\n';
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        return;
    }

    SDL_GL_SetSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, this->width, this->height);
}
Window::~Window()
{
    this->isRunning = false;
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

uint32_t Window::GetWidth()
{
    return this->width;
}
uint32_t Window::GetHeight()
{
    return this->height;
}
SDL_Window* Window::GetWindow()
{
    return this->window;
}
SDL_GLContext Window::GetContext()
{
    return this->context;
}
bool Window::IsRunning()
{
    return this->isRunning;
}