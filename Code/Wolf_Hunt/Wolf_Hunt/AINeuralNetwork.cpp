#include "AINeuralNetwork.h"

Sim::AINeuralNetwork::AINeuralNetwork()
{
	
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
void Sim::AINeuralNetwork::Splice(Sim::AINeuralNetwork & network)
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
void Sim::AINeuralNetwork::Copy(Sim::AINeuralNetwork & network)
{
	for (int i = 0; i < Layers.size(); ++i)
	{
		for (int n = 0; n < Layers[i].size(); ++n)
		{
			//Take mine/take yours/mix
			Layers[i][n].Copy(network.Layers[i][n]);
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
