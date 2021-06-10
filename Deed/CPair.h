#pragma once

namespace Collision
{
	//A collisions with B. Takes an extra manager parameter
	template<typename A, typename B, typename Manager, typename DataT> class Pair
	{
		public:
		virtual void resolution(A* first, B* second, Manager* manager) = 0; //Any extra arguments can be stored as members
		virtual void repeatResolution(A* first, B* second, Manager* manager) = 0; //Same as resolution but indicates at least one of the collidables was already 
		virtual bool canCollide(const DataT time, const A* first, const B* second) const = 0; //Fast approximation of collision that assumes the best case
		virtual bool hardCollision(DataT& resultTime, const A* first, const B* second) = 0; //Slow precise determination of when a collision occurs, *if* it does. Extra data stored as members

	};
}