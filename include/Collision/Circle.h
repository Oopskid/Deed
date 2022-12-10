#pragma once

#include "Traceable.h"
#include "Vector.h"

//Bounding sphere
template<typename T, size_t Dims> class Circle :
public Traceable<T, Dims>
{
	typedef Vector<T, Dims> Vector;

	public:
	Circle() { pos = Vector(); rad = T(); }
	Circle(const Vector position, const T radius) { pos = position; rad = radius; }

	Traceable<T, Dims> const* rayTrace(Ray<T, Dims>& const ray, T& t) override
	{
		Vector disp = ray.getStart() - pos;

		//Quadratic coefficients
		T aQ = ray.getDirection().squareMag();
		T bQ = disp.dot(ray.getDirection()) * 2;
		T cQ = disp.squareMag() - rad * rad;

		std::vector<double> solution = Solve::quadratic(aQ, bQ, cQ);
		if (solution.empty()) { t = -1; return nullptr; }
		else { t = solution[0]; }
		return this;
	}

	Vector tracedNorm(Ray<T, Dims>& const ray, const Vector hitPoint) const override
	{
		return hitPoint - pos;
	}

	//Returns whether a sphere contains a point
	static bool contains(Circle* const first, const Vector second)
	{
		return (second - first->pos).squareMag() <= first->rad * first->rad; //Is square distance smaller than radii?
	}

	//Returns whether two spheres overlap
	static bool overlaps(Circle* const first, Circle* const second)
	{
		Vector displace = first->pos - second->pos; //Displacement between two centres
		T reqDist = first->rad + second->rad; //Distance which spheres would overlap

		return displace.squareMag() <= reqDist * reqDist; //Is square distance smaller than radii?
	}

	Vector getPosition() const { return pos; }
	void setPosition(const Vector newPosition) { pos = newPosition; }
	T getRadius() const { return rad; }
	void setRadius(const T newRadius) { rad = newRadius; }

	protected:
	Vector pos;
	T rad;
};