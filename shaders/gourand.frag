#version 460 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the color from the Vertex Shader
in vec4 shading[2];
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;

in vec4 color;

// Gets the Texture Unit from the main function
uniform int real_texturePresent = 1;

uniform sampler2D real_texture0;

uniform sampler2D real_specular0;

void main()
{
	vec4 tex = real_texturePresent * texture(real_texture0, texCoord) - (real_texturePresent - 1) * color;
	vec4 specularTex = real_texturePresent * texture(real_specular0, texCoord).r - (real_texturePresent - 1) * color;
	FragColor = clamp(tex * shading[0] + specularTex * shading[1], 0.0f, 1.0f);
}