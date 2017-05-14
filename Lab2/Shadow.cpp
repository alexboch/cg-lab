#include "Shadow.h"


GLuint Shadow::GetDepthMap()
{
	return depthMap;
}

GLuint Shadow::GetDepthMapFBO()
{
	return depthMapFBO;
}

Shadow::Shadow()
{
	
}

Shadow::Shadow(int shadowWidth,int shadowHeight,RECT projectionRect, int zNear, int zFar)
{
	this->projectionRect = projectionRect;
	this->shadowWidth = shadowWidth;
	this->shadowHeight = shadowHeight;
	this->zNear = zNear;
	this->zFar = zFar;
	glGenFramebuffers(1, &depthMapFBO);

	
	glGenTextures(1, &depthMap);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



Shadow::~Shadow()
{
}
