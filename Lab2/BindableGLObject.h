#pragma once
#include "GLObject.h"
#include "GLContext.h"
#include <map>
///<summary>
///Абстрактный базовый класс для объектов, привязываемых к контексту
///</summary>
class BindableGLObject :
	public GLObject
{

protected:
	
	BindableGLObject(GLenum type);
	///<summary>
	///Логика для привязки конкретного класса, переопределяется в производном классе
	///</summary>
	virtual void ProtectedBind() = 0;
	///<summary>

public:


	//virtual void ProtectedUnbind() = 0;

	///<summary>
	///Привязка к контексту
	///</summary>
	void Bind();

	void Unbind();

	virtual ~BindableGLObject();
};

