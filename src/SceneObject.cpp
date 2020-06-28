#include "SceneObject.h"


namespace Engine
{
    SceneObject::SceneObject(Rect objectRect) :
        m_position(objectRect.x, objectRect.y),
        m_size(objectRect.w, objectRect.h)
    {

    }

	SceneObject::SceneObject(Vector2f objectPosition, Vector2f objectSize) :
        m_position(objectPosition),
        m_size(objectSize)
	{

	}

    SceneObject::~SceneObject()
    {

    }
}
