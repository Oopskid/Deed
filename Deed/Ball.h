#pragma once

#include "Kinetic.h"

#include "Circle.h"
template<typename T, size_t Dims> class Ball :
public Circle<T, Dims>, public Kinetic<T>
{
	public:
	void motion(T timelapse) override
	{
		pos += velocity * timelapse;
	}

	static bool collision(T& result, Ball* first, Ball second)
	{
		auto velDif = first->velocity - second.velocity;
		auto posDif = first->pos - second.pos;

		//Quadratic coefficients
		T aQ = velDif.squareMag();
		T bQ = 2 * posDif.dot(velDif);
		T cQ = posDif.squareMag() - first->rad * first->rad - second.rad * second.rad;

		std::vector<double> solution = Solve::quadratic(aQ, bQ, cQ);
		if (solution.empty()) { result = -1; return false; }
		else { result = solution[0]; }
		
		return result >= 0;
	}

	private:
	Vector velocity; //Linear velocity
};

