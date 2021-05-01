#include "Core/Renderer.h"

void Renderer::ClearBuffers()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::SwapBuffers(Window* window)
{
    SDL_GL_SwapWindow(window->GetWindow());
}

void Renderer::Render(Mesh& model, const Shader& shader)
{   
    VertexBuffer* vertexBuffer = model.GetVertexBuffer();
    
    shader.Bind();
    vertexBuffer->Bind();
    if(model.GetTexture())
        model.GetTexture()->Bind();

        glm::mat4 transform(1.0f);
        transform = glm::scale(transform, model.scale);
        transform = glm::translate(transform, model.position);
        transform = glm::rotate(transform, model.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, model.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, model.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        
        glm::mat4 projection = glm::perspective
        (
            glm::radians(45.0f), 
            800.0f / 600.0f,
            1.0f,
            100.0f   
        );
        
        shader.SetMat4f("u_transform", glm::value_ptr(transform));

        shader.SetMat4f("u_project", glm::value_ptr(projection));

        shader.SetVec4f("u_color", model.color.x, model.color.y, model.color.z, model.color.w);

        shader.SetInt("u_texture", 0);

        glDrawElements(GL_TRIANGLES, model.GetIndiciesCount(), GL_UNSIGNED_INT, 0);
    
    if(model.GetTexture())
        model.GetTexture()->UnBind();
    vertexBuffer->UnBind();
    shader.UnBind();
}