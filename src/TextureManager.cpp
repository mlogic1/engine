#include "TextureManager.h"
#include "SystemBase.h"
#include "Constants.h"
#include <nlohmann/json.hpp>
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
			// TODO parse data

			/*std::string vertexShaderSource;
			std::string fragmentShaderSource;
			System::SYSTEM_PTR->LoadStringDataFromAssets(PATH_SHADERS + shaderRecord.VertexShaderFileName, vertexShaderSource);
			System::SYSTEM_PTR->LoadStringDataFromAssets(PATH_SHADERS + shaderRecord.FragmentShaderFileName, fragmentShaderSource);
			m_shaders.push_back(new Shader(shaderRecord.ShaderName, vertexShaderSource, fragmentShaderSource));*/
		}
	}
	
	GLuint TextureManager::GetTexture(std::string name) const
	{

		return -1;
	}
}