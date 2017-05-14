#include "stdafx.h"
#include "VertexShader.h"


VertexShader::VertexShader():Shader(GL_VERTEX_SHADER)
{
}

VertexShader::VertexShader(std::string filepath):Shader(GL_VERTEX_SHADER, filepath)
{}

VertexShader::~VertexShader()
{
}
