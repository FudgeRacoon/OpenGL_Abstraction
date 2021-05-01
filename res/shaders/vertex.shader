#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 o_texCoord;

uniform mat4 u_transform;
uniform mat4 u_project;

void main()
{
    gl_Position = u_project * u_transform * vec4(pos, 1.0f);
    o_texCoord = texCoord;
};