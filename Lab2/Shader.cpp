#include "stdafx.h"
#include "Shader.h"


void Shader::ConstructShader(GLenum shaderType, const char * shaderSrc)
{
	id = glCreateShader(shaderType);
	SetShaderSrc(shaderSrc);

}

void Shader::LoadFromFile(std::string filepath)
{
	std::string shaderSrc = File::ReadToEnd(filepath);
	ConstructShader(type, shaderSrc.c_str());
}

Shader::Shader(GLenum shaderType, std::string filepath):Shader(shaderType)
{
	/*std::ifstream shaderFile(filepath, std::ios::in);
	if (shaderFile)
	{
		//чтение файла
		std::string contents;
		shaderFile.seekg(0, std::ios::end);
		contents.resize(shaderFile.tellg());
		shaderFile.seekg(0, std::ios::beg);
		shaderFile.read(&contents[0], contents.size());
		shaderFile.close();
		ConstructShader(shaderType, contents.c_str());
		return;
	}
	throw(errno);*/

	LoadFromFile(filepath);
}





void Shader::SetShaderSrc(const char * shaderSrc)
{
	glShaderSource(id, 1, &shaderSrc, NULL);
	glCompileShader(id);
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);//проверка
	if (success == GL_FALSE)//шейдер не скомпилировался
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		GLchar* infoLog = new GLchar[maxLength];
		glGetShaderInfoLog(id, maxLength, &maxLength, infoLog);
		std::cerr << "Shader compilation error:"  <<infoLog<<std::endl;
		glDeleteShader(id);
		id = 0;
		delete[] infoLog;
		return;
	}
}

Shader::Shader(GLenum shaderType):GLObject(shaderType)
{
	type = shaderType;
}




Shader::~Shader()
{
	glDeleteShader(id);
}
