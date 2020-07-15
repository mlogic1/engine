/**
    SceneObject
	@author mlogic1
	@date 28.06.2020.
*/

#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "GameObject.h"
#include "Rect.h"
#include "Vector2.h"
#include <string>
#include <vector>

namespace Engine
{
	class SceneObject : public GameObject
	{
		public:
			SceneObject(Rect objectRect);
			SceneObject(Vector2f objectPosition, Vector2f objectSize);
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
			std::string GetID();

			virtual void SetVisible(bool visibleState);
			void SetPosition(Vector2f position);
			void SetSize(Vector2f size);

		protected:
			// properties
			bool m_isVisible = true;
			Vector2f m_position;
			Vector2f m_size;
			// TODO add pivots
			// TODO z-order
			// TODO angle
			// TODO destination

		protected:
			const std::string m_objectID = "DefaultObject";	// TODO every object needs a unique ID
	};
}

#endif /* SCENE_OBJECT_H */
