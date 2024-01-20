#version 460 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec4 color[2];
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit from the main function
uniform sampler2D real_texture0;

uniform sampler2D real_specular1;

void main()
{
	FragColor = clamp(texture(real_texture0, texCoord) * color[0] + texture(real_specular1, texCoord).r * color[1], 0.0f, 1.0f);
}

