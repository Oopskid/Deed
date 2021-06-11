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
			CEvents events;
			populate(time, events);

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
		typedef std::multimap<T, std::pair<ColPair, size_t>> CEvents;

		//Check all pairs and queue imminent events
		void populate(T time, CEvents& events)
		{
			size_t curId = 0;
			for (size_t xObj = 1; xObj < collidables.size(); xObj++)
			{
				Obj* first = collidables[xObj];
				for (size_t yobj = 0; yObj < xObj; yObj++)
				{
					Obj* second = collidables[yObj];

					considerCollision(time, first, second, curId, events);

					curid++; //Next pair
				}
			}
		}

		bool considerCollision(T time, Obj* first, Obj* second, size_t id, CEvents& events)
		{
			//Lightweight collision detection
			if (asPair(rules).canCollide(time, first, second))
			{
				//Passed, now for the hard part
				T result = time;
				ColPair collision;

				if (asPair(collision).hardCollision(result, first, second))
				{
					//Valid collision
					if (result < time)
					{
						//Collision is imminent, may occur!
						events.insert(std::make_pair(result, std::make_pair(collision, id)));
						return true;
					}
				}
			}
			return false;
		}

		//Gets the objs associated with a pair ID
		void getPair(size_t id, Obj*& first, Obj*& second)
		{
			auto& it = pairMapping.lower_bound(id);
			
			//Imagine a coordinate system of an (n-1)x(n-1) triangle, where the id is the 1-d index
			first = collidables[it->second];
			second = collidables[id - it->first];
		}

		inline Pair<Obj, Obj, Manager, T>& asPair(Colpair& pair)
		{
			return static_cast<Pair<Obj, Obj, Manager, T>>(pair);
		}

		ColPair rules;
		std::vector<Obj*> collidables;

		std::map<size_t, size_t> pairMapping; //Maps a pair ID to the first obj
		size_t pairs;
	};
}