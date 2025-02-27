#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
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

std::vector<int> selectClusterCenters(const int &k, const unsigned &width,
                                      const unsigned &height) {
  std::srand(std::time(nullptr));
  std::vector<int> centers;
  std::set<int> unique_pixels;

  while (centers.size() < k) {
    int idx = std::rand() % (width * height);
    if (unique_pixels.find(idx) == unique_pixels.end()) {
      unique_pixels.insert(idx);
      centers.push_back(idx);
    }
  }
  return centers;
}

int calculateCentroid(int width, int height, std::vector<int> clusters,
                      int cluster) {
  for (const auto cluster : clusters) {
  }
}

std::vector<std::vector<int>> kMeans(int &k,
                                     std::vector<std::vector<int>> &points,
                                     const unsigned &width,
                                     const unsigned &height) {
  std::vector<int> centroids = selectClusterCenters(k, width, height);
  std::vector<std::vector<int>> clusters;
  bool converged = false;
  while (!converged) {
    clusters.clear();

    for (int coord = 0; coord < points.size(); ++coord) {
      std::vector<int> distance_to_center;
      for (int centroid = 0; centroid < k; ++centroid) {
        distance_to_center.push_back(
            euclideanDist(points[coord], points[centroids[centroid]]));
      }

      int cluster_ass =
          std::distance(std::begin(distance_to_center),
                        std::min_element(std::begin(distance_to_center),
                                         std::end(distance_to_center)));

      clusters[cluster_ass].push_back(coord);
    }

    std::vector<int> new_centroids;
    for (const auto cluster : clusters) {
      int sum_x = 0;
      int sum_y = 0;
      int size = cluster.size();
      for (const auto point : cluster) {
        sum_x += point % width;
        sum_y += point / width;
      }
      sum_x /= size;
      sum_y /= size;
      int new_loc = (sum_x + sum_y) / 2;
      new_centroids.push_back(new_loc);
    }
    converged = (new_centroids == centroids);
    centroids = new_centroids;

    if (converged) {
      return clusters;
    }
  }
}

int main(int argc, char **argv) { return 0; }
