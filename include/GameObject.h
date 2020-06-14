/**
	Game object is a virtual class. Every game related object is derived from this class. It only contains the very basic
	variables and functions.

	@author mlogic1
	@date 28.12.2018.
*/

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector2.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
};

#endif //GAME_OBJECT_H
