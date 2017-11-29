#include "AINode.h"



Sim::AINode::AINode(int weightcount)
{
	for(int i =0; i< weightcount;++i)
		Weights.push_back(0);
}
Sim::AINode::AINode(const AINode & node)
{
	for(auto weight : node.Weights)
		Weights.push_back(weight);
}


Sim::AINode::~AINode()
{
}

void Sim::AINode::Update(std::vector<Sim::AINode> &InputNodes)
{
	float AccIn = 0;
	for(int i = 0;i < InputNodes.size();++i)
	{
		AccIn += InputNodes[i].Output * Weights[i];
	}
	AccIn += Weights.back();
	Output = OutputFunction(AccIn);
}
float Sim::AINode::OutputFunction(float WeightedIn)
{
	//ReLU
	return fmaxf(WeightedIn, 0);
	//Sigmoid
	//return WeightedIn / (1 + abs(WeightedIn));
}
void Sim::AINode::Splice(Sim::AINode &node)
{
	for (int weight = 0; weight < Weights.size(); ++weight)
	{
		const int MixBias = 50;
		int RNG = rand() % 100;
		if (RNG > MixBias)
		{
			//Mix
			Weights[weight] += node.Weights[weight];
			Weights[weight] /= 2;
		}
		else
		{
			//Take other weight, or implicitly keep same weight
			if (rand() % 2 == 0)
			{
				Weights[weight] = node.Weights[weight];
			}
			//Take a
		}
	}
}
void Sim::AINode::Randomise(float Delta)
{
	for (int i = 0; i < Weights.size();++i)
	{
		Weights[i] += (((rand() % 1000) / 1000.0) - 0.5) * Delta;
	}
}