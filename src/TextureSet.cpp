#include "TextureSet.h"

#include "Constants.h"
#include <stb_image.h>
#include "desktop/System.h"


TextureSet::TextureSet(std::list<std::string> texturesToLoad)
{
	for (std::string textureName : texturesToLoad)
	{
		Log::Write("Loading texture | " + textureName);

		std::string textureAssetPath = PATH_TEXTURES + textureName;
		unsigned char* buffer;
		off_t length;
		int width, height, nOfChannels;
		System::LoadBinaryDataFromAssets(textureAssetPath, buffer, length);
		Log::Write("Size | " + std::to_string(length) + " bytes");

		unsigned char* data = stbi_load_from_memory(buffer, length, &width, &height, &nOfChannels, 0);
		delete[] buffer;

		if (!data)
		{
			std::string error = "Unable to load image: ";
			error += textureAssetPath;
			throw error;
		}
		else {
			std::cout << "Loaded image: " << textureAssetPath << std::endl;
		}

		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		

		// texture filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// enables transparency on png texture
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// generate texture
		if (nOfChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		// clean up
		stbi_image_free(data);

		this->m_textures[textureName] = textureID;
	}
}

TextureSet::~TextureSet()
{
}

GLuint TextureSet::operator[](std::string textureName)
{
	return this->m_textures[textureName];
}
