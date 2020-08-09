#include "SceneObjectFactory.h"
#include "SceneObject.h"
#include "Shader.h"
#include "Sprite.h"
#include "TextObject.h"
#include "SystemBase.h"

namespace Engine
{
    SceneObject* SceneObjectFactory::CreateSprite(std::string objectID, Rect spriteRect, GLuint textureID)
    {
        Shader* spriteShader = System::SYSTEM_PTR->GetShaderManager()->GetShader("OrthoShader");
        return new Sprite(objectID, spriteShader, spriteRect, textureID);
    }


    SceneObject* SceneObjectFactory::CreateTextObject(std::string objectID, Rect objectRect, std::string text)
    {
        Shader* fontShader = System::SYSTEM_PTR->GetShaderManager()->GetShader("FontShader");
		return new TextObject(objectID, fontShader, objectRect, System::SYSTEM_PTR->GetFontManager()->GetSupportedCharacters(), text);
    }
}
