/**
	Scene manager handles scene switching

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
		static SceneManager* GetSceneManager();

		void Update();
		void SwitchScene(Scene* newScene);
		void OnKey(System::Key Key);

	private:
		SceneManager();
		SceneManager(const SceneManager& SceneManager);
		~SceneManager();
		
		static SceneManager *m_instance;
		Scene* m_currentScene;

	};
	
}

#endif // SCENE_MANAGER_H