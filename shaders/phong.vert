#version 460 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec4 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
// Normals (not necessarily normalized)
layout (location = 3) in vec3 aNormal;


// Outputs the color for the Fragment Shader
out vec4 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the current position for the Fragment Shader
out vec3 crntPos;
// Outputs the fragment position of the light
#define NUM_LIGHTS 15
out vec4 fragPosLight[NUM_LIGHTS];

// Imports the camera matrix from the main function
uniform mat4 real_camera;
// Imports the model matrix from the main function
uniform mat4 real_model;

uniform mat4 real_lightProjection[NUM_LIGHTS];

void main()
{

	// calculates current position
	crntPos = vec3(real_model * vec4(aPos, 1.0f));
	// Outputs the positions/coordinates of all vertices
	gl_Position = real_camera * vec4(crntPos, 1.0);

	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;

	vec4 fragmentPositons[NUM_LIGHTS];
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		fragmentPositons[i] = real_lightProjection[i] * vec4(crntPos, 1.0f);
	}
	fragPosLight = fragmentPositons;
	// Assigns the normal from the Vertex Data to "Normal"
	mat3 normalMatrix = mat3(transpose(inverse((real_model))));
	Normal = normalize(normalMatrix * aNormal);
}