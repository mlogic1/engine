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

    void SceneObject::update(float deltaTime)
    {

    }

    bool SceneObject::GetVisible()
    {
        return m_isVisible;
    }

    Vector2f SceneObject::GetPosition()
    {
        return m_position;
    }

    Vector2f SceneObject::GetSize()
    {
        return m_size;
    }

    std::string SceneObject::GetID()
    {
        return m_objectID;
    }

    void SceneObject::SetVisible(bool visibleState)
    {
        m_isVisible = visibleState;
    }

    void SceneObject::SetPosition(Vector2f position)
    {
        m_position = position;
    }

    void SceneObject::SetSize(Vector2f size)
    {
        m_size = size;
    }
}
