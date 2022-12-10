#pragma once

#include "Vector.h"

template<typename T, size_t Dims> class Ray
{
	typedef Vector<T, Dims> Vector;

	public:
	Ray() {  }
	Ray(const Vector startPoint, const Vector theDirection)
	{
		start = startPoint;
		direction = theDirection;
	}


	Vector getHit(const T& t)
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

	void setEnd(const Vector newEnd)
	{
		direction = newEnd - start;
	}

	void setDirection(const Vector newDirection)
	{
		direction = newDirection;
	}

	void setStart(const Vector newStart)
	{
		start = newStart;
	}

	private:
	Vector start;
	Vector direction;
};