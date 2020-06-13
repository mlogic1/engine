#ifndef RECT_H
#define RECT_H

#include "Vector2.h"

class Rect
{
public:
	int x, y, w, h;

	Rect();
	Rect(int x, int y, int w, int h);
	Rect(Vector2<int> position, Vector2<int> size);
	~Rect();

};

#endif // RECT_H