#include <iostream>
#include <vector>

#include "Vector.hpp"
#include "Population.hpp"

int main(int argc, char** argv) {
	Vector boardSize(20, 20);
	std::vector<int> sizing{ 28, 16, 3 };

	Population population(boardSize, 0.05, 2000, sizing);

	while(true) {
		if (population.isGenerationFinish()) {
			population.nextGeneration();
		}

		population.nextCycle();
	}

	return EXIT_SUCCESS;
}
