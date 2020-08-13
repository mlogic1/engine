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
#include <vector>

namespace Engine
{
    class SceneObject;
    class Sprite;
    class TextObject;

    struct SpriteData
    {
        std::string id;
        Rect rect;
        GLuint texture;
        std::vector<SpriteData> nestedObjects;
    };

    struct TextObjectData
    {
        std::string id;
        Rect rect;
        std::string text;
        std::vector<TextObjectData> nestedObjects;
    };

	class SceneObjectFactory final
	{
	public:
        static SceneObject* CreateSprite(SpriteData spriteData);
        static SceneObject* CreateTextObject(std::string objectID, Rect objectRect, std::vector<SceneObject*> nestedObjects, std::string text = "");
	};
}

#endif // SCENE_OBJECT_FACTORY_H
