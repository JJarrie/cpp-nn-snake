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
		int width;
		int height;
    public:
        explicit WeightMatrix(const int& width, const int& height);
        explicit WeightMatrix(const std::vector<double> input);
        std::vector<double> getVector() const;
        double get(const int& x, const int& y) const;
        void set(const int& x, const int& y, const double& value);
        WeightMatrix dot(const WeightMatrix& n) const;
        void activate(const std::function<double (double)>& activation) const;
        void mutate(const double& rate);
        WeightMatrix crossover(const WeightMatrix& n);
        WeightMatrix& operator=(const WeightMatrix& m);
        ~WeightMatrix();

        friend WeightMatrix operator*(const WeightMatrix& a, const WeightMatrix& b);
        friend std::ostream& operator<<(std::ostream& out, const WeightMatrix& m);
};

#endif