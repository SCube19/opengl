#version 460 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D real_texture;

uniform sampler2D real_specular;

// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;

uniform vec3 real_cameraPosition;

void main()
{
	// ambient lighting
	float ambient = 0.30f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(real_cameraPosition - crntPos);
	vec3 reflection = reflect(-lightDirection, normal);
	float specularAmount = pow(max(dot(viewDirection, reflection), 0.0f), 16);
	float specular = specularStrength * specularAmount;

	// outputs final color
	FragColor = texture(real_texture, texCoord) * lightColor * (ambient + diffuse) + texture(real_specular, texCoord).r * specular;
}