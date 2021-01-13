#pragma once

#include "Vector.h"

//Bounding sphere
template<typename T, size_t Dims> class Circle
{
	typedef Vector<T, Dims> Vector;

	public:
	Sphere() { pos = Vector(); rad = T(); }
	Sphere(const Vector position, const T radius) { pos = position; rad = radius; }

	//Returns whether two spheres overlap
	static bool overlaps(const Circle& first, const Circle& second)
	{
		Vector displace = first.pos - second.pos; //Displacement between two centres
		T reqDist = first.rad + second.rad; //Distance which spheres would overlap

		return displace.squareMag() <= reqDist * reqDist; //Is square distance smaller than radii?
	}

	Vector getPosition() const { return pos; }
	Vector setPosition(const Vector newPosition) { pos = newPosition; }
	T getRadius() const { return rad; }
	void setRadius(const T newRadius) { rad = newRadius; }

	private:
	Vector pos;
	T rad;
};