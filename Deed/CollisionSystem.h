#pragma once

#include <vector>
#include <map>
#include <type_traits>

#include "Solve.h"
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
			lastFirst = nullptr;
			lastSecond = nullptr;
		}

		void solve(T time, Manager* manager)
		{
			CEvents events;
			populate(time, events);

			while (events.size() > 0)
			{
				auto& it = events.begin();
				size_t first;
				size_t second;

				getPair(it.second.second, first, second);
				Obj* firstObj = collidables[first];
				Obj* secondObj = collidables[second];

				T thisTime = it->first;
				if (asPair(it->second.first).verifyCollision(thisTime, firstObj, secondObj))
				{
					if (thisTime <= it->first)
					{
						//Step simulation
						step(thisTime);
						time -= thisTime;

						//Resolve collision
						if (firstObj == lastFirst || firstObj == lastSecond || secondObj == lastFirst || secondObj == lastSecond)
						{
							asPair(it->second.first).repeatResolution(firstObj, secondObj, manager);
						}
						else
						{
							asPair(it->second.first).resolution(firstObj, secondObj, manager);
						}

						lastFirst = firstObj;
						lastSecond = secondObj;

						//Add any new events
						invalidate(time, first, second, events);
					}
					else
					{
						if (thisTime <= time)
						{
							events.insert(std::make_pair(thisTime, it.second));
						}
					}
				}

				events.erase(it);
			}

		}

		void add(Obj* collidable)
		{
			pairs += collidables.size(); //Progressively calculate (n - 1)th triangular number
			
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

		//Determine if a collision can occur in a timeframe and add it as an event if so
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
					if (result <= time)
					{
						//Collision is imminent, may occur!
						events.insert(std::make_pair(result, std::make_pair(collision, id)));
						return true;
					}
				}
			}
			return false;
		}

		//Consider all the pairs that might be invalid due to two collidable updates
		void invalidate(T time, size_t first, size_t second, CEvents& events)
		{
			size_t curId = Solve::triangular<size_t>(first - 1);

			//Column
			for (size_t i = 0; i < first; i++)
			{
				considerCollision(time, collidables[first], collidables[i], curId, events);
				curId++;
			}

			//Row
			curId += first;
			first++;
			for (; first < collidables.size(); first++)
			{
				considerCollision(time, collidables[first], collidables[second], curId, events);
				curId += first;
			}
		}

		//Step the simulation
		void step(T timePassed)
		{
			for (auto i : collidables)
			{
				reinterpret_cast<Kinetic<T>*>(i)->motion(timePassed);
			}
		}

		//Gets the objs associated with a pair ID
		void getPair(size_t id, size_t& first, size_t& second)
		{
			auto& it = pairMapping.lower_bound(id);
			
			//Imagine a coordinate system of an (n-1)x(n-1) triangle, where the id is the 1-d index
			first = it->second;
			second = id - it->first;
		}

		inline Pair<Obj, Obj, Manager, T>& asPair(Colpair& pair)
		{
			return static_cast<Pair<Obj, Obj, Manager, T>>(pair);
		}

		ColPair rules;
		Obj* lastFirst;
		Obj* lastSecond;
		std::vector<Obj*> collidables;

		std::map<size_t, size_t> pairMapping; //Maps a pair ID to the first obj
		size_t pairs;
	};
}