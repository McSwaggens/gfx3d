#version 440 core

layout(location = 0) in vec3 vertex;

out vec2 uv;

void main()
{
	gl_Position = vec4(vertex, 1);
	uv = (gl_Position.xy + 1) / 2;
}

