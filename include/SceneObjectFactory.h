/**
	Scene Object Factory creates scene objects (sprites, texts etc.)
	@author mlogic1
	@date 26.7.2020.
*/

#ifndef SCENE_OBJECT_FACTORY_H
#define SCENE_OBJECT_FACTORY_H

#include "Rect.h"
#include "Button.h"
#include <glad/glad.h>
#include <map>
#include <string>
#include <vector>

namespace Engine
{
    class SceneObject;
    class Sprite;
    class AnimatedSprite;
    class TextObject;

    struct SpriteData
    {
        std::string id;
        Rect rect;
        GLuint texture;
        std::vector<SpriteData> nestedObjects;
    };

    struct AnimatedSpriteData
    {
        std::string id;
        Rect rect;
        GLuint texture;
        int frameCount;
        float frameTime;
        int frameWidth;
        int frameHeight;
        int textureRows;
        int textureCols;
        std::vector<AnimatedSpriteData> nestedObjects;
    };

    struct TextObjectData
    {
        std::string id;
        Rect rect;
        std::string text;
        std::vector<TextObjectData> nestedObjects;
    };

    struct ButtonObjectData
    {
        std::string id;
        Rect rect;
        std::map<ButtonState, GLuint> textureMap;
        std::string text;
        std::vector<ButtonObjectData> nestedObjects;
    };

	class SceneObjectFactory final
	{
	public:
        static SceneObject* CreateSprite(SpriteData spriteData);
        static SceneObject* CreateAnimatedSprite(AnimatedSpriteData spriteData);
        static SceneObject* CreateTextObject(std::string objectID, Rect objectRect, std::vector<SceneObject*> nestedObjects, std::string text = "");
        static SceneObject* CreateButton(ButtonObjectData buttonData);
	};
}

#endif // SCENE_OBJECT_FACTORY_H
