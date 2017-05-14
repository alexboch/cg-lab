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
	RECT projectionRect;//дл€ ортографической проекции
	int zNear, zFar;//ближн€€ и дальн€€ плоскости проекции
	int shadowWidth, shadowHeight;
	GLuint depthMapFBO;//буфер кадра дл€ карты глубины
	GLuint depthMap;
public:
	GLuint GetDepthMap();
	GLuint GetDepthMapFBO();
	Shadow();
	Shadow(int shadowWidth, int shadowHeight, RECT projectionRect, int zNear, int zFar);
	~Shadow();
};

