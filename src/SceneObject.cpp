#include "SceneObject.h"
#include "Constants.h"
#include "Log.h"

namespace Engine
{
    SceneObject::SceneObject(Rect objectRect, std::string objectID, std::vector<SceneObject*> nestedObjects, SceneObject* parent) :
        m_position(objectRect.x, objectRect.y),
        m_size(objectRect.w, objectRect.h),
        m_objectID(objectID),
        m_nestedObjects(nestedObjects),
        m_parent(parent)
    {

    }

	SceneObject::SceneObject(Vector2f objectPosition, Vector2f objectSize, std::string objectID, std::vector<SceneObject*> nestedObjects, SceneObject* parent) :
        m_position(objectPosition),
        m_size(objectSize),
        m_objectID(objectID),
        m_nestedObjects(nestedObjects),
        m_parent(parent)
	{

	}

    SceneObject::~SceneObject()
    {

    }

    void SceneObject::update(float deltaTime)
    {
        for (SceneObject* nestedObject : m_nestedObjects)
        {
            nestedObject->update(deltaTime);
        }
    }

    bool SceneObject::GetVisible()
    {
        return m_isVisible;
    }

    Vector2f SceneObject::GetPosition()
    {
        return m_position;
    }

    Vector2f SceneObject::GetWorldPosition() const
    {
        Vector2f worldPosition = m_position;
        SceneObject* parent = GetParent();
        while (parent != nullptr)
        {
            worldPosition = worldPosition + parent->GetPosition();
            parent = parent->GetParent();
        }

        return worldPosition;
    }

    Vector2f SceneObject::GetSize()
    {
        return m_size;
    }

    std::string SceneObject::GetID() const
    {
        return m_objectID;
    }

    SceneObject* SceneObject::GetParent() const
    {
        return m_parent;
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
        object->m_parent = this;    // not nice
        m_nestedObjects.push_back(object);
    }

    const std::vector<SceneObject*>& SceneObject::GetNestedObjects()
    {
        return m_nestedObjects;
    }

    void SceneObject::GetNormalizedCoordinates(float(&arr)[20])
    {
        Vector2f worldPosition = GetWorldPosition();
        
        float normX, normY;
        normX = (worldPosition.x - VIRTUAL_RESOLUTION_WIDTH / 2.0f) / (VIRTUAL_RESOLUTION_WIDTH / 2.0f);
        normY = (worldPosition.y - VIRTUAL_RESOLUTION_HEIGHT / 2.0f) / (VIRTUAL_RESOLUTION_HEIGHT / 2.0f);

        float normW, normH;
        normW = (worldPosition.x + m_size.x - VIRTUAL_RESOLUTION_WIDTH / 2.0f) / (VIRTUAL_RESOLUTION_WIDTH / 2.0f);
        normH = (worldPosition.y + m_size.y - VIRTUAL_RESOLUTION_HEIGHT / 2.0f) / (VIRTUAL_RESOLUTION_HEIGHT / 2.0f);

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

        //  TODO angle

        for (int i = 0; i < 20; ++i)
        {
            arr[i] = vertices[i];
        }
    }
}
