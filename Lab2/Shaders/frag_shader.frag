#version 330 core
uniform float materialShininess;//зеркальность
uniform vec3 materialSpecularColor;//цвет блика
uniform float materialAlpha;

struct Light {
    vec3 position;
	vec3 direction;//направление
	vec3 intensities;//цвет
    float ambientCoefficient;
    vec3 diffuse;
    vec3 specular;
};



in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor;

uniform sampler2D texture_diffuse1;

uniform mat4 model;
uniform mat3 normalMatrix;
uniform Light allLights[2];

void main()
{    
	//mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 normal = normalize(normalMatrix * fragNormal);
    vec4 surfaceColor=texture(texture_diffuse1,fragTexCoord);

	 //calculate the location of this fragment (pixel) in world coordinates
    vec3 fragPosition = vec3(model * vec4(fragVert, 1));
    
	for(int i=0;i<2;++i)
	{
		vec3 surfaceToLight = allLights[i].position - fragPosition;
		//calculate the cosine of the angle of incidence
		float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
		brightness = clamp(brightness, 0, 1);
		
		finalColor = vec4((brightness * allLights[i].intensities) * surfaceColor.rgb, surfaceColor.a);
	}
	//finalColor=surfaceColor;
	//прозрачность
	finalColor.a=materialAlpha;
	//color=vec4(fragNormal,alpha);
	//color.a=0.1;
}