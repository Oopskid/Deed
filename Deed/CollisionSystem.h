#pragma once

#include <type_traits>
#include "Kinetic.h"

template<typename T> class CollisionSystem
{
	static_assert(std::is_base_of<Kinetic, T>);

};