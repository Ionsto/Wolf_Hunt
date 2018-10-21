#pragma once
#include <exception>
#include <array>
#include <assert.h>
#include <deque>
namespace Sim {
	struct SwapListID
	{
		SwapListID(int i = -1,int rev = 0): Id(i), Revision(rev) {};
		int Id;
		int Revision;
	};

	template<typename item,int MaxItems = 1000>
	class SwapList
	{
	private:
		std::array<int, MaxItems> VersionPool = {0};
		std::array<int, MaxItems> ReverseIndirectionPool;
		std::array<int, MaxItems> Indirection;
		std::deque<int> FreeList;
	public:
		int ActiveItems = 0;
		std::array<item, MaxItems> ItemPool;
		SwapList()
		{
			//Whole indirection pool is free
			for (int i = 0; i < MaxItems; ++i)
			{
				FreeList.push_back(i);
			}
		}

		~SwapList()
		{

		}
		SwapListID AddItem(item object)
		{
			if (ActiveItems < MaxItems && FreeList.size() != 0)
			{
				int newid = FreeList.front();
				FreeList.pop_front();
				Indirection[newid] = ActiveItems;
				ItemPool[ActiveItems] = object;
				ReverseIndirectionPool[ActiveItems] = newid;
				VersionPool[Indirection[newid]]++;
				++ActiveItems;
				return Sim::SwapListID(newid,VersionPool[ActiveItems-1]);
			} 
			else
			{
				std::cout << "Returned invalid ID \n";
				return SwapListID();
			}
		}
		void RemoveItem(SwapListID & position)
		{
			if (position.Id == -1){
				std::cout << "Can't remove invalid object\n";
			}
			if (ActiveItems > 0)
			{
				//Increment the version

				//Re-add id to indirection pool
				FreeList.push_front(position.Id);
				
				ActiveItems -= 1;
				if (ActiveItems != Indirection[position.Id])
				{
					std::cout << "Set item at " << Indirection[position.Id] << " to item at " << ActiveItems << "\n";
					//Move our back item to position
					ItemPool[Indirection[position.Id]] = ItemPool[ActiveItems];
					Indirection[ReverseIndirectionPool[ActiveItems]] = Indirection[position.Id];
					//ReverseIndirectionPool[Indirection[position.Id]] = ReverseIndirectionPool[ActiveItems];
					//This invalidates all Ids to us
					VersionPool[Indirection[position.Id]] = VersionPool[ActiveItems]; // Somehow we need to tell our updated ID we've changed it's revision
					VersionPool[ActiveItems] += 1; // Somehow we need to tell our updated ID we've changed it's revision
					position.Id = -1;
				}
			}
		}
		inline item & GetItem(SwapListID ids)
		{
			assert(ids.Id != -1);// Attempted to deref invalid ID
			assert(VersionPool[Indirection[ids.Id]] == ids.Revision);//Object version difference
			return ItemPool[Indirection[ids.Id]];
		}

	};
}
