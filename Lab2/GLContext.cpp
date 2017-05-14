#include "stdafx.h"
#include "GLContext.h"


std::map<GLenum, int> GLContext::boundObjects;
bool GLContext::_initialized = false;

bool GLContext::IsInitialized()
{
	return _initialized;
}

void GLContext::Initialize(int& argc, char ** argv, Window wnd, void(*displayFunc)(void),  unsigned int displayMode)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(displayMode);
	glutInitWindowSize(wnd.Width, wnd.Height);
	glutInitWindowPosition(wnd.x, wnd.y);
	glutCreateWindow(argv[0]);
	/* установим черный фон */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, wnd.Width, wnd.Height);
	glutDisplayFunc(displayFunc);

	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR INITIALIZING GLEW: %s\n", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}
}
