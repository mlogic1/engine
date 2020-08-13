#include "SceneLoader.h"
#include "Constants.h"
#include "Log.h"
#include "SystemBase.h"

namespace Engine
{
    std::vector<SceneObject*> SceneLoader::LoadScene(const std::string& sceneName)
    {
        std::vector<SceneObject*> sceneObjects;

        const std::string sceneFileName = std::string(PATH_SCENES) + sceneName;
        std::string sceneDataStr("");
        System::SYSTEM_PTR->LoadStringDataFromAssets(sceneFileName, sceneDataStr);

        nlohmann::json sceneData = nlohmann::json::parse(sceneDataStr);
        nlohmann::json sceneObjectsData = sceneData.at("SceneObjects");

        try
        {
            for (auto data : sceneObjectsData.items())
			{
                std::string objectType = data.value()["type"];
                nlohmann::json obj = data.value();

                if (objectType == TYPE_SPRITE)
                {
                    SpriteData spriteData = ParseSprite(data.value());
                    
                    std::vector<SceneObject*> nestedObjects;
                    SceneObject* object = SceneObjectFactory::CreateSprite(spriteData);
                    
                    sceneObjects.push_back(object);
                }
                else if (objectType == TYPE_TEXT_OBJECT)
                {
                    std::string id = data.value()["id"];
                    std::string text = data.value()["text"];

                    Rect objectRect;
                    objectRect.x = data.value()["rect"]["x"];
                    objectRect.y = data.value()["rect"]["y"];
                    objectRect.w = data.value()["rect"]["w"];
                    objectRect.h = data.value()["rect"]["h"];

                    std::vector<SceneObject*> nestedObjects;
                    sceneObjects.push_back(SceneObjectFactory::CreateTextObject(id, objectRect, nestedObjects, text));
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
    
    SpriteData SceneLoader::ParseSprite(nlohmann::json data)
    {
        SpriteData objectData;
        
        std::string id = data["id"];
        std::string textureIDStr = data["texture"];
        GLuint textureID = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureIDStr);

        Rect spriteRect;
        spriteRect.x = data["rect"]["x"];
        spriteRect.y = data["rect"]["y"];
        spriteRect.w = data["rect"]["w"];
        spriteRect.h = data["rect"]["h"];
        
        objectData.id = id;
        objectData.texture = textureID;
        objectData.rect = spriteRect;
        

        bool containsNested = data.contains("nested_objects");
        
        if (containsNested)
        {
            for (auto nestedData : data["nested_objects"])
            {
                objectData.nestedObjects.push_back(ParseSprite(nestedData));
            }
        }

        return objectData;
    }

    TextObjectData SceneLoader::ParseTextObject(nlohmann::json data)
    {
        return TextObjectData();
    }
}
