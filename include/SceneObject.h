/**
    SceneObject
	@author mlogic1
	@date 28.06.2020.
*/

#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "IIdentifiable.h"
#include "GameObject.h"
#include "Rect.h"
#include "Vector2.h"
#include <string>
#include <vector>

namespace Engine
{
	class SceneObject : public GameObject, public IIdentifiable
	{
		public:
			SceneObject(Rect objectRect, std::string objectID);
			SceneObject(Vector2f objectPosition, Vector2f objectSize, std::string objectID);
			~SceneObject();

			/***************************************
			 * inherited methods
			***************************************/
			virtual void update(float deltaTime);
			virtual void render() = 0;

			/***************************************
			 * properties
			***************************************/
			virtual bool GetVisible();
			Vector2f GetPosition();
			Vector2f GetSize();
			std::string GetID() const override;

			virtual void SetVisible(bool visibleState);
			void SetPosition(Vector2f position);
			void SetSize(Vector2f size);

			void AddNestedObject(SceneObject* object);
			const std::vector<SceneObject*>& GetNestedObjects();

        protected:
			void GetNormalizedCoordinates(float(&arr)[20]);

		protected:
			// properties
			bool m_isVisible = true;
			Vector2f m_position;
			Vector2f m_size;
			const std::string m_objectID;
			// TODO add pivots
			// TODO z-order
			// TODO angle
			// TODO destination

			std::vector<SceneObject*> m_nestedObjects;
	};
}

#endif /* SCENE_OBJECT_H */
