# Image K-Means Clustering and Processing

## Description

This project provides a tool for performing K-Means clustering on an image, allowing you to process and quantize the colors of an image. The image is loaded as a vector, processed with the K-Means clustering algorithm to group similar colors, and then saved back as a new image.

The tool uses the [stb_image](https://github.com/nothings/stb) and [stb_image_write](https://github.com/nothings/stb) libraries to handle image loading and saving. The K-Means clustering algorithm is applied to the RGB values of each pixel in the image.

## Features

- Load PNG images into a 2D vector representation.
- Perform K-Means clustering on image pixels based on RGB values.
- Update image colors based on cluster centroids.
- Save the processed image as a PNG file.
- Customizable number of clusters (`k`).
  
## Requirements

Before you can run the code, you need the following dependencies:

- **C++ Compiler** (GCC, Clang, MSVC, etc.)
- **stb_image** (included in the project)
- **stb_image_write** (included in the project)

You will also need to ensure that your development environment supports C++11 or later.

## Usage

### Compilation and Setup

1. **Download the necessary libraries**:

    - The `stb_image.h` and `stb_image_write.h` files should be placed inside the `includes` directory in your project.
    - You may need to manually configure your compiler to link against the necessary libraries if using a different setup or build system.

2. **Include the necessary headers** in your C++ project:

    ```cpp
    #define STB_IMAGE_IMPLEMENTATION
    #include "../includes/stb_image.h"

    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #include "../includes/stb_image_write.h"
    ```

3. **Implement K-Means clustering in your application**:

    The provided `k_means.cpp` file implements the main logic for the K-Means algorithm on images. The `load_png_to_vector` function loads the image as a 2D vector of RGB values, and `save_vector_to_png` saves the resulting image after clustering back into a PNG file.

4. **Run the program**:

    The main function loads an image (`poke.png` in this example), performs K-Means clustering on it with 55 clusters (`k = 55`), and saves the processed image as `poke_output.png`.

    ```cpp
    int main()
    {
      const char *input_filename = "poke.png";
      const char *output_filename = "poke_output.png";

      int width = 0, height = 0;
      auto image_vector = load_png_to_vector(input_filename, width, height);

      if (image_vector.empty())
      {
        std::cerr << "Failed to load image vector." << std::endl;
        return 1;
      }

      // K-Means clustering
      int k = 55;
      std::unordered_map<int, std::vector<int>> clusters = kMeans(k, image_vector, width, height);

      // Update centroids and colors
      for (auto &[center_id, cluster] : clusters)
      {
        std::vector<int> centroid_rgb = calculateAverageRGB(cluster, image_vector);
        for (auto point : cluster)
        {
          image_vector[point] = centroid_rgb;
        }
      }

      // Save output image
      if (save_vector_to_png(output_filename, image_vector, width, height))
      {
        std::cout << "Image saved successfully to " << output_filename << std::endl;
      }
      else
      {
        std::cerr << "Failed to save output image." << std::endl;
        return 1;
      }

      return 0;
    }
    ```

5. **Build and Run**:
    After compiling the code, you can execute the program, which will process the image and save the output as specified.

### K-Means Algorithm Details

The K-Means algorithm is applied to the image’s RGB values. The steps are as follows:

1. **Initialize centroids**:
   - Randomly select `k` points as initial cluster centers (centroids).

2. **Assign points to clusters**:
   - For each pixel, calculate the Euclidean distance to each centroid and assign the pixel to the nearest centroid.

3. **Update centroids**:
   - Recalculate the centroid for each cluster by averaging the RGB values of the pixels in that cluster.

4. **Repeat**:
   - The algorithm repeats the assignment and update steps until the centroids converge (i.e., the centroids stop moving significantly).

### Functions

- `load_png_to_vector(const char *filename, int &width, int &height)`: Loads a PNG image into a vector of RGB values.
- `save_vector_to_png(const char *filename, const std::vector<std::vector<int>> &image_data, int width, int height)`: Saves the processed image as a PNG file.
- `kMeans(int k, std::vector<std::vector<int>> &points, const unsigned &width, const unsigned &height)`: Performs the K-Means clustering algorithm on the image pixels.
- `calculateAverageRGB(const std::vector<int> &cluster_points, const std::vector<std::vector<int>> &points)`: Calculates the average RGB values for a given cluster of points.
  
## Example

If you run the code with an image like `poke.png`, the output might look like this:

```bash
cluster 0 has 7197 points.
cluster 1 has 9260 points.
cluster 2 has 7354 points.
cluster 3 has 11255 points.
cluster 4 has 7637 points.
cluster 5 has 25188 points.
cluster 6 has 10791 points.
cluster 7 has 8037 points.
cluster 8 has 20843 points.
cluster 9 has 15058 points.
cluster 10 has 10227 points.
cluster 11 has 13248 points.
cluster 12 has 26394 points.
cluster 13 has 5214 points.
cluster 14 has 16604 points.
cluster 15 has 17363 points.
cluster 16 has 36215 points.
cluster 17 has 35371 points.
cluster 18 has 23287 points.
cluster 19 has 26831 points.
cluster 20 has 7227 points.
cluster 21 has 18372 points.
cluster 22 has 16827 points.
cluster 23 has 14388 points.
cluster 24 has 7549 points.
cluster 25 has 12171 points.
cluster 26 has 7958 points.
cluster 27 has 10585 points.
cluster 28 has 6291 points.
cluster 29 has 12470 points.
cluster 30 has 14204 points.
cluster 31 has 10203 points.
cluster 32 has 23079 points.
cluster 33 has 16995 points.
cluster 34 has 15121 points.
cluster 35 has 12166 points.
cluster 36 has 10593 points.
cluster 37 has 19815 points.
cluster 38 has 5174 points.
cluster 39 has 14923 points.
cluster 40 has 13425 points.
cluster 41 has 7550 points.
cluster 42 has 28037 points.
cluster 43 has 17125 points.
cluster 44 has 14764 points.
cluster 45 has 8911 points.
cluster 46 has 8068 points.
cluster 47 has 6885 points.
cluster 48 has 15830 points.
cluster 49 has 14738 points.
cluster 50 has 11500 points.
cluster 51 has 12385 points.
cluster 52 has 10791 points.
cluster 53 has 11405 points.
cluster 54 has 16313 points.
updated centroids (first 5):
centroid 0: 163, 67, 68
centroid 1: 163, 67, 68
centroid 2: 148, 93, 68
centroid 3: 168, 121, 87
centroid 4: 189, 148, 119
image saved successfully to poke_output.png