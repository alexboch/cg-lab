#include "stdafx.h"
#include "ShaderProgram.h"


void ShaderProgram::ProtectedBind()
{
	glUseProgram(id);
}

void ShaderProgram::AttachShader(Shader& shader)
{
	glAttachShader(id, shader.getId());
	_shaders.push_back(shader);
}

void ShaderProgram::Link()
{
	glLinkProgram(id);
	GLint isLinked = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		GLchar* infoLog=new char[maxLength];
		glGetProgramInfoLog(id, maxLength, &maxLength, infoLog);

		//The program is useless now. So delete it.
		glDeleteProgram(id);

		//Provide the infolog in whatever manner you deem best.
		/*std::cerr << "Shader Program linking error:" << infoLog << std::endl;*/
		HandleErrorMessage("Shader Program linking error:", infoLog);
		delete[] infoLog;
		//Exit with failure.
		return;
	}
	_isLinked = true;
}

void ShaderProgram::HandleErrorMessage(std::string msg,const char* uniformName)
{
	if (std::find(_errUniforms.begin(), _errUniforms.end(), uniformName) != _errUniforms.end()) 
	{
		
	}
	else 
	{

		std::cerr << msg<<" "<<std::string(uniformName)<<std::endl;
		char* newChar = new char[strlen(uniformName)+1];
		strcpy(newChar, uniformName);
		//_errUniforms.push_back(std::string(uniformName));
			_errUniforms.insert(std::string(newChar));

	}
}

void ShaderProgram::Use()
{
	if(!_isLinked)
	Link();
	Bind();
}


void ShaderProgram::BindAttribLocation(GLint index, const GLchar * name)
{
	glBindAttribLocation(this->id, index, name);
	GLint err = glGetError();
	if (err != GL_NO_ERROR)
	{
		
		std::cerr << "Error binding attrib location " << err << std::endl;
		
	}
}

GLint ShaderProgram::GetAttribLocation(const GLchar * attributeName) const
{
	return glGetAttribLocation(id, attributeName);
}

GLint ShaderProgram::GetUniformLocation(const GLchar * uniformName)
{
	return glGetUniformLocation(id, uniformName);
}

void ShaderProgram::SetUniform(const GLchar * uniformName,GLfloat value)
{
	GLint uniformLoc = this->GetUniformLocation(uniformName);
	if (uniformLoc != -1)
		glUniform1f(uniformLoc, value);
	else //throw new std::runtime_error("Error setting float uniform value, name:" + std::string(uniformName));
		HandleErrorMessage("Error setting float uniform value, name:",uniformName);
}

void ShaderProgram::SetUniform(const GLchar * uniformName, GLint value)
{
	GLint uniformLoc = this->GetUniformLocation(uniformName);
	if (uniformLoc != -1)
		glUniform1i(uniformLoc, value);
	//else std::cerr << "Error setting int uniform value, name:"+ std::string(uniformName) << std::endl;
	else HandleErrorMessage("Error setting int uniform value, name:", uniformName);
}

void ShaderProgram::SetUniform(const GLchar * uniformName, glm::mat4 value)
{
	GLint uniformLoc = this->GetUniformLocation(uniformName);
	if (uniformLoc != -1)
		glUniformMatrix4fv(uniformLoc, 1,false, glm::value_ptr(value));
	else HandleErrorMessage("Error setting mat4 uniform value, name:", uniformName);
}

void ShaderProgram::SetUniform(const GLchar* uniformName, glm::mat3 value)
{
	GLint uniformLoc = this->GetUniformLocation(uniformName);
	if (uniformLoc != -1)
		glUniformMatrix3fv(uniformLoc, 1, false, glm::value_ptr(value));
	else HandleErrorMessage("Error setting mat3 uniform value, name:", uniformName);
}


void ShaderProgram::SetUniform(const GLchar * uniformName, glm::vec3 value)
{
	GLint uniformLoc = this->GetUniformLocation(uniformName);
	if (uniformLoc != -1)
		glUniform3fv(uniformLoc, 1, glm::value_ptr(value));
	else HandleErrorMessage("Error setting vec3 uniform value, name:", uniformName);
}

void ShaderProgram::SetUniform(const GLchar * uniformName, glm::vec4 value)
{
	GLint uniformLoc = this->GetUniformLocation(uniformName);
	if (uniformLoc != -1)
		glUniform4fv(uniformLoc, 1, glm::value_ptr(value));
	else HandleErrorMessage("Error setting vec4 uniform value, name:", uniformName);
}




const std::vector<Shader>& ShaderProgram::getShaders() const
{
	return _shaders;
}

ShaderProgram::ShaderProgram():BindableGLObject(GL_PROGRAM)
{
	id = glCreateProgram();
}


ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}
