#include "SceneLoader.h"
#include "Constants.h"
#include "Log.h"
#include "SceneObjectFactory.h"
#include "SystemBase.h"
#include <glad/glad.h>
#include <nlohmann/json.hpp>

namespace Engine
{
    std::vector<SceneObject*> SceneLoader::LoadScene(const std::string& sceneName)
    {
        std::vector<SceneObject*> sceneObjects;

        const std::string sceneFileName = std::string(PATH_SCENES) + sceneName;
        std::string sceneDataStr("");
        System::SYSTEM_PTR->LoadStringDataFromAssets(sceneFileName, sceneDataStr);
        Log::Write("Loaded scene data: ");
        Log::Write(sceneDataStr);

        nlohmann::json sceneData = nlohmann::json::parse(sceneDataStr);
        nlohmann::json sceneObjectsData = sceneData.at("SceneObjects");

        try
        {
            for (auto data : sceneObjectsData.items())
			{
                std::string objectType = data.value()["type"];

                if (objectType == "Sprite")
                {
                    std::string id = data.value()["id"];
                    std::string textureIDStr = data.value()["texture"];
                    Log::Write("requested texture: " + textureIDStr);
                    GLuint textureID = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureIDStr);

                    Rect spriteRect;
                    spriteRect.x = data.value()["rect"]["x"];
                    spriteRect.y = data.value()["rect"]["y"];
                    spriteRect.w = data.value()["rect"]["w"];
                    spriteRect.h = data.value()["rect"]["h"];

                    sceneObjects.push_back(SceneObjectFactory::CreateSprite(spriteRect, textureID));
                }
                else if (objectType == "TextObject")
                {
                    std::string id = data.value()["id"];
                    std::string text = data.value()["text"];

                    Rect objectRect;
                    objectRect.x = data.value()["rect"]["x"];
                    objectRect.y = data.value()["rect"]["y"];
                    objectRect.w = data.value()["rect"]["w"];
                    objectRect.h = data.value()["rect"]["h"];

                    sceneObjects.push_back(SceneObjectFactory::CreateTextObject(objectRect, text));
                }
                else
                {
                    Log::Write("Unsupported object type in scene: " + objectType, Log::ERR);
                }
			}
        }
        catch (nlohmann::detail::exception& exception)
		{
			Log::Write("Failed to parse " + sceneFileName + ". Faulty object.", Log::LogType::ERR);
			Log::Write(exception.what());
			throw std::string("SceneLoader: Failed parsing scene file");
		}

        return sceneObjects;
    }
}
