#pragma once
// GL Includes
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderProgram.h"
#include "Model.h"

class Shadow 
{

protected:
	RECT projectionRect;//дл€ ортографической проекции
	int zNear, zFar;//ближн€€ и дальн€€ плоскости проекции
	int shadowWidth, shadowHeight;
	GLuint depthMapFBO;//буфер кадра дл€ карты глубины
	GLuint depthMap;
	glm::mat4 lightProjection;
	glm::mat4 lightView;
public:
	GLuint GetDepthMap();
	GLuint GetDepthMapFBO();
	//glm::mat4 GetLightView();
	/*«аписывает глубину в буфер кадров*/
	void RenderToFramebuffer(glm::vec3 lightPos, ShaderProgram* depthShaderProg,
		Model* model,glm::mat4& lightSpaceMatrix,glm::mat4& modelMatrix);
	Shadow();
	Shadow(int shadowWidth, int shadowHeight, float left, float right,float top, float bottom,
		float zNear, float zFar);
	~Shadow();
};

