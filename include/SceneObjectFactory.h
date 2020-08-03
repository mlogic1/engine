/**
	Scene Object Factory creates scene objects (sprites, texts etc.)
	@author mlogic1
	@date 26.7.2020.
*/

#ifndef SCENE_OBJECT_FACTORY_H
#define SCENE_OBJECT_FACTORY_H

#include "Rect.h"
#include <glad/glad.h>
#include <string>

namespace Engine
{
    class SceneObject;
    class Sprite;
    class TextObject;

	class SceneObjectFactory final
	{
	public:
        static SceneObject* CreateSprite(Rect spriteRect, GLuint textureID);
        static SceneObject* CreateTextObject(Rect objectRect, std::string text = "");
	};
}

#endif // SCENE_OBJECT_FACTORY_H
