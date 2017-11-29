#pragma once
#include <vector>
namespace Sim
{
	class AINode
	{
	public:
		float Output;
		std::vector<float> Weights;
		AINode(int weightcount = 0);
		AINode(const AINode & node);
		~AINode();
		void Update(std::vector<AINode> &Inputs);
		void Splice(AINode &node);
		float OutputFunction(float weightedin);
		void Randomise(float Delta);
	};
}
