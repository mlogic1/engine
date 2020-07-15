/**
    Text Object
	@author mlogic1
	@date 15.07.2020.
*/

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include "SceneObject.h"
#include "Shader.h"
#include <glad/glad.h>
#include <string>

namespace Engine
{
	class TextObject : public SceneObject 
	{

	public:
		TextObject(Shader* fontShader, Rect spriteRect, std::string text = "");
		~TextObject();

		/***************************************
		 * inherited methods
		***************************************/
		void update(float deltaTime) override;
		void render() override;

		/***************************************
		 * textures
		***************************************/
		void SetText(const std::string& newText);
		std::string GetText();

	private:
		std::string m_text;
	};
}

#endif /* TEXTOBJECT_H */
