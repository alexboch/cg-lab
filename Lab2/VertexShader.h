#pragma once
#include "Shader.h"

///<summary>
///��������� ������
///</summary>
class VertexShader :
	public Shader
{
public:

	VertexShader();
	VertexShader(std::string filepath);
	~VertexShader();
};

