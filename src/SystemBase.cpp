#include "SystemBase.h"

namespace System
{
	SystemBase* SYSTEM_PTR = nullptr;
	const GLRenderMode & SystemBase::GetRenderMode()
	{
		return _RenderMode;
	}
}