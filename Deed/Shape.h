#pragma once

#include <vector>

#include "AABB.h"


template<typename T> class Shape
{
	typedef Vector<T, 2> Vector;

	public:
	Shape() { bound = AABB<T, 2>(); }


	protected:
	std::vector<Vector> vertices;
	AABB<T, 2> bound;
};