#include "WeightMatrix.hpp"

WeightMatrix::WeightMatrix(const int& width, const int& height): width(width), height(height)
{
    this->randomizer = Randomizer();
    this->vector = std::vector<double>(width * height);
    
    for(std::vector<double>::iterator it = this->vector.begin(); it != this->vector.end(); ++it) {
        *(it) = this->randomizer.pick(-1, 1);
    }
}

double WeightMatrix::get(const int& x, const int& y) const {
    return this->vector[y * this->width + x];
}


void WeightMatrix::set(const int& x, const int& y, const double& value) {
    this->vector[y * this->width + x] = value;
}

WeightMatrix WeightMatrix::dot(const WeightMatrix& n) const {
    WeightMatrix m(this->height, n.width);

    if (this->width != n.height) {
        throw "Matrix's dimension don't match.";
    }

    for (int y = 0; y < this->height; y++)
    {
        for (int x = 0; x < n.width; x++)
        {
            float s = 0.0;

            for (int k = 0; k < this->width; k++)
            {
                s += this->get(k, y) * n.get(x, k);
            }

            m.set(x, y, s);
        }   
    }

    return m;
}

WeightMatrix WeightMatrix::activate(const std::function<double (double)>& activation) const {
    WeightMatrix m(this->width, this->height);

    for (size_t i = 0; i < vector.size(); ++i) {
        m.vector[i] = activation(vector[i]);
    }

    return m;
}

WeightMatrix WeightMatrix::mutate(const double& rate) {
    WeightMatrix m(this->width, this->height);

    for (size_t i = 0; i < vector.size(); ++i) {
        double r = randomizer.pick(0, 1);
        if (r < rate) {
            m.vector[i] += this->randomizer.pickNorm(5.0, 2.0);
            m.vector[i] = std::min(m.vector[i], 1.0);
            m.vector[i] = std::max(m.vector[i], -1.0);
        }
    }

    return m;
}

WeightMatrix WeightMatrix::crossover(const WeightMatrix& n) {
    WeightMatrix m(this->width, this->height);
    size_t p = randomizer.pick(0, this->vector.size());

    std::vector<double>::const_iterator leftPIter(vector.cbegin());
    std::advance(leftPIter, p);
    std::vector<double> left(vector.cbegin(), leftPIter);

    std::vector<double>::const_iterator rightPIter(n.vector.cbegin());
    std::advance(rightPIter, p);
    std::vector<double> right(rightPIter, n.vector.cend());

    m.vector.insert(m.vector.end(), std::make_move_iterator(left.begin()), std::make_move_iterator(left.end()));
    m.vector.insert(m.vector.end(), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end()));

    return m;
}

WeightMatrix::~WeightMatrix() {}

std::ostream& operator<<(std::ostream& out, const WeightMatrix& m) {
    for (int i = 0; i < m.height; i++)
    {
        for (int j = 0; j < m.width; j++)
        {
            out << m.get(j, i) << ' ';
        }
        out << std::endl;
    }
    
    return out;
}

WeightMatrix operator*(const WeightMatrix& a, const WeightMatrix& b) {
    return a.dot(b);
}