#pragma once

#include "Vector.h"
#include "Bounds.h"
template<typename T, size_t Dims> class AABB
{
	typedef Vector<T, Dims> Vector;

	public:
	AABB() { pos = Vector(); range = Vector(); }
	AABB(const Vector position, const Vector size) { pos = position; range = size; }

	//Return overlap area
	AABB operator-(const AABB& other) const
	{
		AABB result;
		for (size_t i = 0; i < Dims; i++)
		{
			auto partialRes = Bounds::overlap(std::make_pair(pos[i], pos[i] + range[i]), std::make_pair(other.pos[i], other.pos[i] + other.range[i]));
			
			result.pos[i] = partialRes.first; //Position from min
			result.range[i] = partialRes.second - partialRes.first; //Max to range
		}
		return result;
	}

	private:
	Vector pos;
	Vector range;
};