/**
	Scene manager handles scene updates, rendering and switching

	@author mlogic1
	@date 16.06.2019.
*/

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "IInputReceiver.h"
#include <map>
#include <string>

namespace SceneSystem
{
	class SceneManager : public System::IInputReceiver
	{
	public:
		SceneManager(const System::SystemBase& systemRef);
		SceneManager(const SceneManager& SceneManager) = delete;
		~SceneManager();

		void Update(float dt);
		void SwitchScene(Scene* newScene);
		void SwitchScene(std::string newScene);
		void OnKeyPressed(System::Key Key) override;
		void OnKeyReleased(System::Key Key) override;

	private:
		const System::SystemBase& m_systemRef;
		Scene* m_currentScene = nullptr;

		struct SceneDataRecord
        {
            std::string SceneName;
            std::string SceneFileName;
            std::string SceneInstance;
        };

		std::map<std::string, SceneDataRecord> m_scenes;
	};
}

#endif // SCENE_MANAGER_H
