#pragma once
#include <vector>
#include <GL/glew.h>
#include <assimp\Importer.hpp>
#include <assimp\types.h>
#include <assimp\mesh.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "Shader.h"
#include "Mesh.h"
#include <glm/gtc/type_ptr.hpp>

using namespace std;
class Model
{
public:
	/*  Functions   */
	Model(GLchar* path)
	{
		this->loadModel(path);
	}
	void Draw(ShaderProgram* program,glm::vec3 cameraPosition);
	void DrawVertices();
private:
	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::vector<Texture> textures_loaded;
	std::string directory;

	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
	std::string typeName);
	GLint TextureFromFile(const char* path, std::string directory);
};