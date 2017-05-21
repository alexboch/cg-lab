#include "Shadow.h"


GLuint Shadow::GetDepthMap()
{
	return depthMap;
}

GLuint Shadow::GetDepthMapFBO()
{
	return depthMapFBO;
}




void Shadow::RenderToFramebuffer(glm::vec3 lightPos, ShaderProgram* depthShaderProg,
	Model* model, glm::mat4& lightSpaceMatrix,glm::mat4& modelMatrix)
{
	lightView = glm::lookAt(lightPos, glm::vec3(0.2f,0.0f,0.0f), glm::vec3(0.0, 1.0, 0.0));
	
	lightSpaceMatrix = lightProjection*lightView;
	depthShaderProg->Use();
	
	depthShaderProg->SetUniform(LSPACE_MATRIX, lightSpaceMatrix);
	depthShaderProg->SetUniform(M_MODEL, modelMatrix);
	//depthShaderProg->SetUniform(M_MODEL, );
	glViewport(0, 0, shadowWidth, shadowHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	//model->Draw(depthShaderProg);

	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, depthMap);
	model->DrawVertices();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Shadow::Shadow()
{
	
}

Shadow::Shadow(int shadowWidth,int shadowHeight,float left,float right,float top, float bottom,
	float zNear, float zFar)
{
	//this->projectionRect = projectionRect;
	this->shadowWidth = shadowWidth;
	this->shadowHeight = shadowHeight;
	this->zNear = zNear;
	this->zFar = zFar;
	glGenFramebuffers(1, &depthMapFBO);

	
	glGenTextures(1, &depthMap);//создать текстуру для карты глубины
	glBindTexture(GL_TEXTURE_2D, depthMap);
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
	glBindFramebuffer(GL_FRAMEBUFFER, 0);//привязываем буфер по умолчанию

	lightProjection = glm::ortho(left, right,bottom, top, zNear, zFar);

}



Shadow::~Shadow()
{
}
