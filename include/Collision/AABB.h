#pragma once

#include "Maths/Vector.h"
#include "Bounds.h"

//Axis aligned bounding box
template<typename T, size_t Dims> class AABB
{
	typedef Vector<T, Dims> Vector;

	public:
	AABB() {  }
	AABB(const Vector& position, const Vector& size) { pos = position; range = size; }

	//Returns whether two AABB overlap
	static bool overlaps(const AABB* first, const AABB* second)
	{
		//Check each dimension
		for (size_t i = 0; i < Dims; i++)
		{
			if (!Bounds::overlaps(std::make_pair(first->pos[i], first->pos[i] + first->range[i]), std::make_pair(second->pos[i], second->pos[i] + second->range[i]))) { return false; } //Return prematurely
		}
		return true;
	}

	//Returns if this AABB contains a smaller one
  bool contains(const AABB* child) const
	{
		//Check each dimension
		for (size_t i = 0; i < Dims; i++)
		{
			if (!Bounds::contains(std::make_pair(pos[i], pos[i] + range[i]), std::make_pair(child->pos[i], child->pos[i] + child->range[i]))) { return false; } //Return prematurely
		}
		return true;
	}

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

	//Return inclusive area
	AABB operator+(const AABB& other) const
	{
		AABB result;
		for (size_t i = 0; i < Dims; i++)
		{
			auto partialRes = Bounds::include(std::make_pair(pos[i], pos[i] + range[i]), std::make_pair(other.pos[i], other.pos[i] + other.range[i]));

			result.pos[i] = partialRes.first; //Position from min
			result.range[i] = partialRes.second - partialRes.first; //Max to range
		}
		return result;
	}

	//Return inclusive area
	AABB operator+(const Vector& pInclude) const
	{
		AABB result;
		for (size_t i = 0; i < Dims; i++)
		{
			auto partialRes = Bounds::include(std::make_pair(pos[i], pos[i] + range[i]), std::make_pair(pInclude[i], pInclude[i]));

			result.pos[i] = partialRes.first; //Position from min
			result.range[i] = partialRes.second - partialRes.first; //Max to range
		}
		return result;
	}

	void scale(T mult)
	{
		range.scale(mult);
	}

	void translate(const Vector& amount)
	{
		pos += amount;
	}

	const Vector& getPosition() const { return pos; }
	Vector setPosition(const Vector newPosition) { pos = newPosition; }
	const Vector& getSize() const { return range; }
	void setSize(const Vector newSize) { range = newSize; }

	private:
	Vector pos;
	Vector range;
};