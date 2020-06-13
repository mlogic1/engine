#include "Rect.h"

Rect::Rect()
{
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
}

Rect::Rect(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Rect::Rect(Vector2<int> position, Vector2<int> size)
{
	this->x = position.x;
	this->y = position.y;
	this->w = size.x;
	this->h = size.y;
}


Rect::~Rect()
{

}