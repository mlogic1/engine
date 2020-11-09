#include "SystemBase.h"

namespace System
{
	SystemBase* SYSTEM_PTR = nullptr;

	void SystemBase::InitSceneManager()
	{
		m_sceneManager = new SceneSystem::SceneManager(*this);
	}

	void SystemBase::InitShaderManager()
	{
		m_shaderManager = new Engine::ShaderManager(*this);
	}

	void SystemBase::InitTextureManager()
	{
		m_textureManager = new Engine::TextureManager(*this);
	}

	void SystemBase::InitFontManager()
	{
        m_fontManager = new Engine::FontManager(*this);
	}

	const GLRenderMode& SystemBase::GetRenderMode()
	{
		return _RenderMode;
	}

	void SystemBase::ReceiveKeyInput(Key key)
	{
		m_sceneManager->ReceiveKeyInput(key);
	}

    float SystemBase::GetDeltaTime() const
    {
        return m_deltaTime;
    }

    float SystemBase::GetFPS() const
    {
        return m_FPS;
    }

	const Vector2f& SystemBase::GetCursorPosition() const
	{
		return m_cursorPosition;
	}

	const Engine::ShaderManager* SystemBase::GetShaderManager() const
	{
		return m_shaderManager;
	}

	const Engine::TextureManager* SystemBase::GetTextureManager() const
	{
		return m_textureManager;
	}

	const Engine::FontManager* SystemBase::GetFontManager() const
	{
		return m_fontManager;
	}
}
