#include "AINeuralNetwork.h"

Sim::AINeuralNetwork::AINeuralNetwork()
{
	Layers.push_back(std::vector<AINode>());
	Layers.push_back(std::vector<AINode>());
	Layers.push_back(std::vector<AINode>());

	//Input psedo nodes
	Layers[0].push_back(AINode(0));
	Layers[0].push_back(AINode(0));
	Layers[0].push_back(AINode(0));
	Layers[0].push_back(AINode(0));
	Layers[0].push_back(AINode(0));
	//Layers[0].push_back(AINode(0));
	
	//Hidden
	Layers[1].push_back(AINode(Layers[0].size() + 1));
	Layers[1].push_back(AINode(Layers[0].size() + 1));
	Layers[1].push_back(AINode(Layers[0].size() + 1));
	Layers[1].push_back(AINode(Layers[0].size() + 1));

	//Output
	//State node psedo one hot softmax
	Layers[2].push_back(AINode(Layers[1].size() + 1));
	Layers[2].push_back(AINode(Layers[1].size() + 1));
	Layers[2].push_back(AINode(Layers[1].size() + 1));
	//Boid nodes	
	Layers[2].push_back(AINode(Layers[1].size() + 1));//rep
	Layers[2].push_back(AINode(Layers[1].size() + 1));//clump
	Layers[2].push_back(AINode(Layers[1].size() + 1));//coehs
	Layers[2].push_back(AINode(Layers[1].size() + 1));//flee
	Layers[2].push_back(AINode(Layers[1].size() + 1));//wall aversion
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
