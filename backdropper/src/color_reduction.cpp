#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "image_to_normal.cpp"
#include "k_means.cpp"

std::vector<std::vector<int>> load_png_to_vector(const char *filename,
                                                 int &width, int &height) {
  int channels;
  unsigned char *img = stbi_load(filename, &width, &height, &channels, 0);
  if (!img) {
    std::cerr << "failed to load image: " << filename << std::endl;
    return {};
  }

  std::vector<std::vector<int>> image_data(width * height, std::vector<int>(3));

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int pixel_index = y * width + x;
      int index = pixel_index * channels;
      image_data[pixel_index][0] = static_cast<int>(img[index]);
      image_data[pixel_index][1] = static_cast<int>(img[index + 1]);
      image_data[pixel_index][2] = static_cast<int>(img[index + 2]);
    }
  }

  stbi_image_free(img);
  return image_data;
}
bool save_vector_to_png(const char *filename,
                        const std::vector<std::vector<int>> &image_data,
                        int width, int height) {
  if (image_data.empty() ||
      image_data.size() != static_cast<size_t>(width * height)) {
    std::cerr << "image data vector is empty or has a size mismatch!"
              << std::endl;
    return false;
  }

  std::vector<unsigned char> data;
  data.reserve(width * height * 3);

  for (const auto &pixel : image_data) {
    data.push_back(static_cast<unsigned char>(pixel[0])); // r
    data.push_back(static_cast<unsigned char>(pixel[1])); // g
    data.push_back(static_cast<unsigned char>(pixel[2])); // b
  }

  int stride_in_bytes = width * 3;
  int success =
      stbi_write_png(filename, width, height, 3, data.data(), stride_in_bytes);

  return success != 0;
}

int main() {
  const char *input_filename =
      "/users/noahhan/github_projects/blender_addons/backdropper/images/"
      "poke.png";
  const char *output_filename = "/users/noahhan/github_projects/blender_addons/backdropper/images/"
                                "poke_output.png";

  // const char *normal_output_filename = "/Users/noahhan/github_projects/blender_addons/backdropper/images/"
  // "normal_output.png";

  int width = 0, height = 0;
  auto image_vector = load_png_to_vector(input_filename, width, height);
  if (image_vector.empty()) {
    std::cerr << "failed to load image vector." << std::endl;
    return 1;
  }

  std::cout << "loaded image with dimensions: " << width << " x " << height
            << std::endl;

  int k = 12;
  std::unordered_map<int, std::vector<int>> clusters =
      kMeans(k, image_vector, width, height);

  for (auto &[center_id, cluster] : clusters) {
    std::cout << "cluster " << center_id << " has " << cluster.size()
              << " points." << std::endl;
  }

  for (auto &[center_id, cluster] : clusters) {
    std::vector<int> centroid_rgb = calculateAverageRGB(cluster, image_vector);

    for (auto point : cluster) {
      image_vector[point] = centroid_rgb;
    }
  }

  std::cout << "updated centroids (first 5):" << std::endl;
  for (int i = 0; i < std::min(k, 5); ++i) {
    std::cout << "centroid " << i << ": " << image_vector[i][0] << ", "
              << image_vector[i][1] << ", " << image_vector[i][2] << std::endl;
  }

  // std::vector<std::vector<int>> normal_image = imageToNormal(image_vector);

  if (save_vector_to_png(output_filename, image_vector, width, height)) {
    std::cout << "image saved successfully to " << output_filename << std::endl;
  } else {
    std::cerr << "failed to save output image." << std::endl;
    return 1;
  }

  // if (save_vector_to_png(normal_output_filename, normal_image, width, height)) {
  //   std::cout << "Image saved successfully to " << normal_output_filename << std::endl;
  // } else {
  //   std::cerr << "Failed to save output image." << std::endl;
  //   return 1;
  // }

  // poopen();
  return 0;
}
