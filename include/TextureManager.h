/**
    Texture manager loads and supplies all texture data

	@author mlogic1
	@date 15.06.2020.
*/

#pragma once

#include "Log.h"
#include <map>
#include <string>
#include <glad/glad.h>

namespace System
{
	class SystemBase;
}

namespace Engine
{
	class TextureManager
    {
        public:
            TextureManager(const System::SystemBase& system);
            GLuint GetTexture(const std::string& name) const;
		

        private:
			std::map<std::string, GLuint> m_textures;
			const System::SystemBase& m_systemRef;

			struct TextureDataRecord
			{
				std::string TextureName;
				std::string TextureFileName;
			};
    };
}