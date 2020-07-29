/**
    Shader manager loads, compiles and handles all shader data

	@author mlogic1
	@date 14.06.2020.
*/

#pragma once

#include "Log.h"
#include "Shader.h"
#include <string>
#include <vector>

// using json = nlohmann::json;

namespace System
{
	class SystemBase;
}

namespace Engine
{
	class ShaderManager
    {
        public:
            ShaderManager(const System::SystemBase& system);
            Shader* GetShader(std::string name) const;

        private:
            std::vector<Shader*> m_shaders;

			const System::SystemBase& m_systemRef;

			struct ShaderDataRecord
			{
				std::string ShaderName;
				std::string VertexShaderFileName;
				std::string FragmentShaderFileName;
			};
    };
}