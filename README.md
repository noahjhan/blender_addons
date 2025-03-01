# Image K-Means Clustering and Processing

## Description

This is a collection of various addons for Blender - 3D Graphics Software. 

Currently developing a tool to compress and convert image files to a normal mapping.

This project provides a C++ file for performing K-Means clustering on an image, allowing you to process and quantize the colors of an image. The image is loaded as a vector, processed with the K-Means clustering algorithm to group similar colors, and then saved back as a new image.

The tool uses the [stb_image](https://github.com/nothings/stb) and [stb_image_write](https://github.com/nothings/stb) libraries to handle image loading and saving. The K-Means clustering algorithm is applied to the RGB values of each pixel in the image.

## Features

- Load PNG images into a 2D vector representation.
- Perform K-Means clustering on image pixels based on RGB values.
- Update image colors based on cluster centroids.
- Save the processed image as a PNG file.
- Customizable number of clusters (`k`).
- Will soon be integrated into Blender using bpy API and Cython
  
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
... etc
updated centroids (first 5):
centroid 0: 163, 67, 68
centroid 1: 163, 67, 68
centroid 2: 148, 93, 68
centroid 3: 168, 121, 87
centroid 4: 189, 148, 119
image saved successfully to poke_output.png