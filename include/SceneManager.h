/**
	Scene manager handles scene updates, rendering and switching

	@author mlogic1
	@date 16.06.2019.
*/

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "IInputReceiver.h"

namespace SceneSystem
{
	class SceneManager : public System::IInputReceiver
	{
	public:
		SceneManager(const System::SystemBase& systemRef);
		SceneManager(const SceneManager& SceneManager) = delete;
		~SceneManager();

		void Update();
		void SwitchScene(Scene* newScene);
		void ReceiveKeyInput(System::Key Key) override;

	private:
		const System::SystemBase& m_systemRef;
		Scene* m_currentScene = nullptr;
	};
}

#endif // SCENE_MANAGER_H
