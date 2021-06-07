#pragma once

#include <vector>

#include "AABB.h"

template<typename T> class Mesh
{
	typedef Vector<T, 3> Vector;

	public:
	Mesh() { bound = AABB<T, 3>(); }

	protected:
	std::vector<size_t> indices;
	std::vector<Vector> vertices;
	AABB<T, 3> bound;
};