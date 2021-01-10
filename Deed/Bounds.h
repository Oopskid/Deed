#pragma once

#include "Vector.h"

namespace Bounds
{
	template<typename T> bool inRange(T x, T lower, T upper)
	{
		//If x is too small, not in range. Otherwise result is whether x is within the upper limit
		return x < lower ? false : x <= upper;
	}

	template<typename T, size_t dims> bool inBound(Vector<T, dims> x, Vector<T, dims> lower, Vector<T, dims> upper)
	{
		for (size_t i = 0; i < dims; i++)
		{
			if (!inRange(x[i], lower[i], upper[i])) { return false; }
		}
		return true;
	}

	//Returns the range which in two ranges overlap. First is min, second is max. Range only exists if the minimum is truly smaller than the maximum
	template<typename T> std::pair<T, T> overlap(std::pair<T, T> firstR, std::pair<T, T> secondR)
	{
		return std::make_pair(
			firstR.first > secondR.first ? firstR.first : secondR.first, //The max of the mins
			firstR.second < secondR.second ? firstR.second : secondR.second //The min of the max
		);
	}
}
