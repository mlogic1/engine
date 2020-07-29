#include "ShaderManager.h"
#include "SystemBase.h"
#include "Constants.h"
#include <nlohmann/json.hpp>
#include <vector>

namespace Engine
{
	ShaderManager::ShaderManager(const System::SystemBase& system) :
		m_systemRef(system)
	{
		std::string shadersJsonString;
		std::string shadersJsonPath = std::string(PATH_ASSETS) + std::string(ENGINE_FILE_SHADERS);
		m_systemRef.LoadStringDataFromAssets(shadersJsonPath, shadersJsonString);

		std::vector<ShaderDataRecord> shaderData;

		nlohmann::json m_shadersData = nlohmann::json::parse(shadersJsonString);

		try 
		{
			for (auto data : m_shadersData.items())
			{				
				std::string shaderName = data.key();
				std::string vertexShaderFileName = data.value()["VertexShader"];
				std::string fragmentShaderFileName = data.value()["FragmentShader"];
				shaderData.push_back({ shaderName, vertexShaderFileName, fragmentShaderFileName });
			}
		}
		catch (nlohmann::detail::exception& exception)
		{
			Log::Write("Failed to parse " + shadersJsonPath + ". Faulty object.", Log::LogType::ERR);
			Log::Write(exception.what());
		}

		for (ShaderDataRecord& shaderRecord : shaderData)
		{
			std::string vertexShaderSource;
			std::string fragmentShaderSource;
			System::SYSTEM_PTR->LoadStringDataFromAssets(PATH_SHADERS + shaderRecord.VertexShaderFileName, vertexShaderSource);
			System::SYSTEM_PTR->LoadStringDataFromAssets(PATH_SHADERS + shaderRecord.FragmentShaderFileName, fragmentShaderSource);
			m_shaders.push_back(new Shader(shaderRecord.ShaderName, vertexShaderSource, fragmentShaderSource));
		}
	}

	Shader* ShaderManager::GetShader(std::string name) const
	{
		for (Shader* shader : m_shaders)
		{
			if (shader->GetName() == name)
			{
				return shader;
			}
		}
		throw std::string("Unable to find shader: " + name);
	}
}