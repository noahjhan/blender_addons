// #define STBI_NO_HDR
// #define STB_IMAGE_IMPLEMENTATION
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "stb_image.h"
// #include "stb_image_write.h"
// #include <cmath>
// #include <cstdlib>
// #include <ctime>
// #include <iostream>
// #include <map>
// #include <set>
// #include <vector>

// #define DIMENSION (3)

// double euclideanDist(const std::vector<double> &left,
//                      const std::vector<double> &right) {
//   double sum = 0.0;
//   for (unsigned i = 0; i < DIMENSION; ++i) {
//     sum += (left[i] - right[i]) * (left[i] - right[i]);
//   }
//   return sqrt(sum);
// }

// std::vector<int>
// selectClusterCenters(const std::vector<std::vector<int>> &vect,
//                      const unsigned &width, const unsigned &height,
//                      const unsigned &num_centers) {
//   std::srand(std::time(nullptr));
//   std::vector<int> centers;
//   std::set<int> unique_pixels;

//   while (centers.size() < num_centers) {
//     int idx = std::rand() % (width * height);
//     if (unique_pixels.find(idx) == unique_pixels.end()) {
//       unique_pixels.insert(idx);
//       centers.push_back(idx);
//     }
//   }
//   return centers;
// }

// std::map<int, int>
// kMeans(const std::vector<std::vector<int>> &image_data,
//        const unsigned &width, const unsigned &height,
//        const unsigned &num_centers) {
//   std::vector<int> cluster_centers =
//       selectClusterCenters(image_data, width, height, num_centers);
//   std::map<int, int> coord_to_center;

//   bool termination_criteria = false;
//   int iterations = 0, max_iterations = 10;

//   while (!termination_criteria && iterations < max_iterations) {
//     iterations++;
//     termination_criteria = true;

//     std::vector<std::vector<double>> new_centers(
//         num_centers, std::vector<double>(DIMENSION, 0.0));
//     std::vector<int> cluster_counts(num_centers, 0);

//     // Assign each pixel to the closest center
//     for (size_t i = 0; i < width * height; ++i) {
//       int closest_center = 0;
//       double min_dist =
//           euclideanDist(image_data[i], image_data[cluster_centers[0]]);

//       for (size_t j = 1; j < cluster_centers.size(); ++j) {
//         double dist =
//             euclideanDist(image_data[i], image_data[cluster_centers[j]]);
//         if (dist < min_dist) {
//           min_dist = dist;
//           closest_center = j;
//         }
//       }

//       coord_to_center[i] = closest_center;

//       // Add pixel to the new cluster center sum
//       for (size_t c = 0; c < DIMENSION; ++c) {
//         new_centers[closest_center][c] += image_data[i][c];
//       }
//       cluster_counts[closest_center]++;
//     }

//     // Recompute the cluster centers
//     for (size_t i = 0; i < num_centers; ++i) {
//       if (cluster_counts[i] > 0) {
//         for (size_t c = 0; c < DIMENSION; ++c) {
//           new_centers[i][c] /= cluster_counts[i];
//         }
//       }
//     }

//     // Check for convergence (if any center changed, continue iterating)
//     termination_criteria = true;
//     for (size_t i = 0; i < num_centers; ++i) {
//       if (euclideanDist(image_data[cluster_centers[i]], new_centers[i])
//       > 1.0) {
//         cluster_centers[i] = static_cast<int>(new_centers[i][0]);
//         termination_criteria = false;
//       }
//     }
//   }

//   return coord_to_center;
// }

// int main() {
//   int width, height, channels;
//   unsigned char *img = stbi_load("/Users/noahhan/github_projects/"
//                                  "blender_addons/backdropper/images/poke.png",
//                                  &width, &height, &channels, 0);

//   if (!img) {
//     std::cerr << "Failed to load image." << std::endl;
//     return 1;
//   }

//   // Store the image in a 2D vector (width * height) for each pixel's RGB
//   values std::vector<std::vector<int>> image_data(
//       width * height, std::vector<int>(channels));

//   for (int i = 0; i < width * height; ++i) {
//     for (int c = 0; c < channels; ++c) {
//       image_data[i][c] = img[i * channels + c];
//     }
//   }

//   int clustoid = 300; // Number of clusters
//   std::map<int, int> clusters = kMeans(image_data, width, height, clustoid);

//   std::vector<std::vector<int>> cluster_centers(
//       clustoid, std::vector<int>(channels, 0));
//   std::vector<int> cluster_counts(clustoid, 0);

//   // Assign pixel colors based on the cluster centers
//   for (const auto &[pixel_idx, cluster_idx] : clusters) {
//     for (int c = 0; c < channels; ++c) {
//       cluster_centers[cluster_idx][c] += image_data[pixel_idx][c];
//     }
//     cluster_counts[cluster_idx]++;
//   }

//   // Average the cluster centers
//   for (int i = 0; i < clustoid; ++i) {
//     if (cluster_counts[i] > 0) {
//       for (int c = 0; c < channels; ++c) {
//         cluster_centers[i][c] /= cluster_counts[i];
//       }
//     }
//   }

//   // Reassign the pixel colors to the computed cluster centers
//   for (const auto &[pixel_idx, cluster_idx] : clusters) {
//     for (int c = 0; c < channels; ++c) {
//       image_data[pixel_idx][c] = cluster_centers[cluster_idx][c];
//     }
//   }

//   // Allocate memory for the new image and save it
//   unsigned char *new_img = new unsigned char[width * height * channels];
//   for (int i = 0; i < width * height; ++i) {
//     for (int c = 0; c < channels; ++c) {
//       new_img[i * channels + c] = image_data[i][c];
//     }
//   }

//   if (!stbi_write_png("output2.png", width, height, channels, new_img,
//                       width * channels)) {
//     std::cerr << "Failed to save image." << std::endl;
//   }

//   stbi_image_free(img); // Free the original image data
//   delete[] new_img;     // Free the new image data

//   std::cout << "Width: " << width << ", Height: " << height
//             << ", Channels: " << channels << std::endl;

//   return 0;
// }
