#pragma once

#include "Collision/Circle.h"
#include "Physics/Kinetic.h"

template<typename T, size_t Dims> class Ball :
public Circle<T, Dims>, public Kinetic<T>
{
	typedef Vector<T, Dims> Vector;

	public:
	Ball() : Circle<T, Dims>() { vel = Vector(); }
	Ball(const Vector position, const T radius) : Circle<T, Dims>(position, radius) { vel = Vector(); }
	Ball(const Vector position, const Vector velocity, const T radius) : Circle<T, Dims>(position, radius) { vel = velocity; }

	void motion(T timelapse) override
	{
		Circle<T, Dims>::pos = Circle<T, Dims>::pos + vel * timelapse;
	}

	static bool collision(T& result, Ball* first, Ball* second)
	{
		auto velDif = first->vel - second->vel;
		auto posDif = first->pos - second->pos;

		//Quadratic coefficients
		T aQ = velDif.squareMag();
		T bQ = 2 * posDif.dot(velDif);
		T cQ = posDif.squareMag() - first->rad * first->rad - second->rad * second->rad;

		std::vector<double> solution = Solve::quadratic(aQ, bQ, cQ);
		if (solution.empty()) { result = -1; return false; }
		else { result = solution[0]; }
		
		return result >= 0;
	}

	Vector getVelocity() const { return vel; }
	void setVelocity(Vector newVelocity) { vel = newVelocity; }

	private:
	Vector vel; //Linear velocity
};

