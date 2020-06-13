/**
	Textureset handles loading, storing and deallocating textures

	@author mlogic1
	@date 04.11.2019.
*/

#ifndef TEXTURESET_H
#define TEXTURESET_H

#include "Log.h"

#include <string>
#include <map>
#include <list>
#include <glad/glad.h>

struct Texture
{
	std::string TextureName;
	std::string TexturePath;
};

class TextureSet
{
public:
	TextureSet(std::list<std::string> texturesToLoad);
	~TextureSet();

	GLuint operator[](std::string textureName);

private:

	std::map<std::string, GLuint> m_textures;
};

#endif