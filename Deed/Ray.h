#pragma once

#include "Vector.h"

template<typename T, size_t Dims> class Ray
{
	typedef Vector<T, Dims> Vector;

	public:

	Vector getHit(const double& t)
	{
		return start + direction * t;
	}

	Vector getDirection() const
	{
		return direction;
	}

	Vector getStart() const
	{
		return start;
	}

	private:
	Vector start;
	Vector direction;
};