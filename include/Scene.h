/**
	A single scene that's being rendered to the window. Any game scenes should inherit this class.

	@author mlogic1
	@date 16.06.2019.
*/

#ifndef SCENE_H
#define SCENE_H

#include "GameCamera.h"
#include "Key.h"
#include "Shader.h"
#include "Sprite.h"
#include "Rect.h"
#include <string>
#include <vector>

namespace SceneSystem
{
	class Scene
	{
	public:
		Scene(const char* SceneName);
		virtual ~Scene();

		virtual void UpdateScene() = 0;
		virtual void DrawScene() = 0;
		virtual void OnKey(System::Key Key);
		void InstantiateSprite(Sprite* sprite);
		void InstantiateSprite(Shader* shader, Rect rect, std::string texture);

	protected:
		std::string m_sceneName;
		GameCamera *m_gameCamera;
		std::vector<Sprite*> m_sprites;
	};
}

#endif // !SCENE_H

