#pragma once

#include "Traceable.h"
#include "Vector.h"

//Bounding sphere
template<typename T, size_t Dims> class Circle :
public Traceable<T, Dims>
{
	typedef Vector<T, Dims> Vector;
	typedef Ray<T, Dims> Ray;

	public:
	Sphere() { pos = Vector(); rad = T(); }
	Sphere(const Vector position, const T radius) { pos = position; rad = radius; }

	Traceable const* rayTrace(Ray& const ray, double& t) override
	{
		Vector disp = pos - ray.getStart();
		
		//Quadratic coefficients
		T aQ = ray.direction.squareMag();
		T bQ = disp.dot(ray.direction) * 2;
		T cQ = disp.squareMag() - rad * rad;

		std::vector<double> solution = Solve::quadratic(aQ, bQ, cQ);
		if (solution.empty()) { return -1; } else { return solution[0]; }
		return this;
	}

	Vector tracedNorm(Ray& const ray, const Vector hitPoint) const override
	{
		return hitPoint - pos;
	}

	//Returns whether two spheres overlap
	static bool overlaps(Circle* const first, Circle* const second)
	{
		Vector displace = first->pos - second->pos; //Displacement between two centres
		T reqDist = first->rad + second->rad; //Distance which spheres would overlap

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