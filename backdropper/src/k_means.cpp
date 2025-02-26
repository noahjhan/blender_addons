#include <iostream>
#include <numeric>
#include <vector>

#define DIMENSION (3) // RGB

template <typename T>
double euclideanDist(const std::vector<T> &left, const std::vector<T> &right) {
  if (left.size() != right.size() || left.size() != DIMENSION ||
      right.size() != DIMENSION) {
    std::cerr << "ERROR: undefined behavior\nsize of left vector: "
              << left.size() << "\nsize of right vector: " << right.size()
              << "\nDimension = " << DIMENSION << '\n'
              << std::endl;
  }

  return std::sqrt(std::inner_product(
      left.begin(), left.end(), right.begin(), 0.0, std::plus<>(),
      [](T a, T b) { return (a - b) * (a - b); }));
}

int main(int argc, char **argv) { return 0; }