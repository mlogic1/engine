#include "SceneMainMenu.h"
#include "Log.h"
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <list>

namespace SceneSystem
{
	SceneMainMenu::SceneMainMenu(const char* sceneName) : Scene(sceneName)
	{
		try {
			mainShader = new Shader("StandardShaderVertex.vs", "StandardShaderFragment.fs");
			orthoShader = new Shader("OrthoShaderVertex.vs", "StandardShaderFragment.fs");

			Rect bgRect = { 0, 0, 1280, 720 };
			Rect spriteRect = { 650, 630, 632, 84 };

			mainSprite = new Sprite(orthoShader, spriteRect, "logo.png");
			bgSprite = new Sprite(orthoShader, bgRect, "bg.jpg");
		}
		catch (std::string err)
		{
			Log::Write(err, Log::LogType::ERR);
		}
		
		//std::list<std::string> addTextures = { "xdoge.png" };
		//t = new TextureSet(addTextures);
	}

	SceneMainMenu::~SceneMainMenu()
	{
	}

	void SceneMainMenu::UpdateScene()
	{
		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mainSprite->update(0.016f);
		bgSprite->update(0.016f);
		this->m_gameCamera->update(0.016f);

		glm::mat4 cameraProjection = m_gameCamera->getProjection();
		glm::mat4 cameraView = m_gameCamera->getMatrixView();

		mainShader->setMat4("projection", cameraProjection);
		mainShader->setMat4("view", cameraView);

		glm::mat4 model1 = glm::mat4(1.0f);
		glm::vec3 modelPositionTranslate1 = glm::vec3(4.1f, 0.1f, -2.5f);
		glm::vec3 modelPositionRotate1 = glm::vec3(0.0f, 1.0f, 0.75f);
		mainShader->setMat4("model", model1);
	}

	void SceneMainMenu::DrawScene()
	{
		// 2D - ortho sprites
		glDisable(GL_DEPTH_TEST);
		bgSprite->render();
		mainSprite->render();
		
		// 3D - projection sprites
		glEnable(GL_DEPTH_TEST);
		//mainSprite->render();
	}
	
	void SceneMainMenu::OnKey(System::Key Key)
	{
		Log::Write("A");
		
		GLuint nTexture = (*t)["xdoge.png"];
		mainSprite->SetTexture(nTexture);
	}
}