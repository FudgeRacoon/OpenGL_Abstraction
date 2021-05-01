#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <stdint.h>
#include "SDL2/SDL.h"
#include "GL/glew.h"

class Window
{
private:
    const char* name;
    uint32_t width;
    uint32_t height;

private:
    SDL_Window* window;
    SDL_GLContext context;

private:
    bool isRunning;
    bool isFullscreen;

public:
    Window(const char* name, uint32_t width, uint32_t height, uint32_t windowFlags, bool isFullscreen);
    ~Window();

public:
    uint32_t GetWidth();
    uint32_t GetHeight();
    SDL_Window* GetWindow();
    SDL_GLContext GetContext();
    bool IsRunning();
};

#endif