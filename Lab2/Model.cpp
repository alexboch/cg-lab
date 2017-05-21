#include "Model.h"

void Model::Draw(ShaderProgram* program)
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		/*if (i == 1)
			glDisable(GL_DEPTH_TEST);*/

		//todo:�������� ���������� ���������� �������� �� ���������� �� ������

		this->meshes[i].Draw(program);
		//glEnable(GL_DEPTH_TEST);
	}
}

void Model::DrawVertices()
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i].DrawVertices();
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}

	size_t pos = path.find_last_of('/');
	if(pos==std::string::npos)
	this->directory = path.substr(0, path.find_last_of('\\'));

	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;




	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// Process vertex positions, normals and texture coordinates
		//�������
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		
		//�������
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		//���������� ����������
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	// Process indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	float alpha = 1;//��������������
	Material meshMaterial;
		// Process material
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			
			
			//if (aiGetMaterialFloat(material, AI_MATKEY_OPACITY, &alpha) != AI_SUCCESS) {			
			//	alpha = 1;//���� �� ������� �������� ��������, �� ��������� ������������
			//}
			if (aiGetMaterialFloat(material, AI_MATKEY_OPACITY, &meshMaterial.alpha) != AI_SUCCESS) {
				meshMaterial.alpha = 1;//���� �� ������� �������� ��������, �� ��������� ������������
			}
			aiColor4D specularColor;
			if (aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor) != AI_SUCCESS)
			{

			}
			else
			{
				meshMaterial.specularColor = glm::vec3(specularColor.r, specularColor.g, specularColor.b);
			}
			

			if (aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &meshMaterial.shininess) != AI_SUCCESS)
			{
				meshMaterial.shininess = 0;
			}

			std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material,
				aiTextureType_DIFFUSE, TextureTypes::duffuseTexName);
			
			if(diffuseMaps.size()==0)
			{
				//��������� �������� �� ���������
				Texture defaultTexture("Textures\\default.bmp");
				diffuseMaps.push_back(defaultTexture);
			}
			
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			

			std::vector<Texture> specularMaps = this->loadMaterialTextures(material,
				aiTextureType_SPECULAR, TextureTypes::specularTexName);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

	//return Mesh(vertices, indices, textures,alpha);
		return Mesh(vertices, indices, textures, meshMaterial);
}



//todo:������� �������� �� ������������� �����
vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		GLboolean skip = false;
		for (GLuint j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].getPath().c_str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // If texture hasn't been loaded already, load it
			Texture texture(typeName);
			std::string fullpath = TEX_DIR + std::string(str.C_Str());
			texture.Load(fullpath);
			//texture.id = TextureFromFile(str.C_Str(), this->directory);
			//texture.type = typeName;
			//texture.path = str;
			textures.push_back(texture);
			this->textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}


//GLint Model::TextureFromFile(const char* path, std::string directory)
//{
//	//Generate texture ID and load texture data 
//	std::string filename = std::string(path);
//	//filename = directory + '/' + filename;
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//	int width, height;
//	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
//	// Assign texture to ID
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	// Parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	SOIL_free_image_data(image);
//	return textureID;
//}
