/**
	Sprite Factory creates scene sprites
	@author mlogic1
	@date 26.7.2020.
*/

#ifndef SPRITE_FACTORY_H
#define SPRITE_FACTORY_H

#include "Shader.h"
#include "Sprite.h"
#include "Rect.h"
#include <glad/glad.h>

namespace Engine
{
	class SpriteFactory
	{
	public:
		static Sprite* Create(Rect spriteRect, GLuint textureID);
	};
}

#endif // SPRITE_FACTORY_H