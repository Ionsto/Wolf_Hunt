#include "GridNode.h"



Sim::GridNode::GridNode() : Location()
{
}

Sim::GridNode::GridNode(Vector<int> loc) : Location(loc)
{
}


Sim::GridNode::~GridNode()
{
}

void Sim::GridNode::AddEntity(Entity * ent)
{
	this->EntityList.push_back(ent);
}
void Sim::GridNode::RemoveEntity(Entity * ent)
{
	auto it = std::find(EntityList.begin(), EntityList.end(), ent);
	if (it != EntityList.end()) {
		std::swap(*it, EntityList.back());
		EntityList.pop_back();
	}
}
std::vector<Sim::Entity*> &Sim::GridNode::GetEntities()
{
	return EntityList;
}