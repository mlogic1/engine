/**
	Font manager handles font loading and handling

	@author mlogic1
	@date 27.06.2019.
*/

#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <map>

namespace System
{
	class SystemBase;
}

namespace Engine
{
	class FontManager
	{
	public:
		FontManager(const System::SystemBase& systemRef);
		FontManager(const FontManager& FontManager) = delete;
		~FontManager();

        void RenderTest(std::string text);  // TODO move this to TextObject file

	private:
		FT_Library m_fontLibrary;
		const System::SystemBase& m_systemRef;
		unsigned int VAO, VBO;

		const std::string FONTS_LIST_FILE = "fonts.json";   // move this to constants

		std::map<std::string, FT_Face> m_fonts;

        struct Character
        {
            unsigned int TextureID;  // ID handle of the glyph texture
            glm::ivec2   Size;       // Size of glyph
            glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
            unsigned int Advance;    // Offset to advance to next glyph
        };

        std::map<char, Character> m_characters;

        struct FontDataRecord
        {
            std::string FontName;
            std::string FontFileName;
        };
    };
}

#endif // FONT_MANAGER_H
