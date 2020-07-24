/**
    Text Object
	@author mlogic1
	@date 15.07.2020.
*/

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include "FontManager.h"
#include "SceneObject.h"
#include "Shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <string>

namespace Engine
{
	class TextObject : public SceneObject 
	{

	public:
		TextObject(Shader* fontShader, Rect spriteRect, std::map<char, Character> supportedCharacters, std::string text = "");
		~TextObject();

		/***************************************
		 * inherited methods
		***************************************/
		void update(float deltaTime) override;
		void render() override;

		void SetText(const std::string& newText);
		const std::string& GetText();

	private:
		std::string m_text;

		glm::mat4 projection;
		Shader* m_fontShader;
		std::map<char, Character> m_characters;

		/***************************************
		 * GL
		***************************************/
		unsigned int VAO, VBO;
	};
}

#endif /* TEXTOBJECT_H */
