#include "SceneObject.h"
#include "Constants.h"

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

    void SceneObject::AddNestedObject(SceneObject* object)
    {
        m_nestedObjects.push_back(object);
    }

    const std::vector<SceneObject*>& SceneObject::GetNestedObjects()
    {
        return m_nestedObjects;
    }

    void SceneObject::GetNormalizedCoordinates(float(&arr)[20])
    {
        float normX, normY;
        normX = (m_position.x - VIRTUAL_RESOLUTION_WIDTH / 2.0f) / (VIRTUAL_RESOLUTION_WIDTH / 2.0f);
        normY = (m_position.y - VIRTUAL_RESOLUTION_HEIGHT / 2.0f) / (VIRTUAL_RESOLUTION_HEIGHT / 2.0f);

        float normW, normH;
        normW = (m_position.x + m_size.x - VIRTUAL_RESOLUTION_WIDTH / 2.0f) / (VIRTUAL_RESOLUTION_WIDTH / 2.0f);
        normH = (m_position.y + m_size.y - VIRTUAL_RESOLUTION_HEIGHT / 2.0f) / (VIRTUAL_RESOLUTION_HEIGHT / 2.0f);

        float tlX = normX, tlY = normY * -1.0f;
        float trX = normW, trY = normY * -1.0f;

        float blX = normX, blY = normH * -1.0f;
        float brX = normW, brY = normH * -1.0f;

        float vertices[20] =
        {
            // position          // texture     // stride = 5 floats
            trX, trY,  1.0f,   1.0f, 1.0f,    // top right corner
            brX, brY, 1.0f,   1.0f, 0.0f,    // bottom right corner
            blX, blY, 1.0f,   0.0f, 0.0f,   // bottom left corner
            tlX, tlY,  1.0f,   0.0f, 1.0f    // top left corner
        };

        for (int i = 0; i < 20; ++i)
        {
            arr[i] = vertices[i];
        }
    }
}
