#pragma once

//Generic kinematics (physics) base
template<typename T> class Kinetic
{
	public:
	virtual void motion(T timelapse) = 0;
};