#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
out vec3 fragNormal;
out vec2 fragTexCoord;
out vec3 fragVert;
out vec4 fragPosLightSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    fragNormal=normal;
	fragVert=position;
	fragTexCoord = texCoords;
	fragPosLightSpace = lightSpaceMatrix * vec4(fragVert, 1.0);
}