#include <vector>
#include <cmath>
#include <iostream>

#define dimension (3)

double euclidianDist(std::vector<int> left, std::vector<int> right) {
    double sum = 0.0;
    for (unsigned i = 0; i < dimension; ++i) sum += (left[dimension] - right[dimension]) * (left[dimension] - right[dimension]);
    return sqrt(sum);

}

int main() {
    std::vector<int> left = {1, 2, 3}; 
    std::vector<int> right= {1, 1, 3};

    std::cout << euclidianDist(left, right) << std::endl;

    return 0;
}