// TODO specific scenes need to be moved to main project

#ifndef SCENE_MAIN_MENU_H
#define SCENE_MAIN_MENU_H

#include "Scene.h"
#include "Shader.h"
#include "Sprite.h"
#include "TextureSet.h"


namespace SceneSystem
{
	class SceneMainMenu final : public Scene
	{
	public:
		SceneMainMenu(const char*  sceneName);
		~SceneMainMenu();

		void UpdateScene();
		void DrawScene();
		void OnKey(System::Key Key);

	private:
		Shader *mainShader;
		Shader *orthoShader;
		Sprite *mainSprite;
		Sprite *bgSprite;
		
		TextureSet* t;
	};

}
#endif // SCENE_MAIN_MENU_H