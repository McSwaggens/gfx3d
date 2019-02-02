#version 440 core

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec4 color;

uniform mat4 u_proj;

out vec4 p_color;

void main()
{
	p_color = color;
	gl_Position = u_proj * vertex;
}

