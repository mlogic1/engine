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
		for (Sprite* sprite : m_sprites)
		{
			sprite->update(0.0016);
		}
		UpdateScene();
	}

	void Scene::Render()
	{
		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glDisable(GL_DEPTH_TEST);
		for (Sprite* sprite : m_sprites)
		{
			sprite->render();
		}
		RenderScene();
	}

	void Scene::OnKey(System::Key Key)
	{
	}

	void Scene::InstantiateSprite(Sprite* sprite)
	{
		m_sprites.push_back(sprite);
	}

	void Scene::InstantiateSprite(Shader* shader, Rect rect, const GLuint& textureID)
	{
		m_sprites.push_back(new Sprite(shader, rect, textureID));
	}

	void Scene::RemoveSprite(const std::string& spriteID)
	{
		// TODO implement
	}
}
