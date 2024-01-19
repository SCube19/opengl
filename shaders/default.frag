#version 460 core

out vec4 FragColor;

uniform vec4 real_color;

void main()
{
	FragColor = real_color;
}