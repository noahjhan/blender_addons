#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <vector>

#define DIMENSION (3) // RGB

template <typename T>
double euclideanDist(const std::vector<T> &left, const std::vector<T> &right) {
  return std::sqrt(std::inner_product(
      left.begin(), left.end(), right.begin(), 0.0, std::plus<>(),
      [](T a, T b) { return (a - b) * (a - b); }));
}

std::vector<std::vector<int>>
selectClusterCenters(const int &k, const unsigned &width,
                     const unsigned &height,
                     const std::vector<std::vector<int>> &points) {
  std::srand(std::time(nullptr));
  std::vector<std::vector<int>> centers;
  std::set<int> unique_pixels;

  int first_center = std::rand() % (width * height);
  centers.push_back(points[first_center]);
  unique_pixels.insert(first_center);

  while (centers.size() < k) {
    std::vector<double> distances(width * height,
                                  std::numeric_limits<double>::max());

    for (int i = 0; i < width * height; ++i) {
      if (unique_pixels.find(i) != unique_pixels.end())
        continue;

      double min_dist = std::numeric_limits<double>::max();
      for (const auto &center : centers) {
        double dist = euclideanDist(points[i], center);
        min_dist = std::min(min_dist, dist);
      }
      distances[i] = min_dist;
    }

    double max_dist = *std::max_element(distances.begin(), distances.end());
    int next_center =
        std::distance(distances.begin(),
                      std::find(distances.begin(), distances.end(), max_dist));
    centers.push_back(points[next_center]);
    unique_pixels.insert(next_center);
  }

  return centers;
}

std::vector<int>
calculateAverageRGB(const std::vector<int> &cluster_points,
                    const std::vector<std::vector<int>> &points) {
  int sum_r = 0, sum_g = 0, sum_b = 0;

  for (const int idx : cluster_points) {
    sum_r += points[idx][0];
    sum_g += points[idx][1];
    sum_b += points[idx][2];
  }

  int avg_r = sum_r / cluster_points.size();
  int avg_g = sum_g / cluster_points.size();
  int avg_b = sum_b / cluster_points.size();

  return {avg_r, avg_g, avg_b};
}

void assignPointsToClusters(const std::vector<std::vector<int>> &points,
                            const std::vector<std::vector<int>> &centroids,
                            std::map<int, std::vector<int>> &clusters, int k) {
  for (int coord = 0; coord < points.size(); ++coord) {
    std::vector<double> distance_to_center;

    for (int centroid = 0; centroid < k; ++centroid) {
      distance_to_center.push_back(
          euclideanDist(points[coord], centroids[centroid]));
    }

    int cluster_ass = std::distance(
        distance_to_center.begin(),
        std::min_element(distance_to_center.begin(), distance_to_center.end()));
    clusters[cluster_ass].push_back(coord);
  }
}

std::vector<std::vector<int>>
updateCentroids(const std::map<int, std::vector<int>> &clusters,
                const std::vector<std::vector<int>> &points,
                const std::vector<std::vector<int>> &centroids) {
  std::vector<std::vector<int>> new_centroids;

  for (const auto &[cluster_id, cluster_points] : clusters) {
    if (cluster_points.empty()) {
      int rand_idx = rand() % points.size();
      new_centroids.push_back(points[rand_idx]);
      continue;
    }

    std::vector<int> new_centroid = calculateAverageRGB(cluster_points, points);
    new_centroids.push_back(new_centroid);
  }

  return new_centroids;
}

std::map<int, std::vector<int>> kMeans(int k,
                                       std::vector<std::vector<int>> &points,
                                       const unsigned &width,
                                       const unsigned &height) {
  std::vector<std::vector<int>> centroids =
      selectClusterCenters(k, width, height, points);
  std::map<int, std::vector<int>> clusters;
  bool converged = false;
  int num_passes = 0;
  double epsilon = 1e-4;

  while (!converged) {
    if (num_passes++ == 50) {
      std::cout << "Max iterations reached. Exiting.\n";
      return clusters;
    }

    clusters.clear();

    assignPointsToClusters(points, centroids, clusters, k);

    std::vector<std::vector<int>> new_centroids =
        updateCentroids(clusters, points, centroids);

    converged = true;
    for (int i = 0; i < k; ++i) {
      if (euclideanDist(centroids[i], new_centroids[i]) > epsilon) {
        converged = false;
        break;
      }
    }

    centroids = new_centroids;
  }

  return clusters;
}
