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
public:
	GLuint GetDepthMap();
	GLuint GetDepthMapFBO();
	/*���������� ������� � ����� ������*/
	void RenderToFramebuffer(glm::vec3 lightPos, ShaderProgram* depthShaderProg, Model* model);
	Shadow();
	Shadow(int shadowWidth, int shadowHeight, float left, float right,float top, float bottom,
		float zNear, float zFar);
	~Shadow();
};

