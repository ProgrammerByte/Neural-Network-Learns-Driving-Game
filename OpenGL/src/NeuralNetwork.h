#pragma once

#include <vector>

class NeuralNetwork {
private:
	std::vector<int> nodes;
	std::vector<std::vector<std::vector<double>>> weights;
	std::vector<std::vector<double>> bias;
	std::vector<std::vector<double>> contents;

public:
	NeuralNetwork(std::vector<int> nodes = {0, 0, 0, 0}); //will only work for four layers
	void randomize();
	void setInputs(std::vector<double> inputs);
	std::vector<double> getOutputs();
	~NeuralNetwork();
};