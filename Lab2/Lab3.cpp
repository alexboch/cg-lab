// Lab2.cpp : Defines the entry point for the console application.
//

#pragma once
#include <GL\glew.h>
#include "GLObject.h"
#include "GLContext.h"
#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include <assimp\Importer.hpp>
#include "Model.h"
#include "stdafx.h"
#include <memory>
#include "Camera.h"
#include "Light.h"
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shadow.h"

#pragma region Variables
std::unique_ptr<Model> model;
std::unique_ptr<Mesh> triangleMesh;
//std::unique_ptr<ShaderProgram>  shaderProgram;
ShaderProgram* shaderProgram;
ShaderProgram* depthShaderProgram;
GLuint screenWidth = 1024, screenHeight = 768;
Camera camera;
const GLfloat cameraZoomSpeed = 0.1f;
bool firstMotion = true;
int deltaTime, oldTimeSinceStart = 0;
Light pointLight, directionalLight;
std::vector<Light> gLights;//источники света
float lightMoveSpeed = 0.001f;
bool pointLightIsMoving = false;
bool dirLightIsMoving = false;
float pointLightXMovement = 0.0f;
float pointLightYMovement = 0.0f;
float dirLightXMovement = 0.0f;
float dirLightYMovement = 0.0f;

#pragma region Shadow
/*–азмеры ортографической проекции*/
const float shadowLeft = -10.0f;
const float shadowRight = 10.0f;
const float shadowTop = 10.0f;
const float shadowBottom = -10.0f;
const float nearPlane = 1.0f, farPlane = 7.5f;
const int shadowWidth = 1024;
const int shadowHeight = 1024;
Shadow* shadow;
#pragma endregion

#pragma endregion


enum MouseEnum
{
	MOUSE_LEFT_BUTTON = 0,
	MOUSE_MIDDLE_BUTTON = 1,
	MOUSE_RIGHT_BUTTON = 2,
	MOUSE_SCROLL_UP = 3,
	MOUSE_SCROLL_DOWN = 4
};



template <typename T>
void SetLightUniform(ShaderProgram* program, const char* propertyName, size_t lightIndex, const T& value) {
	std::ostringstream ss;
	//ss << "allLights[" << lightIndex << "]." << propertyName;
	ss << L_ARR << "[" << lightIndex << "]." << propertyName;
	std::string uniformName = ss.str();

	program->SetUniform(uniformName.c_str(), value);
}

#pragma region Callbacks
void display(void)
{
	
}
GLuint quadVAO, quadVBO;

void renderQuad()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void idle()
{
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shaderProgram->Use();

	glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shaderProgram->SetUniform(M_PROJ, projection);
	shaderProgram->SetUniform(M_VIEW, view);
	// Draw the loaded model
	glm::mat4 modelMatrix;
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -0.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
	//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
	shaderProgram->SetUniform(M_MODEL, modelMatrix);
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
	shaderProgram->SetUniform(NORM_MATRIX, normalMatrix);
#pragma region Lighting
	//—вет
	//ShaderProgram* sp = shaderProgram.get();
	ShaderProgram* sp = shaderProgram;

	if (pointLightIsMoving)
	{
		pointLightXMovement += lightMoveSpeed;
		pointLightYMovement += lightMoveSpeed;
	}
	if (dirLightIsMoving)
	{
		dirLightXMovement += lightMoveSpeed;
		dirLightYMovement += lightMoveSpeed;
	}
	for (size_t i = 0; i < gLights.size(); ++i) 
	{
		if (gLights[i].lightType == DIR_LIGHT&&dirLightIsMoving)
		{
				gLights[i].position.x += cos(5 * dirLightXMovement) / 70.0f;
				gLights[i].position.y += sin(8 * dirLightYMovement) / 50.0f;
		}
		else if (gLights[i].lightType == POINT_LIGHT&&pointLightIsMoving)
		{
						
				gLights[i].position.x += cos(10 * pointLightXMovement) / 80.0f;
				gLights[i].position.y += sin(10 * pointLightYMovement) / 50.0f;
		}
		SetLightUniform(shaderProgram, L_POS, i, gLights[i].position);
		SetLightUniform(shaderProgram, L_INTENS, i, gLights[i].intensities);
		SetLightUniform(shaderProgram, L_ATTEN, i, gLights[i].attenuation);
		SetLightUniform(shaderProgram, L_AMBIENTCOEFF, i, gLights[i].ambientCoefficient);
		SetLightUniform(shaderProgram, "coneAngle", i, gLights[i].coneAngle);
		SetLightUniform(shaderProgram, "coneDirection", i, gLights[i].coneDirection);
	}
#pragma endregion
	glm::mat4 lightSpaceMatrix;
	shadow->RenderToFramebuffer(gLights[0].position, depthShaderProgram,model.get(),
		lightSpaceMatrix,modelMatrix);
	
	shaderProgram->Use();
	shaderProgram->SetUniform(CAM_POS, camera.Position);
	shaderProgram->SetUniform(LSPACE_MATRIX, lightSpaceMatrix);
	glViewport(0,0,screenWidth, screenHeight);
	shaderProgram->SetUniform(SHADOW_MAP, 1);//указываем, что номер карты теней--первый
	glActiveTexture(GL_TEXTURE1);
	//shaderProgram->SetUniform("shadowMap",)
	glBindTexture(GL_TEXTURE_2D, shadow->GetDepthMap());
	model->Draw(shaderProgram);
	//model->DrawVertices();
	glutSwapBuffers();
}

