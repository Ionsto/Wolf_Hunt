#pragma once
#include "SwapList.h"
namespace Sim {
	struct ComponentIDRenderObject {
		ComponentIDRenderObject(SwapListID id = SwapListID()) :swpId(id) {
			if (id.Id == -1)
			{
				Valid = false;
			}
		};
		SwapListID swpId;
		bool Valid = true;
	};
	struct ComponentIDRenderCamera {
		ComponentIDRenderCamera(SwapListID id = SwapListID()) :swpId(id)
		{
			if (id.Id == -1)
			{
				Valid = false;
			}
		};
		SwapListID swpId;
		bool Valid = true;
	};
	struct ComponentIDCollision {
		ComponentIDCollision(SwapListID id = SwapListID()) :swpId(id)
		{
			if (id.Id == -1)
			{
				Valid = false;
			}
		};
		SwapListID swpId;
		bool Valid = true;
	};
	struct ComponentIDAI {
		ComponentIDAI(SwapListID id = SwapListID()) :swpId(id)
		{
			if (id.Id == -1)
			{
				Valid = false;
			}
		};
		SwapListID swpId;
		bool Valid = true;
	};
}
