#include "SceneManager.h"
#include "Constants.h"
#include "Log.h"
#include "SystemBase.h"
#include <nlohmann/json.hpp>
#include <glad/glad.h>
#include <vector>

namespace SceneSystem
{
	SceneManager::SceneManager(const System::SystemBase& systemRef) :
		m_systemRef(systemRef)
	{
        // TODO update this loader
        Log::Write("Initializing scene manager");
        std::string scenesJsonString;
        std::string pathJsonScenes = std::string(PATH_ASSETS) + std::string(ENGINE_FILE_SCENES);
        m_systemRef.LoadStringDataFromAssets(pathJsonScenes, scenesJsonString);

        std::vector<SceneDataRecord> scenesData;
        nlohmann::json scenesJsonData = nlohmann::json::parse(scenesJsonString);

        try
        {
            for (auto data : scenesJsonData.items())
			{
				std::string sceneName = data.key();
				std::string sceneFileName = data.value()["SceneFile"];
				std::string sceneInstance = data.value()["SceneInstance"];
				Log::Write("Loaded scene: " + sceneName);
				Log::Write("Loaded scene file name: " + sceneFileName);
				Log::Write("Loaded scene instance: " + sceneInstance);

				scenesData.push_back({ sceneName, sceneFileName, sceneInstance });
			}
        }
        catch (nlohmann::detail::exception& exception)
		{
			Log::Write("Failed to parse " + pathJsonScenes + ". Faulty object.", Log::LogType::ERR);
			Log::Write(exception.what());
			throw std::string("Scenemanager: Failed parsing scenes file");
		}

		// TODO check for duplicates

		for (const SceneDataRecord& data : scenesData)
		{
            m_scenes.emplace(data.SceneName, data);
		}

		// TODO initialize starting scene
	}

	SceneManager::~SceneManager()
	{

	}

	void SceneManager::Update(float dt)
	{
		if (this->m_currentScene != nullptr)
		{
			this->m_currentScene->Update(dt);
			this->m_currentScene->Render();
		}
	}

	void SceneManager::SwitchScene(Scene* newScene)
	{
		this->m_currentScene = newScene;
	}

	void SceneManager::SwitchScene(std::string newScene)
	{
        Log::Write("Switching scene: " + newScene);
        if (m_scenes.find(newScene) != m_scenes.end())
        {
            std::cout << "Key " + newScene + " found\n";
        }
        else
        {
            throw std::string("Attemping to switch to non existing scene: " + newScene);
        }



	}

	void SceneManager::ReceiveKeyInput(System::Key Key)
	{
		this->m_currentScene->ReceiveKeyInput(Key);
	}
}
