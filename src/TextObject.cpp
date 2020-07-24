#include "TextObject.h"
#include "FontManager.h"
#include "SystemBase.h"
#include "Log.h"
#include "Constants.h"

namespace Engine
{
	TextObject::TextObject(Shader* fontShader, Rect spriteRect, std::map<char, Character> supportedCharacters, std::string text)
		: SceneObject(spriteRect),
		m_fontShader(fontShader),
		m_text(text)
	{
		projection = glm::ortho(0.0f, static_cast<float>(VIRTUAL_RESOLUTION_WIDTH), 0.0f, static_cast<float>(VIRTUAL_RESOLUTION_HEIGHT));
        
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

	TextObject::~TextObject()
	{

	}

	void TextObject::update(float deltaTime)
	{

	}

	void TextObject::render()
	{
        m_fontShader->useShader();
        m_fontShader->setMat4("projection", projection);
        m_fontShader->setVec3f("textColor", 1.0f, 1.0f, 1.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        //float x = 50, y = 50, scale = 1.0f;
        float temp_x = m_position.x;
        float scale = 1.0f;

        // iterate through all characters
        std::string::const_iterator c;
        for (c = m_text.begin(); c != m_text.end(); c++)
        {
            Character ch = m_characters[*c];

            float xpos = temp_x + ch.Bearing.x * scale;
            float ypos = m_position.y - (ch.Size.y - ch.Bearing.y) * scale;

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
            temp_x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextObject::SetText(const std::string& newText)
	{
		m_text = newText;
	}

	const std::string& TextObject::GetText()
	{
		return m_text;
	}
}
