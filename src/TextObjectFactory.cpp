#include "TextObjectFactory.h"
#include "SystemBase.h"

namespace Engine
{
	TextObject* TextObjectFactory::Create(Rect objectRect, std::string text)
	{
		Shader* fontShader = System::SYSTEM_PTR->GetShaderManager()->GetShader("FontShader");
		return new TextObject(fontShader, objectRect, System::SYSTEM_PTR->GetFontManager()->GetSupportedCharacters(), text);
	}
}