void DrawShadowsToBuffer()
{
	
}


void mouse(int button, int state, int x, int y)
{
	// Wheel reports as button 3(scroll up) and button 4(scroll down)
	if ((button == MouseEnum::MOUSE_SCROLL_DOWN) || (button == MouseEnum::MOUSE_SCROLL_UP)) // It's a wheel event
	{
		// Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
		if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
		//printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);

		GLfloat yOffset = button == MOUSE_SCROLL_DOWN ? -cameraZoomSpeed : cameraZoomSpeed;
		camera.ProcessMouseScroll(yOffset);
	}
	else if (button == MOUSE_LEFT_BUTTON || button == MOUSE_RIGHT_BUTTON || button == MOUSE_MIDDLE_BUTTON&&state==GLUT_UP)
		firstMotion = true;
	else {  // normal button event
		//printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
	}
}


int prevX, prevY;

void motion(int x, int y)
{
	if (firstMotion)
	{
		prevX = x;
		prevY = y;
		firstMotion = false;
	}
	else {
		int dx = x - prevX;
		int dy = y - prevY;
		//printf("dx:%i dy:%i", dx,dy);
		camera.ProcessMouseMovement(dx, -dy);
		prevX = x;
		prevY = y;
	}
}

void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		camera.ProcessKeyboard(RIGHT, deltaTime);
		break;
	case GLUT_KEY_LEFT:
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		camera.ProcessKeyboard(FORWARD, deltaTime);
		break;
	case 's':
		camera.ProcessKeyboard(BACKWARD, deltaTime);
		break;
	case 'a':
		camera.ProcessKeyboard(LEFT, deltaTime);
		break;
	case 'd':
		camera.ProcessKeyboard(RIGHT, deltaTime);
		break;
	case 'q':
		pointLightIsMoving = !pointLightIsMoving;
		break;
	case 'e':
		dirLightIsMoving = !dirLightIsMoving;
		break;
	}
}
#pragma endregion


void InitLights()
{
	shaderProgram->Use();
	directionalLight.position = glm::vec4(0, 1, 0, 0); //w == 0 indications a directional light
	directionalLight.intensities = glm::vec3(1, 1, 1); 
	directionalLight.ambientCoefficient = 0.06f;
	directionalLight.lightType = DIR_LIGHT;
	gLights.push_back(directionalLight);
	shaderProgram->SetUniform(NUM_LIGHTS, (GLint)gLights.size());//устанавливаем количество источников света
}


int main(int argc, char** argv)
{
	Window wnd(screenWidth,screenHeight,10,10,"Lab2");
	GLContext::Initialize(argc, argv, wnd, display);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	//shaderProgram = std::make_unique<ShaderProgram>();
	shaderProgram = new ShaderProgram();
	model = std::unique_ptr<Model>(new Model("Models\\room\\room.obj"));

	VertexShader vertexShader("Shaders\\shadows.vert");
	FragmentShader fragmentShader("Shaders\\shadows.frag");
	shaderProgram->AttachShader(vertexShader);
	shaderProgram->AttachShader(fragmentShader);
	
	//shaderProgram->Use();
#pragma region Prepare shadows
	depthShaderProgram = new ShaderProgram();
	VertexShader depthVertexShader("Shaders\\depth_shader.vert");
	FragmentShader depthFragmentShader("Shaders\\depth_shader.frag");
	depthShaderProgram->AttachShader(depthVertexShader);
	depthShaderProgram->AttachShader(depthFragmentShader);
	depthShaderProgram->Link();
	shadow = new Shadow(shadowWidth, shadowHeight, shadowLeft, shadowRight,
	shadowTop, shadowBottom, nearPlane, farPlane);
#pragma endregion


	InitLights();
	
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	
    return 0;
}

