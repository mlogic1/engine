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

	void Scene::InstantiateSprite(Sprite* sprite)
	{
		m_sprites.push_back(sprite);
	}

	void Scene::InstantiateSprite(Shader* shader, Rect rect, std::string texture)
	{
		m_sprites.push_back(new Sprite(shader, rect, texture));
	}
}
