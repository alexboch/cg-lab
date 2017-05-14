#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GLContext.h"
#include "Constants.h"
///<summary>
///Базовый абстрактный класс для объектов OpenGL
///</summary>
class GLObject
{	
	
protected:
	GLObject(GLenum glType=-1);//Защищенный конструктор необходим для конструирования производных обхектов
	GLuint id;
	GLenum type;
	void ProtectedBind();
public:
	GLuint getId() const;
	GLenum GetType();
	virtual ~GLObject();
};

