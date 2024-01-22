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
out vec4 shading[3];
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;

out vec4 color;

//trzeba policzyć w fragment shaderze
out vec4 fragPosLight;

// Imports the camera matrix from the main function
uniform mat4 real_camera;
// Imports the model matrix from the main function
uniform mat4 real_model;

uniform vec3 real_position;

uniform vec3 real_cameraPosition;

// light parameters
#define NUM_LIGHTS 20
uniform vec3 real_lightPosition[NUM_LIGHTS];
uniform vec4 real_lightColor[NUM_LIGHTS];
uniform uint real_lightType[NUM_LIGHTS];
uniform float real_lightIntensity[NUM_LIGHTS];
uniform vec2 real_lightFalloff[NUM_LIGHTS];
uniform vec3 real_lightDirection[NUM_LIGHTS];
uniform float real_lightInner[NUM_LIGHTS];
uniform float real_lightOuter[NUM_LIGHTS];

uniform mat4 lightProjection;

void pointLight(inout vec4 shading[3], vec3 crntPos, vec3 Normal, vec3 lightPosition, vec4 lightColor, float lightIntensity, vec2 lightFalloff)
{	
	vec3 lightVec = lightPosition - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float inten = lightIntensity / (lightFalloff.x * dist * dist + lightFalloff.y * dist + 1.0f);

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(real_cameraPosition - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	shading[0] += (ambient * lightColor);
	shading[1] += (diffuse * inten * lightColor);
	shading[2] += (specular * inten * lightColor);
}

void directionalLight(inout vec4 shading[3], vec3 crntPos, vec3 Normal, vec3 lightPosition, vec4 lightColor, float lightIntensity, vec3 lightDirection)
{
    // ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDir = -normalize(lightDirection);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(real_cameraPosition - crntPos);
	vec3 reflectionDirection = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	shading[0] += (ambient * lightColor);
	shading[1] += (diffuse * lightIntensity * lightColor);
	shading[2] += (specular * lightIntensity * lightColor);
}

void spotlightLight(inout vec4 shading[3], vec3 crntPos, vec3 Normal, vec3 lightPosition, vec4 lightColor, float lightIntensity, vec3 lightDirection, float inner, float outer)
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - crntPos);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(real_cameraPosition - crntPos);
	vec3 reflectionDirection = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;
	
	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(-lightDirection, lightDir);
	float inten = clamp((angle - outer) / (inner - outer), 0.0f, 1.0f);

	shading[0] += (ambient * lightColor);
	shading[1] += (diffuse * inten * lightColor);
	shading[2] += (specular * inten * lightColor);
}

void main()
{

	// calculates current position
	vec3 crntPos = vec3(real_model * vec4(aPos, 1.0f));
	// Outputs the positions/coordinates of all vertices
	gl_Position = real_camera * vec4(crntPos, 1.0);

	// Assigns the colors from the Vertex Data to "color"
	vec4 result[3] = vec4[](vec4(0.0f), vec4(0.0f), vec4(0.0f));
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	color = aColor;

	texCoord = aTex;
	// Assigns the normal from the Vertex Data to "Normal"
	mat3 normalMatrix = mat3(transpose(inverse((real_model))));
	vec3 Normal = normalize(normalMatrix * aNormal);

	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		switch(real_lightType[i])
		{
			case 0:
				directionalLight(
					result,
					crntPos,
					Normal,
					real_lightPosition[i],
					real_lightColor[i],
					real_lightIntensity[i],
					real_lightDirection[i]);
				break;
			case 1:
				spotlightLight(
					result,
					crntPos,
					Normal,
					real_lightPosition[i],
					real_lightColor[i],
					real_lightIntensity[i],
					real_lightDirection[i],
					real_lightInner[i],
					real_lightOuter[i]
				);
				break;
			case 2:
				pointLight(
					result,
					crntPos,
					Normal,
					real_lightPosition[i],
					real_lightColor[i],
					real_lightIntensity[i],
					real_lightFalloff[i]
				);
				break;
		}
	}
	shading = result;
}