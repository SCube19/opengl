#version 460 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
flat in vec4 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
flat in vec3 Normal;
// Imports the current position from the Vertex Shader
flat in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform int real_texturePresent = 1;

uniform sampler2D real_texture0;

uniform sampler2D real_specular0;

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

vec4 pointLight(vec3 lightPosition, vec4 lightColor, float lightIntensity, vec2 lightFalloff)
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

	vec4 tex = real_texturePresent * texture(real_texture0, texCoord) - (real_texturePresent - 1) * color;
	vec4 specularTex = real_texturePresent * texture(real_specular0, texCoord).r - (real_texturePresent - 1) * color;
	
	return (tex * (diffuse * inten + ambient) +  specularTex * specular * inten) * lightColor;
}

vec4 directionalLight(vec3 lightPosition, vec4 lightColor, float lightIntensity, vec3 lightDirection)
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

	vec4 tex = real_texturePresent * texture(real_texture0, texCoord) - (real_texturePresent - 1) * color;
	vec4 specularTex = real_texturePresent * texture(real_specular0, texCoord).r - (real_texturePresent - 1) * color;

	return (tex * (diffuse * lightIntensity + ambient) + specularTex * specular * lightIntensity) * lightColor;
}


vec4 spotlightLight(vec3 lightPosition, vec4 lightColor, float lightIntensity, vec3 lightDirection, float inner, float outer)
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

	vec4 tex = real_texturePresent * texture(real_texture0, texCoord) - (real_texturePresent - 1) * color;
	vec4 specularTex = real_texturePresent * texture(real_specular0, texCoord).r - (real_texturePresent - 1) * color;

	return (tex * (diffuse * inten + ambient) + specularTex * specular * inten) * lightColor;
}

void main()
{
	// outputs final color
	vec4 result = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		switch(real_lightType[i])
		{
			case 0:
				result += directionalLight(
					real_lightPosition[i],
					real_lightColor[i],
					real_lightIntensity[i],
					real_lightDirection[i]);
				break;
			case 1:
				result += spotlightLight(
					real_lightPosition[i],
					real_lightColor[i],
					real_lightIntensity[i],
					real_lightDirection[i],
					real_lightInner[i],
					real_lightOuter[i]
				);
				break;
			case 2:
				result += pointLight(
					real_lightPosition[i],
					real_lightColor[i],
					real_lightIntensity[i],
					real_lightFalloff[i]
				);
				break;
		}
	}
	FragColor = clamp(result, 0.0f, 1.0f);
}