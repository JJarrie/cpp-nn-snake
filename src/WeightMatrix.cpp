#include "WeightMatrix.hpp"

WeightMatrix::WeightMatrix(const int& width, const int& height): width(width), height(height)
{
    this->vector = std::vector<double>(width * height);
    
    for(std::vector<double>::iterator it = this->vector.begin(); it != this->vector.end(); ++it) {
        *(it) = Randomizer::get().pick(-1, 1);
    }
}

WeightMatrix::WeightMatrix(const std::vector<double> input): width(1), height(input.size() + 1) 
{
    this->vector = std::vector<double>(input);
    this->vector.push_back(1);
}

std::vector<double> WeightMatrix::getVector() const {
    return vector;
}

double WeightMatrix::get(const int& x, const int& y) const {
    return this->vector[y * this->width + x];
}


void WeightMatrix::set(const int& x, const int& y, const double& value) {
    this->vector[y * this->width + x] = value;
}

WeightMatrix WeightMatrix::dot(const WeightMatrix& n) const {

    if (width != n.height) {
        throw "Matrix's dimension don't match.";
    }

    WeightMatrix m(n.width, this->height);


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

void WeightMatrix::activate(const std::function<double (double)>& activation) {
    std::transform(vector.begin(), vector.end(), vector.begin(), activation);
}

void WeightMatrix::mutate(const double& rate) {
    std::for_each(vector.begin(), vector.end(), [this, rate](double &n) {
        double r = Randomizer::get().pick(0, 1);
        if (r < rate) {
            n += Randomizer::get().pick(-1, 1);
            n = std::min(n, 1.0);
            n = std::max(n, -1.0);
        }

    });
}

WeightMatrix WeightMatrix::crossover(const WeightMatrix& n) {
    WeightMatrix m(this->width, this->height);
    size_t p = Randomizer::get().pick(0, this->vector.size());

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

WeightMatrix& WeightMatrix::operator=(const WeightMatrix& m) {
    width = m.width;
    height = m.height;
    vector = std::vector<double>(m.vector);

    return *this;
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