#ifndef RENDERER_H
#define RENDERER_H

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "Core/Window.h"
#include "Core/Mesh.h"
#include "Core/Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Renderer
{
public:
    void ClearBuffers();
    void SwapBuffers(Window* window);
    
public:
    void Render(Mesh& model, const Shader& shader);
};

#endif