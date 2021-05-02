#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 o_texCoord;

uniform mat4 u_project;
uniform mat4 u_view;
uniform mat4 u_model;


void main()
{
    gl_Position = u_project * u_view * u_model * vec4(pos, 1.0f);
    o_texCoord = texCoord;
};