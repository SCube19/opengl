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
uniform sampler2D real_texture0;

uniform sampler2D real_specular1;

// Gets the color of the light from the main function
uniform vec4 real_lightColor;
// Gets the position of the light from the main function
uniform vec3 real_lightPosition;

uniform vec3 real_cameraPosition;

// light parameters 
uniform uint real_lightType;
uniform float real_lightIntensity;
uniform vec2 real_lightFalloff;
uniform vec3 real_lightDirection;
uniform float real_lightInner;
uniform float real_lightOuter;

vec4 pointLight()
{	
	//fall-off
	vec3 lightVec = real_lightPosition - crntPos;
	float dist = length(lightVec);
	
	float a = real_lightFalloff.x;
	float b = real_lightFalloff.y;
	float falloff = real_lightIntensity / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.30f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//specular
	//later should be material shininess
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(real_cameraPosition - crntPos);
	vec3 reflection = reflect(-lightDirection, normal);
	
	//blinn
	vec3 halfway = normalize(viewDirection + lightDirection);

	float specularAmount = pow(max(dot(normal, halfway), 0.0f), 16);
	float specular = specularStrength * specularAmount;

	return texture(real_texture0, texCoord) * real_lightColor * (ambient + diffuse * falloff) 
	     + texture(real_specular1, texCoord).r * (falloff * specular);
}

vec4 directionalLight()
{
	// ambient lighting
	float ambient = 0.30f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = -normalize(real_lightDirection);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//specular
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(real_cameraPosition - crntPos);
	vec3 reflection = reflect(-lightDirection, normal);
	
	//blinn
	vec3 halfway = normalize(viewDirection + lightDirection);

	float specularAmount = pow(max(dot(normal, halfway), 0.0f), 16);
	float specular = specularStrength * specularAmount;

	return texture(real_texture0, texCoord) * real_lightColor * (ambient + diffuse * real_lightIntensity)
	     + texture(real_specular1, texCoord).r * (real_lightIntensity * specular);
}


vec4 spotlightLight()
{
	vec3 lightVec = real_lightPosition - crntPos;

	// ambient lighting
	float ambient = 0.30f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//specular
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(real_cameraPosition - crntPos);
	vec3 reflection = reflect(-lightDirection, normal);
	
	//blinn
	vec3 halfway = normalize(viewDirection + lightDirection);

	float specularAmount = pow(max(dot(normal, halfway), 0.0f), 16);
	float specular = specularStrength * specularAmount;

	float angle = dot(real_lightDirection, -lightDirection);
	float intensity =  clamp((angle - real_lightOuter) / (real_lightInner - real_lightOuter), 0.0f, 1.0f);

	return texture(real_texture0, texCoord) * real_lightColor * (ambient + diffuse * intensity) 
	    + texture(real_specular1, texCoord).r * (intensity * specular);
}

void main()
{
	// outputs final color
	FragColor = spotlightLight();
	// switch(real_lightType)
	// {
	// 	case 0:
	// 		FragColor = directionalLight();
	// 		break;
	// 	case 1:

	// 		break;
	// 	case 2:
	// 		FragColor = pointLight();
	// 		break;
	// }
}