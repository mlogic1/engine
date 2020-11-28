#include "SceneObjectFactory.h"
#include "SceneObject.h"
#include "Shader.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
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

    SceneObject* SceneObjectFactory::CreateAnimatedSprite(AnimatedSpriteData spriteData)
    {
        Shader* spriteShader = System::SYSTEM_PTR->GetShaderManager()->GetShader("OrthoShader");

        SceneObject* baseObject = new AnimatedSprite(spriteData.id, spriteShader, spriteData.rect, spriteData.texture, spriteData.frameCount, spriteData.frameTime, spriteData.frameWidth, spriteData.frameHeight, spriteData.textureRows, spriteData.textureCols);

        for (int i = 0; i < spriteData.nestedObjects.size(); ++i)
        {
            AnimatedSpriteData nestedObjectData = spriteData.nestedObjects[i];
            SceneObject* nestedObject = CreateAnimatedSprite(nestedObjectData);
            baseObject->AddNestedObject(nestedObject);
        }

        return baseObject;
    }


    SceneObject* SceneObjectFactory::CreateTextObject(TextObjectData objectData)
    {
        Shader* fontShader = System::SYSTEM_PTR->GetShaderManager()->GetShader("FontShader");
        SceneObject* baseObject = new TextObject(objectData.id, fontShader, objectData.rect, System::SYSTEM_PTR->GetFontManager()->GetSupportedCharacters(), objectData.text);

        // TODO nested objects

		return baseObject;
    }

    SceneObject* SceneObjectFactory::CreateButton(ButtonObjectData buttonData)
    {
        Shader* buttonShader = System::SYSTEM_PTR->GetShaderManager()->GetShader("OrthoShader");

        SceneObject* baseObject = new Button(buttonData.id, buttonShader, buttonData.rect, buttonData.textureMap, System::SYSTEM_PTR->GetCursorPosition());

        for (int i = 0; i < buttonData.nestedObjects.size(); ++i)
        {
            ButtonObjectData nestedObjectData = buttonData.nestedObjects[i];
            SceneObject* nestedObject = CreateButton(nestedObjectData);
            baseObject->AddNestedObject(nestedObject);
        }

        return baseObject;
    }
}
