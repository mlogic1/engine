#include "SceneManager.h"
#include <glad/glad.h>

#include "Constants.h"
#include "SceneMainMenu.h"

namespace SceneSystem
{
	void SceneManager::Update()
	{
		if (this->m_currentScene != nullptr)
		{
			this->m_currentScene->UpdateScene();
			this->m_currentScene->DrawScene();
		}
	}

	void SceneManager::SwitchScene(Scene * newScene)
	{
		this->m_currentScene = newScene;
	}

	void SceneManager::OnKey(System::Key Key)
	{
		this->m_currentScene->OnKey(Key);
	}


	SceneManager::SceneManager()
	{
	}


	SceneManager::~SceneManager()
	{
	}
}