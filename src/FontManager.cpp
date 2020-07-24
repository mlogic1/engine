#include "FontManager.h"
#include "Constants.h"
#include "Log.h"
#include "SystemBase.h"
#include "Shader.h"

#include <glad/glad.h>
#include <nlohmann/json.hpp>
#include <vector>

namespace Engine
{
	FontManager::FontManager(const System::SystemBase& systemRef) :
		m_systemRef(systemRef)
	{
		if (FT_Init_FreeType(&m_fontLibrary))
		{
            std::string errMessage = "Failed to init font manager";
			Log::Write(errMessage, Log::LogType::ERR);
			throw errMessage;
		}

        Log::Write("Success init font manager", Log::LogType::SUCCESS);
        std::string fontsJsonString;
        std::string pathJsonFonts = PATH_ASSETS + FONTS_LIST_FILE;
        m_systemRef.LoadStringDataFromAssets(pathJsonFonts, fontsJsonString);

        std::vector<FontDataRecord> fontData;
        nlohmann::json fontsData = nlohmann::json::parse(fontsJsonString);

        try
        {
            for (auto data : fontsData.items())
			{
				std::string fontName = data.key();
				std::string fontFileName = data.value();

				fontData.push_back({ fontName, fontFileName });
			}
        }
        catch (nlohmann::detail::exception& exception)
		{
			Log::Write("Failed to parse " + pathJsonFonts + ". Faulty object.", Log::LogType::ERR);
			Log::Write(exception.what());
			throw std::string("Fontmanager: Failed parsing fonts file");
		}

        for (const FontDataRecord& fontRecord : fontData)
        {
            Log::Write("Loading font | " + fontRecord.FontFileName);
            std::string fontAssetPath = PATH_FONTS + fontRecord.FontFileName;
            unsigned char* buffer;
            off_t length;
            System::SYSTEM_PTR->LoadBinaryDataFromAssets(fontAssetPath, buffer, length);

            FT_Face fontFace;
            if (FT_New_Memory_Face(m_fontLibrary, buffer, length, 0, &fontFace))
            {
                std::string errorMessage = "Failed to create font face from memory";
                Log::Write(errorMessage);
                throw errorMessage;
            }

            FT_Set_Pixel_Sizes(fontFace, 0, 48);
            // disable byte-alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            Log::Write("Loading all supported characters");
            for (int i = 97 ; i < 123 ; ++i)
            {
                if (FT_Load_Char(fontFace, static_cast<char>(i), FT_LOAD_RENDER))
                {
                    std::string errorMessage = "Failed to load font char: " + std::to_string('G');
                    Log::Write(errorMessage);
                    throw errorMessage;
                }
                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    fontFace->glyph->bitmap.width,
                    fontFace->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    fontFace->glyph->bitmap.buffer
                );
                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // now store character for later use
                Character character = {
                    texture,
                    glm::ivec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows),
                    glm::ivec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top),
                    static_cast<unsigned int>(fontFace->glyph->advance.x)
                };
                m_characters.insert(std::pair<char, Character>(i, character));
            }

            m_fonts.emplace(fontRecord.FontName, fontFace);
        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
	}

	FontManager::~FontManager()
	{
        // TODO release all fonts
	}

    std::map<char, Character> FontManager::GetSupportedCharacters() const
    {
        return m_characters;
    }

	void FontManager::RenderTest(std::string text)
	{
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(VIRTUAL_RESOLUTION_WIDTH), 0.0f, static_cast<float>(VIRTUAL_RESOLUTION_HEIGHT));
        Shader* fontShader = m_systemRef.GetShaderManager()->GetShader("FontShader");

        if (fontShader == nullptr)
        {
            Log::Write("Font shader does not exist");
            throw std::string("Font shader does not exist");
        }

        fontShader->useShader();
        fontShader->setMat4("projection", projection);
        fontShader->setVec3f("textColor", 1.0f, 1.0f, 1.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        float x = 50, y = 50, scale = 1.0f;

        // iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = m_characters[*c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
	}
}
