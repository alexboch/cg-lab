#pragma once
#include "Shader.h"
///<summary>
///����������� ������
///</summary>
class FragmentShader :
	public Shader
{
public:
	FragmentShader();
	FragmentShader(std::string filepath);
	~FragmentShader();
};

