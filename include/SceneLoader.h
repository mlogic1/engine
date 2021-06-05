/**
	Scene loader loads scene json data, parses it, and instantiates all scene objects

	@author mlogic1
	@date 04.08.2020.
*/

#include "SceneObject.h"
#include "Rect.h"
#include "SceneObjectFactory.h"
#include <glad/glad.h>
#include <string>
#include <vector>
#include <tinyxml2.h>

namespace Engine
{
    class SceneLoader final
    {
        public:
            static std::vector<SceneObject*> LoadScene(const std::string& sceneName);

        private:
            static constexpr const char* TYPE_SPRITE = "Sprite";
            static constexpr const char* TYPE_ANIMATED_SPRITE = "AnimatedSprite";
            static constexpr const char* TYPE_TEXT_OBJECT = "TextObject";
            static constexpr const char* TYPE_BUTTON = "Button";

            static SceneObject* ParseElement(tinyxml2::XMLElement* element);
            static SpriteData ParseSprite(tinyxml2::XMLElement* element);
            static AnimatedSpriteData ParseAnimatedSprite(tinyxml2::XMLElement* element);
            static TextObjectData ParseTextObject(tinyxml2::XMLElement* element);
            static ButtonObjectData ParseButtonObject(tinyxml2::XMLElement* element);
    };
}
