#include "TextureManager.h"
#include "SystemBase.h"
#include "Constants.h"
#include <nlohmann/json.hpp>
#include <stb_image.h>
#include <vector>

namespace Engine
{
	TextureManager::TextureManager(const System::SystemBase& system) :
		m_systemRef(system)
	{
		std::string texturesJsonString;
		std::string texturesJsonPath = PATH_ASSETS + TEXTURE_LIST_FILE;
		m_systemRef.LoadStringDataFromAssets(texturesJsonPath, texturesJsonString);

		std::vector<TextureDataRecord> textureData;

		nlohmann::json texturesData = nlohmann::json::parse(texturesJsonString);

		try 
		{
			for (auto data : texturesData.items())
			{				
				std::string textureName = data.key();
				std::string textureFileName = data.value();
				
				textureData.push_back({ textureName, textureFileName });
			}
		}
		catch (nlohmann::detail::exception& exception)
		{
			Log::Write("Failed to parse " + texturesJsonPath + ". Faulty object.", Log::LogType::ERR);
			Log::Write(exception.what());
		}

		for (const TextureDataRecord& textureRecord : textureData)
		{
			Log::Write("Loading texture | " + textureRecord.TextureFileName);

			std::string textureAssetPath = PATH_TEXTURES + textureRecord.TextureFileName;
			unsigned char* buffer;
			off_t length;
			int width, height, nOfChannels;
			stbi_set_flip_vertically_on_load(true);
			System::SYSTEM_PTR->LoadBinaryDataFromAssets(textureAssetPath, buffer, length);
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
			m_textures[textureRecord.TextureName] = textureID;
		}
	}
	
	GLuint TextureManager::GetTexture(const std::string& name) const
	{
		if (m_textures.find(name) == m_textures.end())
		{
			throw std::string("Texture " + name + " is not loaded or doesn't exist");
		}
		else 
		{
			return m_textures.at(name);
		}
	}
}