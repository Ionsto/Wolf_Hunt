#include "SwapList.h"


template<typename item>
Sim::SwapList<item>::SwapList()
{
	for (int i = 0; i < MaxItems; ++i)
	{
		FreeList.push_back(i);
	}
}

template<typename item>
Sim::SwapList<item>::~SwapList()
{
}

template<typename item>
Sim::SwapListID Sim::SwapList<item>::AddItem(item object)
{
	if (ActiveItems < MaxItems)
	{
		int newid = FreeList.front();
		FreeList.pop_front();
		Indirection[newid] = ActiveItems;
		ItemPool[ActiveItems] = object;
		++ActiveItems;
		return SwapListID(Sim::SwapListID(newid));
	}
	else
	{
		auto out = SwapListID();
		out.Valid = false;
		return out;
	}
}
template<typename item>
void Sim::SwapList<item>::RemoveItem(SwapListID position)
{
	if (ActiveItems > 0)
	{
		VersionPool[Indirection[newid]]++;

		FreeList.push_front(position.Id);

		item tmp = ItemPool[ActiveItems-1];

		GetItem(position) = tmp;
		--ActiveItems;
	}
}