/**
	Text Object Factory creates Text Scene objects
	@author mlogic1
	@date 26.7.2020.
*/

#ifndef TEXT_OBJECT_FACTORY_H
#define TEXT_OBJECT_FACTORY_H

#include "Shader.h"
#include "TextObject.h"
#include "Rect.h"
#include <glad/glad.h>
#include <string>

namespace Engine
{
	class TextObjectFactory
	{
	public:
		static TextObject* Create(Rect objectRect, std::string text = "");
	};
}

#endif // TEXT_OBJECT_FACTORY_H