#include "Scene.h"
#include "Log.h"
#include <glad/glad.h>

namespace SceneSystem
{
	Scene::Scene(const char* SceneName) : m_sceneName(SceneName)
	{
		m_gameCamera = new GameCamera();
	}

	Scene::~Scene()
	{
	}

	void Scene::OnKey(System::Key Key)
	{
	}

}
