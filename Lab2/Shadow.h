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
	RECT projectionRect;//��� ��������������� ��������
	int zNear, zFar;//������� � ������� ��������� ��������
	int shadowWidth, shadowHeight;
	GLuint depthMapFBO;//����� ����� ��� ����� �������
	GLuint depthMap;
	glm::mat4 lightProjection;
	glm::mat4 lightView;
public:
	GLuint GetDepthMap();
	GLuint GetDepthMapFBO();
	//glm::mat4 GetLightView();
	/*���������� ������� � ����� ������*/
	void RenderToFramebuffer(glm::vec3 lightPos, ShaderProgram* depthShaderProg,
		Model* model,glm::mat4& lightSpaceMatrix,glm::mat4& modelMatrix);
	Shadow();
	Shadow(int shadowWidth, int shadowHeight, float left, float right,float top, float bottom,
		float zNear, float zFar);
	~Shadow();
};

