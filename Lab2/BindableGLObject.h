#pragma once
#include "GLObject.h"
#include "GLContext.h"
#include <map>
///<summary>
///����������� ������� ����� ��� ��������, ������������� � ���������
///</summary>
class BindableGLObject :
	public GLObject
{

protected:
	
	BindableGLObject(GLenum type);
	///<summary>
	///������ ��� �������� ����������� ������, ���������������� � ����������� ������
	///</summary>
	virtual void ProtectedBind() = 0;
	///<summary>

public:


	//virtual void ProtectedUnbind() = 0;

	///<summary>
	///�������� � ���������
	///</summary>
	void Bind();

	void Unbind();

	virtual ~BindableGLObject();
};

