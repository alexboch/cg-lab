#pragma once
#include <vector>
#include <GL/glew.h>
#include <assimp\Importer.hpp>
#include <assimp\types.h>
#include "Shader.h"

#include "Vertex.h"
#include <iostream>
#include <string>
#include <sstream>
#include "ShaderProgram.h"
#include "TextureTypeNames.h"
#include "Texture.h"

//using namespace std;
//struct Texture {
//	GLuint id;
//	string type;
//	aiString path;
//};

struct Material {
	float shininess = 0.0f;//зеркальность
	float alpha = 1.0f;//непрозрачность
	glm::vec3 specularColor;//цвет отражаемого света
};

class Mesh
{
public:
	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	Texture texture;
	/*  Functions  */
	//Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures,float alpha=1.0);
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, Material mat);
	void Draw(ShaderProgram* program);
	void DrawVertices();
	void SetMaterialProps(ShaderProgram* program);
	Material GetMaterial();
	~Mesh();
private:
	/*  Render data  */
	GLuint VAO, VBO, EBO;

	//float _alpha;//непрозрачность
	//float _shininess;
	Material _material;
	/*  Functions    */
	void setupMesh();
};

