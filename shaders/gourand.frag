#version 460 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec4 shading[3];
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;

in vec4 color;

in vec4 fragPosLight;

// Gets the Texture Unit from the main function
uniform int real_texturePresent = 1;

uniform sampler2D real_texture0;

uniform sampler2D real_specular0;

uniform sampler2D shadowMap;

float shadowCalc(vec4 fragPosLightSpace, vec3 lightDir, vec3 normal)
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
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
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

void main()
{
	vec4 tex = real_texturePresent * texture(real_texture0, texCoord) - (real_texturePresent - 1) * color;
	vec4 specularTex = real_texturePresent * texture(real_specular0, texCoord).r - (real_texturePresent - 1) * color;
	
	float shadow = 0.0f;
	FragColor = clamp(tex * ((1.0 - shadow) * shading[0] + shading[1]) + specularTex * (1.0 - shadow) * shading[2], 0.0f, 1.0f);
}

