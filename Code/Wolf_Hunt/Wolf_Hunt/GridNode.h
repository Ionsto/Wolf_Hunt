#pragma once
#include "Vector.h"
namespace Sim {
	class GridNode
	{
	public:
		Sim::Vector Size;
		Sim::Vector Location;
		GridNode();
		~GridNode();
	};
}
