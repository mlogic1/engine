/**
	Scene loader loads scene json data, parses it, and instantiates all scene objects

	@author mlogic1
	@date 04.08.2020.
*/

#include "SceneObject.h"
#include "Rect.h"
#include "SceneObjectFactory.h"
#include <glad/glad.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Engine
{
    class SceneLoader final
    {
        public:
            static std::vector<SceneObject*> LoadScene(const std::string& sceneName);

        private:
            static const constexpr char* TYPE_SPRITE = "Sprite";
            static const constexpr char* TYPE_ANIMATED_SPRITE = "AnimatedSprite";
            static const constexpr char* TYPE_TEXT_OBJECT = "TextObject";

            static SpriteData ParseSprite(nlohmann::json data);
            static AnimatedSpriteData ParseAnimatedSprite(nlohmann::json data);
            static TextObjectData ParseTextObject(nlohmann::json data);
    };
}
