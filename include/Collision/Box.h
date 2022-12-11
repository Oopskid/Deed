#pragma once

#include "AABB.h"
#include "Physics/Kinetic.h"

template<typename T, size_t Dims> class Box :
public AABB<T, Dims>, public Kinetic<T>
{
	typedef Vector<T, Dims> Vector;

	public:
	static bool collision(double& result, const Box* first, const Box* second)
	{

	}

	virtual void motion(T timelapse) override
	{
		translate(velocity * timelapse);
	}

	private:
	Vector velocity;
};