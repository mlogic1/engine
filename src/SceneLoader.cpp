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

        tinyxml2::XMLDocument sceneDoc;
        sceneDoc.Parse(sceneDataStr.c_str());
        tinyxml2::XMLError error = sceneDoc.ErrorID();
        if (error != tinyxml2::XMLError::XML_SUCCESS)
        {
            Log::Write("Failed to parse " + sceneFileName + ". Faulty object.", Log::LogType::ERR);
            throw std::string("SceneLoader: Failed parsing scene file");
        }

        tinyxml2::XMLElement* sceneRootElement = sceneDoc.FirstChildElement("Scene");
        if (!sceneRootElement)
        {
            throw std::string("Error: Scene root object not found in scene");
        }
           
        if (sceneRootElement->NoChildren())
        {
            Log::Write("Scene has no objects", Log::LogType::WARNING);
            return sceneObjects;
        }

        for (tinyxml2::XMLElement* sceneObjectElement = sceneRootElement->FirstChildElement(); sceneObjectElement != nullptr; sceneObjectElement = sceneObjectElement->NextSiblingElement())
        {
            SceneObject* sceneObject = ParseElement(sceneObjectElement);
            sceneObjects.push_back(sceneObject);
        }

        return sceneObjects;
    }

    // TODO: some sort of id checking
    SceneObject* SceneLoader::ParseElement(tinyxml2::XMLElement* element)
    {
        SceneObject* sceneObject = nullptr;
        const char* objectType = element->Name();

        if (strcmp(objectType, TYPE_SPRITE) == 0)
        {
            SpriteData objectData = ParseSprite(element);
            sceneObject = SceneObjectFactory::CreateSprite(objectData);
        }
        else if (strcmp(objectType, TYPE_ANIMATED_SPRITE) == 0)
        {
            AnimatedSpriteData objectData = ParseAnimatedSprite(element);
            sceneObject = SceneObjectFactory::CreateAnimatedSprite(objectData);
        }
        else if (strcmp(objectType, TYPE_TEXT_OBJECT) == 0)
        {
            TextObjectData objectData = ParseTextObject(element);
            sceneObject = SceneObjectFactory::CreateTextObject(objectData);
        }
        else if (strcmp(objectType, TYPE_BUTTON) == 0)
        {
            ButtonObjectData objectData = ParseButtonObject(element);
            sceneObject = SceneObjectFactory::CreateButton(objectData);
        }
        else
        {
            Log::Write("Unsupported object type in scene: " + std::string(objectType), Log::ERR);
        }

        // children
        for (tinyxml2::XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            SceneObject* childObject = ParseElement(child);
            sceneObject->AddNestedObject(childObject);
        }

        return sceneObject;
    }

    SpriteData SceneLoader::ParseSprite(tinyxml2::XMLElement* element)
    {
        SpriteData objectData;

        std::string id = element->FindAttribute("id")->Value();
        std::string textureIDStr = element->FindAttribute("texture")->Value();
        GLuint textureID = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureIDStr);
        
        Rect spriteRect;
        element->FindAttribute("x")->QueryIntValue(&spriteRect.x);
        element->FindAttribute("y")->QueryIntValue(&spriteRect.y);
        element->FindAttribute("w")->QueryIntValue(&spriteRect.w);
        element->FindAttribute("h")->QueryIntValue(&spriteRect.h);

        objectData.id = id;
        objectData.texture = textureID;
        objectData.rect = spriteRect;

        return objectData;
    }

    AnimatedSpriteData SceneLoader::ParseAnimatedSprite(tinyxml2::XMLElement* element)
    {
        AnimatedSpriteData objectData;

        std::string id = element->FindAttribute("id")->Value();
        std::string textureIDStr = element->FindAttribute("texture")->Value();
        GLuint textureID = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureIDStr);

        Rect spriteRect;
        element->FindAttribute("x")->QueryIntValue(&spriteRect.x);
        element->FindAttribute("y")->QueryIntValue(&spriteRect.y);
        element->FindAttribute("w")->QueryIntValue(&spriteRect.w);
        element->FindAttribute("h")->QueryIntValue(&spriteRect.h);

        objectData.id = id;
        objectData.texture = textureID;
        objectData.rect = spriteRect;

        element->FindAttribute("frame_count")->QueryIntValue(&objectData.frameCount);
        element->FindAttribute("frame_time")->QueryFloatValue(&objectData.frameTime);
        element->FindAttribute("frame_width")->QueryIntValue(&objectData.frameWidth);
        element->FindAttribute("frame_height")->QueryIntValue(&objectData.frameHeight);
        element->FindAttribute("frame_cols")->QueryIntValue(&objectData.textureCols);
        element->FindAttribute("frame_rows")->QueryIntValue(&objectData.textureRows);

        return objectData;
    }

    TextObjectData SceneLoader::ParseTextObject(tinyxml2::XMLElement* element)
    {
        TextObjectData objectData;

        const std::string id = element->FindAttribute("id")->Value();
        Rect objectRect;
        element->FindAttribute("x")->QueryIntValue(&objectRect.x);
        element->FindAttribute("y")->QueryIntValue(&objectRect.y);
        element->FindAttribute("w")->QueryIntValue(&objectRect.w);
        element->FindAttribute("h")->QueryIntValue(&objectRect.h);

        const std::string text = element->FindAttribute("text")->Value();

        objectData.id = id;
        objectData.rect = objectRect;

        return objectData;
    }

    ButtonObjectData SceneLoader::ParseButtonObject(tinyxml2::XMLElement* element)
    {
        ButtonObjectData buttonData;

        std::string id = element->FindAttribute("id")->Value();
        const std::string textureStrIdle = element->FindAttribute("texture_idle")->Value();
        const std::string textureStrHover = element->FindAttribute("texture_hover")->Value();
        const std::string textureStrPressed = element->FindAttribute("texture_pressed")->Value();
        const std::string textureStrDisabled = element->FindAttribute("texture_disabled")->Value();

        GLuint textureIDIdle = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureStrIdle);
        GLuint textureIDHover = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureStrHover);
        GLuint textureIDPressed = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureStrPressed);
        GLuint textureIDDisabled = System::SYSTEM_PTR->GetTextureManager()->GetTexture(textureStrDisabled);

        Rect buttonRect;
        element->FindAttribute("x")->QueryIntValue(&buttonRect.x);
        element->FindAttribute("y")->QueryIntValue(&buttonRect.y);
        element->FindAttribute("w")->QueryIntValue(&buttonRect.w);
        element->FindAttribute("h")->QueryIntValue(&buttonRect.h);

        buttonData.id = id;
        buttonData.rect = buttonRect;
        buttonData.textureMap.emplace(ButtonState::IDLE, textureIDIdle);
        buttonData.textureMap.emplace(ButtonState::HOVER, textureIDHover);
        buttonData.textureMap.emplace(ButtonState::PRESSED, textureIDPressed);
        buttonData.textureMap.emplace(ButtonState::DISABLED, textureIDDisabled);

        const tinyxml2::XMLAttribute* textAttribute = element->FindAttribute("text");

        if (textAttribute)
        {
            buttonData.text = textAttribute->Value();
        }

        return buttonData;
    }
}
