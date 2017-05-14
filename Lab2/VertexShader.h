#pragma once
#include "Shader.h"

///<summary>
///Вершинный шейдер
///</summary>
class VertexShader :
	public Shader
{
public:

	VertexShader();
	VertexShader(std::string filepath);
	~VertexShader();
};

