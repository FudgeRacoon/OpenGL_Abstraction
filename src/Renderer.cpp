#include "Core/Renderer.h"

void Renderer::ClearBuffers()
{
    glClearColor(0.15f, 0.27f, 0.31f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::SwapBuffers(Window* window)
{
    SDL_GL_SwapWindow(window->GetWindow());
}

void Renderer::Render(Mesh*& mesh, const Shader& shader)
{   
    VertexBuffer* vertexBuffer = mesh->GetVertexBuffer();
    
    shader.Bind();
    vertexBuffer->Bind();
    if(mesh->GetTexture())
        mesh->GetTexture()->Bind();

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        
        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 model(1.0f);
        model = glm::scale(model, mesh->scale);
        model = glm::translate(model, mesh->position);
        model = glm::rotate(model, mesh->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, mesh->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, mesh->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        
        shader.SetMat4f("u_project", glm::value_ptr(projection));

        shader.SetMat4f("u_view", glm::value_ptr(view));

        shader.SetMat4f("u_model", glm::value_ptr(model));

        shader.SetVec4f("u_color", mesh->color.x, mesh->color.y, mesh->color.z, mesh->color.w);

        shader.SetInt("u_texture", 0);

        glDrawElements(GL_TRIANGLES, mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0);
    
    if(mesh->GetTexture())
        mesh->GetTexture()->UnBind();
    vertexBuffer->UnBind();
    shader.UnBind();
}