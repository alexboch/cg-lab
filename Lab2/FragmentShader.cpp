#include "stdafx.h"
#include "FragmentShader.h"


FragmentShader::FragmentShader():Shader(GL_FRAGMENT_SHADER)
{

}

FragmentShader::FragmentShader(std::string filepath):Shader(GL_FRAGMENT_SHADER,filepath)
{
}

 

FragmentShader::~FragmentShader()
{
}
