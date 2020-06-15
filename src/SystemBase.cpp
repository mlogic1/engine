#include "SystemBase.h"

namespace System
{
	SystemBase* SYSTEM_PTR = nullptr;

	void SystemBase::InitShaderManager()
	{
		m_shaderManager = new Engine::ShaderManager(*this);
	}

	void SystemBase::InitTextureManager()
	{
		m_textureManager = new Engine::TextureManager(*this);
	}

	const GLRenderMode & SystemBase::GetRenderMode()
	{
		return _RenderMode;
	}
}