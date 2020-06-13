/**
	Scene manager handles scene updates, rendering and switching

	@author mlogic1
	@date 16.06.2019.
*/

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"

namespace SceneSystem
{
	class SceneManager
	{
	public:
		SceneManager();
		SceneManager(const SceneManager& SceneManager) = delete;
		~SceneManager();

		void Update();
		void SwitchScene(Scene* newScene);
		void OnKey(System::Key Key);

	private:
		Scene* m_currentScene = nullptr;
	};
}

#endif // SCENE_MANAGER_H