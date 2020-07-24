#include "SceneManager.h"
#include "SystemBase.h"
#include "Constants.h"
#include <glad/glad.h>

namespace SceneSystem
{
	SceneManager::SceneManager(const System::SystemBase& systemRef) :
		m_systemRef(systemRef)
	{

	}

	SceneManager::~SceneManager()
	{

	}

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

	void SceneManager::ReceiveKeyInput(System::Key Key)
	{
		this->m_currentScene->ReceiveKeyInput(Key);
	}
}