#version 330 core

uniform mat4 model;
uniform vec3 cameraPosition;

uniform sampler2D materialTex;
uniform sampler2D shadowMap;
uniform float materialShininess;
uniform vec3 materialSpecularColor;
uniform float materialAlpha;

uniform mat3 normalMatrix;

#define MAX_LIGHTS 10
uniform int numLights;//количество источников света
uniform struct Light {
   vec4 position;
   vec3 intensities; //a.k.a the color of the light
   float attenuation;
   float ambientCoefficient;
   float coneAngle;
   vec3 coneDirection;
   int lightType;
} allLights[MAX_LIGHTS];
const int POINT_LIGHT=0;
const int DIR_LIGHT=1;


in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;
in vec4 fragPosLightSpace;
in vec3 fragPos;
out vec4 finalColor;


float ShadowCalculation(vec4 fragPosLightSpace,vec3 lightPos)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

	//float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.009);
    // check whether current frag pos is in shadow
    //float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
   //keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
    shadow = 0.0f;
        
    return shadow;
}


vec3 ApplyLight(Light light, vec3 surfaceColor, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera) {
    vec3 surfaceToLight;
    float attenuation = 1.0;
    if(light.lightType==DIR_LIGHT) {
			//directional light
			surfaceToLight = normalize(light.position.xyz);
			attenuation = 1.0; //no attenuation for directional lights
		} 
		else 
		{
			//point light
			surfaceToLight = normalize(light.position.xyz - surfacePos);//направление от освещаемой поверхности к ист-ку света
			float distanceToLight = length(light.position.xyz - surfacePos); //distance from light source to surface
			attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));//rasseivaniye
		}

    //ambient
    vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.intensities;

    //diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;
    
    //specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
    vec3 specular = specularCoefficient * materialSpecularColor * light.intensities;
	//float shadow=ShadowCalculation(fragPosLightSpace,light.position.xyz);
	//float shadow=ShadowCalculation(fragPosLightSpace,vec3(0));
	float shadow=ShadowCalculation(fragPosLightSpace,light.position.xyz);
	//float shadow=0;
    //linear color (color before gamma correction)
    return ambient + attenuation*(1.0-shadow)*(diffuse + specular);
	
}




void main() {
    
	vec3 normal = normalize(normalMatrix * fragNormal);
    vec3 surfacePos = vec3(model * vec4(fragVert, 1.0));
    vec4 surfaceColor = texture(materialTex, fragTexCoord);
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);

    //combine color from all the lights
    vec3 linearColor = vec3(0);
    for(int i = 0; i < numLights; ++i){
        linearColor += ApplyLight(allLights[i], surfaceColor.rgb, normal, surfacePos, surfaceToCamera);
	}
    
    //final color (after gamma correction)
    vec3 gamma = vec3(1.0/2.2);
    finalColor = vec4(pow(linearColor, gamma), surfaceColor.a);
	finalColor=vec4(linearColor,materialAlpha);
	//finalColor=vec4(linearColor,surfaceColor.a);
	finalColor.a=materialAlpha;
}