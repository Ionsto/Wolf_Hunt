#include "AINeuralNetwork.h"

Sim::AINeuralNetwork::AINeuralNetwork()
{
	Layers.push_back(std::vector<AINode>());

	//Input psedo nodes
	Layers[0].emplace_back(AINode(0));
	Layers[0].emplace_back(AINode(0));
	Layers[0].emplace_back(AINode(0));
	Layers[0].emplace_back(AINode(0));
	Layers[0].emplace_back(AINode(0));
	//Layers[0].push_back(AINode(0));
	for (int l = 0; l < 0; ++l)
	{
		Layers.push_back(std::vector<AINode>());
		for (int n = 0; n < 5; ++n)
		{
			//Hidden
			Layers[l + 1].emplace_back(AINode(Layers[l-1].size() + 1));
		}
	}

	Layers.push_back(std::vector<AINode>());
	//Output
	//State node psedo one hot softmax
	Layers.back().emplace_back(AINode((Layers.end() - 2)->size() + 1));
	Layers.back().emplace_back(AINode((Layers.end() - 2)->size() + 1));
	Layers.back().emplace_back(AINode((Layers.end() - 2)->size() + 1));
	//Boid nodes	
	Layers.back().emplace_back(AINode((Layers.end() - 2)->size() + 1));//rep
	Layers.back().emplace_back(AINode((Layers.end() - 2)->size() + 1));//clump
	Layers.back().emplace_back(AINode((Layers.end() - 2)->size() + 1));//coehs
	Layers.back().emplace_back(AINode((Layers.end() - 2)->size() + 1));//flee
	Layers.back().emplace_back(AINode((Layers.end() - 2)->size() + 1));//wall aversion
}


Sim::AINeuralNetwork::~AINeuralNetwork()
{
}

void Sim::AINeuralNetwork::Update(std::vector<float> Inputs)
{
	for(int i = 0;i< Inputs.size();++i)
	{
		Layers[0][i].Output = Inputs[i];
	}
	for (int i = 1; i < Layers.size(); ++i)
	{
		for (int n = 0; n < Layers[i].size(); ++n)
		{
			Layers[i][n].Update(Layers[i-1]);
		}
	}
}
std::vector<float> Sim::AINeuralNetwork::GetOutput()
{
	return Outputs;
}
void Sim::AINeuralNetwork::Splice(Sim::AINeuralNetwork network)
{
	for (int i = 0; i < Layers.size(); ++i)
	{
		for (int n = 0; n < Layers[i].size(); ++n)
		{
			//Take mine/take yours/mix
			Layers[i][n].Splice(network.Layers[i][n]);
		}
	}
}
void Sim::AINeuralNetwork::Randomise(float Delta)
{
	for (int i = 0; i < Layers.size(); ++i)
	{
		for (int n = 0; n < Layers[i].size(); ++n)
		{
			Layers[i][n].Randomise(Delta);
		}
	}
}
