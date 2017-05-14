#pragma once
#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL.h>




class Texture
{

private:
	int id=0;
	std::string type;
	std::string path;
public:

	std::string getPath()
	{
		return path;
	}

	int GetID()
	{
		return id;
	}

	std::string getType()
	{
		return type;
	}

	Texture():Texture(TextureTypes::duffuseTexName)
	{

	}

	Texture(std::string type)
	{
		this->type = type;
	}

	void Load(const char* filepath)
	{
		Load(filepath, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT|SOIL_LOAD_RGBA);
	}

	void Load(std::string filepath)
	{
		Load(filepath.c_str(), SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT|SOIL_LOAD_RGBA);
	}

	

	void Load(const char* filepath, unsigned int flags)
	{
		int tex = SOIL_load_OGL_texture(filepath, SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			flags);
		if (tex == 0)
		{
			printf("SOIL texture loading error: '%s', path to texture: '%s'\n", SOIL_last_result(),filepath);
			return;
		}
		id = tex;
		path = filepath;
	}

	void Bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	~Texture()
	{
	}
};

