#version 460 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec4 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the fragment position of the light
#define NUM_LIGHTS 15
in vec4 fragPosLight[NUM_LIGHTS];

// Gets the Texture Unit from the main function
uniform int real_lastLight;

uniform int real_texturePresent = 1;

uniform sampler2D real_texture0;

uniform sampler2D real_specular0;

uniform sampler2D real_shadowMap[NUM_LIGHTS];

uniform samplerCube real_shadowCubeMap0;
uniform samplerCube real_shadowCubeMap1;
uniform samplerCube real_shadowCubeMap2;
uniform samplerCube real_shadowCubeMap3;
uniform samplerCube real_shadowCubeMap4;
uniform samplerCube real_shadowCubeMap5;
uniform samplerCube real_shadowCubeMap6;
uniform samplerCube real_shadowCubeMap7;
uniform samplerCube real_shadowCubeMap8;
uniform samplerCube real_shadowCubeMap9;
uniform samplerCube real_shadowCubeMap10;
uniform samplerCube real_shadowCubeMap11;
uniform samplerCube real_shadowCubeMap12;
uniform samplerCube real_shadowCubeMap13;
uniform samplerCube real_shadowCubeMap14;

uniform float real_far;

uniform vec3 real_cameraPosition;

// light parameters
uniform vec3 real_lightPosition[NUM_LIGHTS];
uniform vec4 real_lightColor[NUM_LIGHTS];
uniform uint real_lightType[NUM_LIGHTS];
uniform float real_lightIntensity[NUM_LIGHTS];
uniform vec2 real_lightFalloff[NUM_LIGHTS];
uniform vec3 real_lightDirection[NUM_LIGHTS];
uniform float real_lightInner[NUM_LIGHTS];
uniform float real_lightOuter[NUM_LIGHTS];

vec3 sampleOffsetDirections[20] = vec3[]
(
   vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
   vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
   vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
   vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
   vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);   

float shadowCalc(vec4 fragPosLightSpace, vec3 lightDir, vec3 normal, float biasValue, sampler2D shadowMap)
{

	// perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
	if(projCoords.z > 1.0) 
		return 0;
	
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
	float bias = max(biasValue * (1.0 - dot(normal, lightDir)), biasValue / 10);
    float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 9.0;

    return shadow;
}

float shadowCalcPoint(vec3 lightPos, samplerCube cubeMap) 
{
	// get vector between fragment position and light position
    vec3 fragToLight = crntPos - lightPos;
    // use the light to fragment vector to sample from the depth map    
    float closestDepth = texture(cubeMap, fragToLight).r;
    // it is currently in linear range between [0,1]. Re-transform back to original value
    closestDepth *= real_far;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // now test for shadows
	float shadow = 0.0;
	float bias   = 0.15;
	int  samples  = 20;
	float viewDistance = length(real_cameraPosition - crntPos);
	float diskRadius = (1.0 + (viewDistance / real_far)) / 25.0;
	for(int i = 0; i < samples; ++i)
	{
		float closestDepth = texture(cubeMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
		closestDepth *= real_far;   // undo mapping [0;1]
		if(currentDepth - bias > closestDepth)
			shadow += 1.0;
	}
	shadow /= float(samples);  

    return shadow;

}


vec4 pointLight(vec3 lightPosition, vec4 lightColor, float lightIntensity, vec2 lightFalloff, int index)
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
	
	float shadow = shadowCalcPoint(lightPosition, real_shadowCubeMap0);
	
	return (tex * ((1.0 - shadow) * diffuse * inten + ambient) +  specularTex * specular * inten * (1.0 - shadow)) * lightColor;
}

vec4 directionalLight(vec3 lightPosition, vec4 lightColor, float lightIntensity, vec3 lightDirection, vec4 fragPosLight, sampler2D shadowMap)
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
	
	float shadow = shadowCalc(fragPosLight, lightDir, normal, 0.05, shadowMap);

	vec4 tex = real_texturePresent * texture(real_texture0, texCoord) - (real_texturePresent - 1) * color;
	vec4 specularTex = real_texturePresent * texture(real_specular0, texCoord).r - (real_texturePresent - 1) * color;

	return (tex * ((1.0 - shadow) * diffuse * lightIntensity + ambient) + specularTex * specular * lightIntensity * (1.0 - shadow)) * lightColor;
}


vec4 spotlightLight(vec3 lightPosition, vec4 lightColor, float lightIntensity, vec3 lightDirection, float inner, float outer, vec4 fragPosLight, sampler2D shadowMap)
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
	
	float shadow = shadowCalc(fragPosLight, lightDir, normal, 0.005f, shadowMap);

	vec4 tex = real_texturePresent * texture(real_texture0, texCoord) - (real_texturePresent - 1) * color;
	vec4 specularTex = real_texturePresent * texture(real_specular0, texCoord).r - (real_texturePresent - 1) * color;

	return (tex * ((1.0 - shadow) * diffuse * inten + ambient) + specularTex * specular * inten * (1.0 - shadow)) * lightColor;
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
					real_lightDirection[i],
					fragPosLight[i],
					real_shadowMap[i]);
				break;
			case 1:
				result += spotlightLight(
					real_lightPosition[i],
					real_lightColor[i],
					real_lightIntensity[i],
					real_lightDirection[i],
					real_lightInner[i],
					real_lightOuter[i],
					fragPosLight[i],
					real_shadowMap[i]
				);
				break;
			case 2:
				result += pointLight(
					real_lightPosition[i],
					real_lightColor[i],
					real_lightIntensity[i],
					real_lightFalloff[i],
					i
				);
				break;
		}
	}
	FragColor = result;
}