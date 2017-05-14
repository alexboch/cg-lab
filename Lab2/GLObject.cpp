#include "stdafx.h"
#include "GLObject.h"




GLObject::GLObject(GLenum glType)
{
	
	type = glType;
}

GLuint GLObject::getId() const
{
	return id;
}

GLenum GLObject::GetType()
{
	return type;
}



GLObject::~GLObject()
{
}



