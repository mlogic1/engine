/**
	A single scene that's being rendered to the window. Any game scenes should inherit this class.

	@author mlogic1
	@date 16.06.2019.
*/

#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <string>
#include <vector>

#include "GameCamera.h"
#include "Key.h"

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

		protected:
			std::string m_sceneName;
			GameCamera *m_gameCamera;
			std::vector<GameObject*> m_gameObjects;

	};
}

#endif // !SCENE_H

