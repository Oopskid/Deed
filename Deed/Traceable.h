#pragma once

#include "Ray.h"
#include "Solve.h"

//Interface to handle raytracing
template<typename T, size_t Dims> class Traceable
{
	private:
	typedef Vector<T, Dims> TraceV;
	protected:
	typedef Traceable<T, Dims> Traced;
	
	typedef Ray<T, Dims> TraceRay;

	public:
	//Returns the hit item (in case of hierarchy) and the parameter value of the ray
	virtual Traced const* rayTrace(TraceRay& const ray, T& t) = 0;
	
	//Returns the detected normal at a hit spot. No obligation to be normalised
	virtual TraceV tracedNorm(TraceRay& const ray, const TraceV hitPoint) const = 0;
	TraceV tracedNorm(TraceRay& const ray, const T& t) { return tracedNorm(ray, ray.getHit(t)); }

	//Raytraces this item and compares to a previous result, overwrites if found to be more immediate
	void closer(Traced const* hit, TraceRay& const ray, T& t)
	{
		T resultT;
		Traced const* resultHit = rayTrace(ray, resultT);

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