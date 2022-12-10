#pragma once

#include "Vector.h"

namespace Bounds
{
	template<typename T> bool inRange(const T x, const T lower, const T upper)
	{
		//If x is too small, not in range. Otherwise result is whether x is within the upper limit
		return x < lower ? false : x <= upper;
	}

	template<typename T, size_t dims> bool inBound(const Vector<T, dims> x, const Vector<T, dims> lower, const Vector<T, dims> upper)
	{
		for (size_t i = 0; i < dims; i++)
		{
			if (!inRange(x[i], lower[i], upper[i])) { return false; }
		}
		return true;
	}

	//Returns the range which in two ranges overlap. First is min, second is max. Range only exists if the minimum is truly smaller than the maximum
	template<typename T> std::pair<T, T> overlap(const std::pair<T, T> firstR, const std::pair<T, T> secondR)
	{
		return std::make_pair(
			firstR.first > secondR.first ? firstR.first : secondR.first, //The max of the mins
			firstR.second < secondR.second ? firstR.second : secondR.second //The min of the max
		);
	}

	//Returns whether two ranges overlap. First is min, second is max
	template<typename T> inline bool overlaps(const std::pair<T, T> firstR, const std::pair<T, T> secondR)
	{
		return firstR.second >= secondR.first && secondR.second >= firstR.first;
	}

	//Returns the minimum range which includes two ranges
	template<typename T> std::pair<T, T> include(const std::pair<T, T> firstR, const std::pair<T, T> secondR)
	{
		return std::make_pair(
			firstR.first < secondR.first ? firstR.first : secondR.first, //The min of the mins
			firstR.second > secondR.second ? firstR.second : secondR.second //The max of the maxs
		);
	}

	//Returns when two values overlap, given a 'velocity'
	template<typename T> inline T when(const T to, const T from, const T velocity)
	{
		return (to - from) / velocity;
	}
}
