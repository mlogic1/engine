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

	void Scene::Update()
	{
		this->m_gameCamera->update(0.016f);
		for (Engine::SceneObject* object : m_sceneObjects)
		{
			object->update(0.0016);
		}
		UpdateScene();
	}

	void Scene::Render()
	{
		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glDisable(GL_DEPTH_TEST);
		for (Engine::SceneObject* sprite : m_sceneObjects)
		{
			sprite->render();
		}
		RenderScene();
	}

	void Scene::ReceiveKeyInput(System::Key Key)
	{

	}

	void Scene::InstantiateSprite(Engine::Sprite* sprite)
	{
		m_sceneObjects.push_back(sprite);
	}

	void Scene::InstantiateSprite(Shader* shader, Rect rect, const GLuint& textureID)
	{
		m_sceneObjects.push_back(new Engine::Sprite(shader, rect, textureID));
	}

	void Scene::RemoveSprite(const std::string& spriteID)
	{
		// TODO implement
	}
}
