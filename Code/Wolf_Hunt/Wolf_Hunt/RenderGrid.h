#pragma once
#include <array>
#include "SwapList.h"
#include "ComponentID.h"
#include "RenderComponents.h"
#include "Vector.h"
namespace Sim {
	struct GridID {
		SwapListID swpId;
		Vector<int> GridId;
		bool Valid = true;
	};
	struct GridNode {
		static constexpr int MaxCicles = 50;
		static constexpr int MaxCameras = 50;
		SwapList<ComponentRenderCircle, MaxCicles> SListCircle;
		SwapList<ComponentRenderCamera, MaxCameras> SListCamera;
	};
	template
	<int GridCount, int GridSize, int EntityPerGrid>
	class RenderGrid
	{
		//std::Array<> 
		GridID AddItem(item object)
		{

		}
		void RemoveItem(GridID position)
		{
		}
		inline item & GetItem(GridID ids)
		{
		}
	}
}
