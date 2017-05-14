#pragma once
#include "Light.h"
struct DirectionalLight :public Light
{
	glm::vec3 direction;
};