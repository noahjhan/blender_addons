// #include <algorithm> // For std::min and std::max
// #include <cmath>
// #include <iostream>
// #include <vector>

// // Define a struct to represent a 3D vector (for normals)
// struct Vec3 {
//   float x, y, z;
//   Vec3() : x(0), y(0), z(0) {}
//   Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

//   // Normalize the vector
//   void normalize() {
//     float length = std::sqrt(x * x + y * y + z * z);
//     if (length != 0) {
//       x /= length;
//       y /= length;
//       z /= length;
//     }
//   }
// };

// // Function to create a normal map from an image
// std::vector<std::vector<int>> imageToNormal(const std::vector<std::vector<int>> &image) {
//   int width = image[0].size();
//   int height = image.size();
//   std::vector<std::vector<int>> normalMap(height, std::vector<int>(width, 0));

//   // Sobel operator kernels for gradient calculation
//   int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
//   int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

//   // Loop through the image and calculate the gradients
//   for (int y = 1; y < height - 1; ++y) {
//     for (int x = 1; x < width - 1; ++x) {
//       int gradX = 0, gradY = 0;

//       // Apply the Sobel operator to the grayscale intensity values (average of RGB)
//       for (int ky = -1; ky <= 1; ++ky) {
//         for (int kx = -1; kx <= 1; ++kx) {
//           int pixel = image[y + ky][x + kx]; // Assuming RGB image
//           // Extract RGB components
//           int r = (pixel >> 16) & 0xFF;
//           int g = (pixel >> 8) & 0xFF;
//           int b = pixel & 0xFF;

//           // Convert RGB to grayscale intensity
//           int intensity = static_cast<int>(r * 0.2989 + g * 0.5870 + b * 0.1140);
//           gradX += intensity * sobelX[ky + 1][kx + 1];
//           gradY += intensity * sobelY[ky + 1][kx + 1];
//         }
//       }

//       // Compute the normal vector based on gradients
//       Vec3 normal;
//       normal.x = gradX;
//       normal.y = gradY;
//       normal.z = 255.0f; // Increased Z value for better depth representation

//       // Normalize the normal vector
//       normal.normalize();

//       // Encode the normal vector as RGB values
//       int r = static_cast<int>((normal.x * 0.5 + 0.5) * 255); // Normalized to range [0, 255]
//       int g = static_cast<int>((normal.y * 0.5 + 0.5) * 255); // Normalized to range [0, 255]
//       int b = static_cast<int>((normal.z * 0.5 + 0.5) * 255); // Normalized to range [0, 255]

//       // Ensure that RGB values stay within valid range
//       r = std::min(255, std::max(0, r));
//       g = std::min(255, std::max(0, g));
//       b = std::min(255, std::max(0, b));

//       // Store the encoded normal as an RGB value in the normalMap
//       normalMap[y][x] = (r << 16) | (g << 8) | b; // Pack RGB into a single integer
//     }
//   }

//   return normalMap;
// }

// int poopen() {
//   // Example usage: create a simple 3x3 image
//   std::vector<std::vector<int>> image = {
//       {0xFF0000, 0x00FF00, 0x0000FF},
//       {0xFFFFFF, 0x808080, 0x000000},
//       {0xFF00FF, 0xFFFF00, 0x00FFFF}};

//   std::vector<std::vector<int>> normalMap = imageToNormal(image);

//   // Print out the normal map
//   for (int y = 0; y < normalMap.size(); ++y) {
//     for (int x = 0; x < normalMap[0].size(); ++x) {
//       int pixel = normalMap[y][x];
//       int r = (pixel >> 16) & 0xFF;
//       int g = (pixel >> 8) & 0xFF;
//       int b = pixel & 0xFF;
//       std::cout << "(" << r << ", " << g << ", " << b << ") ";
//     }
//     std::cout << std::endl;
//   }

//   return 0;
// }
