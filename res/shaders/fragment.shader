#version 330 core

out vec4 color;
in vec2 o_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
    color = texture(u_texture, o_texCoord) * u_color; 
}