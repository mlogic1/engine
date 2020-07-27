#include "SpriteFactory.h"
#include "SystemBase.h"

namespace Engine
{
    Sprite* SpriteFactory::Create(Rect spriteRect, GLuint textureID)
    {
        Shader* spriteShader = System::SYSTEM_PTR->GetShaderManager()->GetShader("OrthoShader");
        return new Sprite(spriteShader, spriteRect, textureID);
    }
}