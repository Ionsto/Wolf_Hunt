#pragma once
#include <vector>
#include "AINode.h"
namespace Sim
{
	class AINeuralNetwork
	{
	public:
		std::vector<std::vector<AINode>> Layers;
		std::vector<float> Outputs;
		AINeuralNetwork();
		~AINeuralNetwork();
		void Update(std::vector<float> Inputs);
		std::vector<float> GetOutput();
		void Splice(AINeuralNetwork network);
		void Randomise(float delta);
	};
}
