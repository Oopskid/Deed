#pragma once

#include <vector>
#include <map>
#include <type_traits>

#include "Kinetic.h"
#include "CPair.h"

namespace Collision
{
	template<typename T, typename Obj, typename Manager, typename ColPair> class SimpleSystem
	{
		static_assert(std::is_base_of<Kinetic<T>, Obj>);
		static_assert(std::is_base_of<Pair<Obj, Obj, Manager, T>, ColPair>);

		public:
		SimpleSystem()
		{
			pairs = 0;
		}

		void solve(T time, Manager* manager)
		{

			std::multimap<T, std::pair<ColPair, size_t>>


		}

		void add(Obj* collidable)
		{
			pairs += collidables.size(); //Progressively calculate (x - 1)!
			
			collidables.push_back(collidable);

			pairMapping.insert(pairMapping.end(), std::make_pair(pairs, collidables.size())); //Map this pair ID to first obj
		}

		void clear()
		{
			pairs = 0;
			collidables.clear();
		}

		private:
		//Gets the objs associated with a pair ID
		void getPair(size_t id, Obj*& first, Obj*& second)
		{
			auto& it = pairMapping.lower_bound(id);
			
			//Imagine a coordinate system of an (n-1)x(n-1) triangle, where the id is the 1-d index
			first = collidables[it->second];
			second = collidables[id - it->first];
		}

		ColPair rules;
		std::vector<Obj*> collidables;

		std::map<size_t, size_t> pairMapping; //Maps a pair ID to the first obj
		size_t pairs;
	};
}