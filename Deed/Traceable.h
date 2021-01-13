#pragma once

#include "Ray.h"

//Interface to handle raytracing
template<typename T, size_t Dims> class Traceable
{
	typedef Ray<T, Dims> Ray;
	typedef Vector<T, Dims> Vector;

	public:
	//Returns the hit item (in case of hierarchy) and the parameter value of the ray
	virtual Traceable const* rayTrace(Ray& const ray, T& t) = 0;
	
	//Returns the detected normal at a hit spot
	virtual Vector tracedNorm(Ray& const ray, const Vector hitPoint) const = 0;
	Vector tracedNorm(Ray& const ray, const T& t) { return tracedNorm(ray, ray.getHit(t)); }

	//Raytraces this item and compares to a previous result, overwrites if found to be more immediate
	void closer(Traceable const* hit, Ray& const ray, T& t)
	{
		T resultT;
		Traceable const* resultHit = rayTrace(ray, resultT);

		//Improvement?
		if (resultT < t)
		{
			hit = resultHit;
			t = resultT;
		}
	}
};