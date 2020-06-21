/**
	A single scene that's being rendered to the window. Any game scenes should inherit this class.

	@author mlogic1
	@date 16.06.2019.
*/

#ifndef SCENE_H
#define SCENE_H

#include "GameCamera.h"
#include "IInputReceiver.h"
#include "Key.h"
#include "Shader.h"
#include "Sprite.h"
#include "Rect.h"
#include <string>
#include <vector>

namespace SceneSystem
{
	class Scene : public System::IInputReceiver
	{
	public:
		Scene(const char* SceneName);
		virtual ~Scene();

		void Update();
		void Render();
		virtual void ReceiveKeyInput(System::Key Key) override;
		void InstantiateSprite(Sprite* sprite);
		void InstantiateSprite(Shader* shader, Rect rect, const GLuint& textureID);
		void RemoveSprite(const std::string& spriteID);

	protected:
		virtual void UpdateScene() = 0;
		virtual void RenderScene() = 0;

	protected:
		std::string m_sceneName;
		GameCamera* m_gameCamera;
		std::vector<Sprite*> m_sprites;
	};
}

#endif // SCENE_H

