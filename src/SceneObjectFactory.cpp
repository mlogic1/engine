#include "SceneObjectFactory.h"
#include "SceneObject.h"
#include "Shader.h"
#include "Sprite.h"
#include "TextObject.h"
#include "SystemBase.h"

namespace Engine
{
    SceneObject* SceneObjectFactory::CreateSprite(SpriteData spriteData)
    {
        Shader* spriteShader = System::SYSTEM_PTR->GetShaderManager()->GetShader("OrthoShader");

        SceneObject* baseObject = new Sprite(spriteData.id, spriteShader, spriteData.rect, spriteData.texture);

        for (int i = 0; i < spriteData.nestedObjects.size(); ++i)
        {
            SpriteData nestedObjectData = spriteData.nestedObjects[i];
            SceneObject* nestedObject = CreateSprite(nestedObjectData);
            baseObject->AddNestedObject(nestedObject);
        }

        return baseObject;
    }


    SceneObject* SceneObjectFactory::CreateTextObject(std::string objectID, Rect objectRect, std::vector<SceneObject*> nestedObjects, std::string text)
    {
        Shader* fontShader = System::SYSTEM_PTR->GetShaderManager()->GetShader("FontShader");
		return new TextObject(objectID, fontShader, objectRect, System::SYSTEM_PTR->GetFontManager()->GetSupportedCharacters(), nestedObjects, text);
    }
}
