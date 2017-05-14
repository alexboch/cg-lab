#include "stdafx.h"
#include "BindableGLObject.h"


BindableGLObject::BindableGLObject(GLenum type):GLObject(type)
{
}

void BindableGLObject::Bind()
{
	
	if (GLContext::boundObjects[type] != id)//���� ��� �� ���������
	{
		GLContext::boundObjects[type] = id;
		ProtectedBind();
	}
}

BindableGLObject::~BindableGLObject()
{
}
