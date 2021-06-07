#pragma once

#include "Ray.h"
#include "Solve.h"

//Interface to handle raytracing
template<typename T, size_t Dims> class Traceable
{
	typedef Ray<T, Dims> Ray;
	typedef Vector<T, Dims> Vector;

	public:
	//Returns the hit item (in case of hierarchy) and the parameter value of the ray
	virtual Traceable const* rayTrace(Ray& const ray, double& t) = 0;
	
	//Returns the detected normal at a hit spot. No obligation to be normalised
	virtual Vector tracedNorm(Ray& const ray, const Vector hitPoint) const = 0;
	Vector tracedNorm(Ray& const ray, const double& t) { return tracedNorm(ray, ray.getHit(t)); }

	//Raytraces this item and compares to a previous result, overwrites if found to be more immediate
	void closer(Traceable const* hit, Ray& const ray, double& t)
	{
		double resultT;
		Traceable const* resultHit = rayTrace(ray, resultT);

		//Improvement?
		if (resultT < t)
		{
			//...but is it really?
			if (resultT >= 0)
			{
				hit = resultHit;
				t = resultT;
			}
		}
	}
};