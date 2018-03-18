#pragma once
#include <array>
#include <deque>
namespace Sim {
	struct SwapListID
	{
		SwapListID(int i = -1): Id(i) {};
		int Id;
		int Revision;
	};

	template<typename item>
	class SwapList
	{
	private:
		static const int MaxItems = 1000;
		std::array<int, MaxItems> VersionPool;
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
			if (ActiveItems < MaxItems)
			{
				int newid = FreeList.front();
				FreeList.pop_front();
				Indirection[newid] = ActiveItems;
				ItemPool[ActiveItems] = object;
				ReverseIndirectionPool[ActiveItems] = newid;
				++ActiveItems;
				return Sim::SwapListID(newid);
			}
			else
			{
				return SwapListID();
			}
		}
		void RemoveItem(SwapListID position)
		{
			if (ActiveItems > 0)
			{
				//Increment the version
				VersionPool[Indirection[position.Id]]++;

				//Re-add id to indirection pool
				FreeList.push_front(position.Id);
				
				--ActiveItems;
				if (ActiveItems != Indirection[position.Id])
				{
					std::cout << "Set item at" << Indirection[position.Id] << "To item at" << ActiveItems<<"\n";
					//Move our back item to position
					ItemPool[Indirection[position.Id]] = ItemPool[ActiveItems];
					Indirection[ReverseIndirectionPool[ActiveItems]] = Indirection[position.Id];
					ReverseIndirectionPool[Indirection[position.Id]] = ReverseIndirectionPool[ActiveItems];
				}
			}
		}
		inline item & GetItem(SwapListID ids)
		{
			return ItemPool[Indirection[ids.Id]];
		}

	};
}
