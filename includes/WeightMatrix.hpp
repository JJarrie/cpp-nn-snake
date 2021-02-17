#ifndef __WEIGHT_MATRIX_HPP__
#define __WEIGHT_MATRIX_HPP__

#include <functional>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Randomizer.hpp"

class WeightMatrix {
    private:
        Randomizer randomizer;
        std::vector<double> vector;
		const int width;
		const int height;
    public:
        explicit WeightMatrix(const int& width, const int& height);
        double get(const int& x, const int& y) const;
        void set(const int& x, const int& y, const double& value);
        WeightMatrix dot(const WeightMatrix& n) const;
        WeightMatrix activate(const std::function<double (double)>& activation) const;
        WeightMatrix mutate(const double& rate);
        WeightMatrix crossover(const WeightMatrix& n);
        ~WeightMatrix();

        friend WeightMatrix operator*(const WeightMatrix& a, const WeightMatrix& b);
        friend std::ostream& operator<<(std::ostream& out, const WeightMatrix& m);
};

#endif