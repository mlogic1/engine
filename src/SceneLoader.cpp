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
                    SceneObject* object = SceneObjectFactory::CreateSprite(spriteData);
                    sceneObjects.push_back(object);
                }
                else if (objectType == TYPE_TEXT_OBJECT)
                {
                    TextObjectData objectData = ParseTextObject(data.value());
                    SceneObject* object = SceneObjectFactory::CreateTextObject(objectData);
                    sceneObjects.push_back(object);
                }
                else if (objectType == TYPE_ANIMATED_SPRITE)
                {
                    AnimatedSpriteData spriteData = ParseAnimatedSprite(data.value());
                    SceneObject* object = SceneObjectFactory::CreateAnimatedSprite(spriteData);
                    sceneObjects.push_back(object);
                }
                else if (objectType == TYPE_BUTTON)
                {
                    ButtonObjectData buttonData = ParseButtonObject(data.value());
                    SceneObject* object = SceneObjectFactory::CreateButton(buttonData);
                    sceneObjects.push_back(object);
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
                objectData.nestedObjects.push_back(ParseSprite(nestedData));    // wrong
            }
        }

        return objectData;
    }

    AnimatedSpriteData SceneLoader::ParseAnimatedSprite(nlohmann::json data)
    {
        AnimatedSpriteData objectData;

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
        objectData.frameCount = data["frame_count"];
        objectData.frameTime = data["frame_time"];
        objectData.frameWidth = data["frame_width"];
        objectData.frameHeight = data["frame_height"];
        objectData.textureCols = data["frame_cols"];
        objectData.textureRows = data["frame_rows"];

        bool containsNested = data.contains("nested_objects");

        if (containsNested)
        {
            for (auto nestedData : data["nested_objects"])
            {
                objectData.nestedObjects.push_back(ParseAnimatedSprite(nestedData));    // wrong
            }
        }

        return objectData;
    }

    TextObjectData SceneLoader::ParseTextObject(nlohmann::json data)
    {
        TextObjectData objectData;

        const std::string id = data["id"];
        Rect objectRect;
        objectRect.x = data["rect"]["x"];
        objectRect.y = data["rect"]["y"];
        objectRect.w = data["rect"]["w"];
        objectRect.h = data["rect"]["h"];

        const std::string text = data["text"];

        objectData.id = id;
        objectData.rect = objectRect;

        bool containsNested = data.contains("nested_objects");

        if (containsNested)
        {
            for (auto nestedData : data["nested_objects"])
            {
                // TODO
            }
        }

        return objectData;
    }

    ButtonObjectData SceneLoader::ParseButtonObject(nlohmann::json data)
    {
        ButtonObjectData buttonData;

        std::string id = data["id"];
        const std::string textureStrIdle = data["texture_idle"];
        const std::string textureStrHover = data["texture_hover"];
        const std::string textureStrPressed = data["texture_pressed"];
        const std::string textureStrDisabled = data["texture_disabled"];

        GLuint textureIDIdle = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureStrIdle);
        GLuint textureIDHover = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureStrHover);
        GLuint textureIDPressed = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureStrPressed);
        GLuint textureIDDisabled = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureStrDisabled);

        Rect buttonRect;
        buttonRect.x = data["rect"]["x"];
        buttonRect.y = data["rect"]["y"];
        buttonRect.w = data["rect"]["w"];
        buttonRect.h = data["rect"]["h"];

        buttonData.id = id;
        buttonData.rect = buttonRect;
        buttonData.textureMap.emplace(ButtonState::IDLE, textureIDIdle);
        buttonData.textureMap.emplace(ButtonState::HOVER, textureIDHover);
        buttonData.textureMap.emplace(ButtonState::PRESSED, textureIDPressed);
        buttonData.textureMap.emplace(ButtonState::DISABLED, textureIDDisabled);

        bool hasText = data.contains("text");

        if (hasText)
        {
            buttonData.text = data["text"];
        }

        bool containsNested = data.contains("nested_objects");

        if (containsNested)
        {
            for (auto nestedData : data["nested_objects"])
            {
                buttonData.nestedObjects.push_back(ParseButtonObject(nestedData)); // wrong
            }
        }

        return buttonData;
    }
}
