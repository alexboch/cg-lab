#pragma once
#include <iostream>


#include <map>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <GL/GL.h>


struct Window {
	int Width;
	int Height;
	int x, y;
	char* Title;
	Window(int w,int h, int x, int y,char* title)
	{
		Width = w;
		Height = h;
		this->x = x;
		this->y = y;
		Title = new char[strlen(title)];
		strcpy(Title, title);

	}
};

class GLContext
{
private:
	static bool _initialized;
	GLContext() {};
	GLContext(const GLContext&);
	GLContext& operator =(GLContext&) {};
	~GLContext() {};

public:
	static bool IsInitialized();
	static void Initialize(int& argc, char ** argv, Window wnd,
		void(*displayFunc)(void), unsigned int displayMode = GLUT_DOUBLE | GLUT_RGB);
	static std::map<GLenum, int> boundObjects;
	
};

