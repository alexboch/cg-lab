#pragma once
// GL Includes
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderProgram.h"

class Shadow 
{

protected:
	ShaderProgram* sProg;
	RECT projectionRect;//��� ��������������� ��������
	int zNear, zFar;//������� � ������� ��������� ��������
	int shadowWidth, shadowHeight;
	GLuint depthMapFBO;//����� ����� ��� ����� �������
	GLuint depthMap;
public:
	GLuint GetDepthMap();
	GLuint GetDepthMapFBO();
	Shadow();
	Shadow(int shadowWidth, int shadowHeight, RECT projectionRect, int zNear, int zFar);
	~Shadow();
};

