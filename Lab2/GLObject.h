#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GLContext.h"
#include "Constants.h"
///<summary>
///������� ����������� ����� ��� �������� OpenGL
///</summary>
class GLObject
{	
	
protected:
	GLObject(GLenum glType=-1);//���������� ����������� ��������� ��� ��������������� ����������� ��������
	GLuint id;
	GLenum type;
	void ProtectedBind();
public:
	GLuint getId() const;
	GLenum GetType();
	virtual ~GLObject();
};

