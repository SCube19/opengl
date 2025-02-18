#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 real_model;

void main()
{
    gl_Position = real_model * vec4(aPos, 1.0);
}