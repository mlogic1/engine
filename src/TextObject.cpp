#include "TextObject.h"
#include "SystemBase.h"
#include "Log.h"
#include "Constants.h"

namespace Engine
{
	TextObject::TextObject(Shader* fontShader, Rect spriteRect, std::string text)
		: SceneObject(spriteRect)
	{
		m_text = text;
	}
	TextObject::~TextObject()
	{
	}
	void TextObject::update(float deltaTime)
	{
	}
	void TextObject::render()
	{
	}
	void TextObject::SetText(const std::string& newText)
	{
		m_text = newText;
	}
	std::string TextObject::GetText()
	{
		return m_text;
	}
}
