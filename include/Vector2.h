#ifndef VECTOR2_H
#define VECTOR2_H

template<typename T>
class Vector2
{
public:
	T x;
	T y;


	Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2(const T &vector)
	{
		this->x = static_cast<T>(vector.x);
		this->y = static_cast<T>(vector.y);
	}

	~Vector2()
	{

	}
};

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;

#endif // VECTOR2_H