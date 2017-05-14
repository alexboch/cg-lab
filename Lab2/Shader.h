#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <SOIL.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "File.h"
#include "GLObject.h"

class Shader:public GLObject
{	
protected:
	GLenum type;
	void ConstructShader(GLenum shaderType, const char* shaderSrc);
	
	Shader(GLenum, std::string filepath);
	Shader(GLenum shaderType);
public:
	void SetShaderSrc(const char* shaderSrc);
	void LoadFromFile(std::string filepath);
	~Shader();
};

