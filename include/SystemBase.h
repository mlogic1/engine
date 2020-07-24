#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H

#include "IInputReceiver.h"
#include "SceneManager.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Vector2.h"
#include <string>

namespace System
{
	/*enum SystemType
	{
		DESKTOP = 0,
		ANDROID
	};*/

	enum GLRenderMode
	{
		LetterBox = 0,
		Virtual4By3 = 1,
		Stretch
	};

	class SystemBase : public IInputReceiver
	{
	public:
		virtual bool InitSystem() = 0;
		
		void InitSceneManager();
		void InitShaderManager();
		void InitTextureManager();
		void InitFontManager();

		virtual void Update() = 0;
		virtual bool IsRunning() = 0;
		const GLRenderMode& GetRenderMode();
		void ReceiveKeyInput(Key key) override;
		// TODO getsystemtype
		SceneSystem::SceneManager* m_sceneManager;	// TODO move to proctected part

		const Engine::ShaderManager* GetShaderManager() const;
		const Engine::TextureManager* GetTextureManager() const;
		const Engine::FontManager* GetFontManager() const;

		virtual bool LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length) const = 0;
		virtual bool LoadStringDataFromAssets(const std::string fileName, std::string& data) const  = 0;
		

	protected:
		// rendering mode // TODO maybe move this to a global configuration source file
		GLRenderMode _RenderMode = GLRenderMode::LetterBox;
		Engine::ShaderManager* m_shaderManager = nullptr;
		Engine::TextureManager* m_textureManager = nullptr;
		Engine::FontManager* m_fontManager = nullptr;

	private:
		// cursor
		Vector2f m_cursorPosition{-1.0f, -1.0f};
	};

	extern SystemBase* SYSTEM_PTR;
	bool InitGameEngine();
}

#endif // SYSTEM_H
