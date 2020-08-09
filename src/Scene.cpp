#include "Scene.h"
#include "Log.h"
#include "SceneLoader.h"
#include "SceneObjectFactory.h"
#include <glad/glad.h>

namespace SceneSystem
{
	Scene::Scene(const std::string& SceneName, const std::string& sceneFileName) : m_sceneName(SceneName)
	{
		m_gameCamera = new GameCamera();


		m_sceneObjects = Engine::SceneLoader::LoadScene(sceneFileName);
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

	void Scene::InstantiateSprite(std::string objectID, Rect rect, const GLuint& textureID)
	{
		m_sceneObjects.push_back(Engine::SceneObjectFactory::CreateSprite(objectID, rect, textureID));
	}

	void Scene::InstantiateFontObject(std::string objectID, Rect fontRect, std::string text)
	{
		m_sceneObjects.push_back(Engine::SceneObjectFactory::CreateTextObject(objectID, fontRect, text));
	}

	void Scene::RemoveSprite(const std::string& spriteID)
	{
		// TODO implement
	}

	Engine::SceneObject* Scene::GetObject(const std::string& id)
	{
        for (Engine::SceneObject* object : m_sceneObjects)
        {
            if (object->GetID() == id)
            {
                return object;
            }
        }
        std::string error("Unable to find object by ID: " + id);
        throw error;
	}
}
