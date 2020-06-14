#include "SceneManager.h"
#include "Constants.h"
#include <glad/glad.h>

namespace SceneSystem
{
	void SceneManager::Update()
	{
		if (this->m_currentScene != nullptr)
		{
			this->m_currentScene->Update();
			this->m_currentScene->Render();
		}
	}

	void SceneManager::SwitchScene(Scene* newScene)
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