#pragma once

namespace Collision
{
	//A collisions with B. Takes an extra manager parameter
	template<typename A, typename B, typename Manager, typename DataT> class Pair
	{
		public:
		virtual void resolution(A* first, B* second, Manager* manager) {  } //Any extra arguments can be stored as members
		virtual void repeatResolution(A* first, B* second, Manager* manager) { resolution(first, second, manager); } //Same as resolution but indicates at least one of the collidables was already colliding (crush detection)
		virtual bool canCollide(const DataT time, const A* first, const B* second) const { return true; } //Fast approximation of collision that assumes the best case
		virtual bool hardCollision(DataT& resultTime, const A* first, const B* second) = 0; //Slow precise determination of when a collision occurs, *if* it does. Extra data stored as members
		virtual bool verifyCollision(DataT& resultTime, const A* first, const B* second) const { return true; } //Confirmation using previous data whether a previously detected collision is still valid
	};
}