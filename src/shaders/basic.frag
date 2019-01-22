#version 440 core

out vec4 color;
in vec2 uv;

void main()
{
	color = vec4(uv.x, 1-(uv.x * uv.y * 0.5 + 0.5), uv.y, 1);
}

