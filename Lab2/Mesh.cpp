#include "Mesh.h"






Mesh::~Mesh()
{
}

//Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, float alpha)
//{
//	this->vertices = vertices;
//	this->indices = indices;
//	this->textures = textures;
//	this->_alpha = alpha;
//	this->setupMesh();
//}

///<summary>
///Отправляет в шейдер свойства материала
///</summary>
void Mesh::SetMaterialProps(ShaderProgram* program)
{
	GLint alphaLoc = program->GetUniformLocation(MAT_ALPHA);
	program->SetUniform(MAT_ALPHA, _material.alpha);
	
	program->SetUniform(MAT_SPCOLOR, _material.specularColor);
	program->SetUniform(MAT_SHINE, _material.shininess);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
		&this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
		&this->indices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, Material mat)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	//this->_alpha = alpha;
	_material = mat;
	this->setupMesh();
}

void Mesh::Draw(ShaderProgram* program)
{
	
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	//for (GLuint i = 0; i < this->textures.size(); i++)
	//{
	//	glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
	//									  // Retrieve texture number (the N in diffuse_textureN)
	//	std::stringstream ss;
	//	std::string number;
	//	std::string name = this->textures[i].getType();
	//	if (name == TextureTypes::duffuseTexName)
	//		ss << diffuseNr++; // Transfer GLuint to stream
	//	else if (name == TextureTypes::specularTexName)
	//		ss << specularNr++; // Transfer GLuint to stream
	//	number = ss.str();

	//	//glUniform1f(glGetUniformLocation(program.getId(), ("material." + name + number).c_str()), i);
	//	SetMaterialProps(program);

	//	//glUniform1f()
	//	
	//	//glUniform1f(glGetUniformLocation(program.getId(), (name + number).c_str()), i);
	//	glBindTexture(GL_TEXTURE_2D, this->textures[i].GetID());
	//}
	SetMaterialProps(program);
	//program->SetUniform()
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textures[0].GetID());
	//включить прозрачность
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::DrawVertices()
{
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

