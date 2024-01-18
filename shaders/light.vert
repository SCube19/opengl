#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 real_model;
uniform mat4 real_camera;

void main()
{
	gl_Position = real_camera * real_model * vec4(aPos, 1.0f);
}