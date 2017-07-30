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
	EntityList.remove(ent);
}
std::list<Sim::Entity*> Sim::GridNode::GetEntities()
{
	return EntityList;
}