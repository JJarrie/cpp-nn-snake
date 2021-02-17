#include <iostream>

#include "NeuralNetwork.hpp"
#include "Randomizer.hpp"

int main(int argc, char** argv) {
	std::vector<int> sizing = { 28, 16, 3 };
	NeuralNetwork n(sizing);

	std::cout << n << std::endl;

	return EXIT_SUCCESS;
}
