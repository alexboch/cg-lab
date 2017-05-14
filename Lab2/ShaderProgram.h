#pragma once
#include "Shader.h"
#include "BindableGLObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <set>


class ShaderProgram:public BindableGLObject
{
private:
	std::vector<Shader> _shaders;
	//std::vector<std::string> _errUniforms;//имена неустановленных юниформов, чтобы вывод не повторялся
	std::set<std::string> _errUniforms;
	std::set<std::string> _errUniforms2;
	bool _isLinked = false;
	void HandleErrorMessage(std::string msg,const char* uniformName);
protected:
	void ProtectedBind();
public:
	void AttachShader(Shader& shader);
	void Link();
	void Use();
	void BindAttribLocation(GLint index, const GLchar* name);
	GLint GetAttribLocation(const GLchar* attributeName) const;
	GLint GetUniformLocation(const GLchar* uniformName);
	void SetUniform(const GLchar* uniformName,GLfloat value);
	void SetUniform(const GLchar* uniformName, GLint value);
	void SetUniform(const GLchar* uniformName, glm::mat4 value);
	void SetUniform(const GLchar* uniformName, glm::mat3 value);
	void SetUniform(const GLchar* uniformName, glm::vec3 value);
	void SetUniform(const GLchar* uniformName, glm::vec4 value);
	const std::vector<Shader>& getShaders() const;
	ShaderProgram();
	~ShaderProgram();
};

