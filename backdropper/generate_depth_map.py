from PIL import Image
import numpy as np
import disjoint_set

def listify(path):
    with Image.open(path) as img:
        width, height = img.size
        img = img.convert("RGB")
        arr_3D = np.array(img)

        pixels = arr_3D.reshape(-1, arr_3D.shape[2])

        ordered_arr = width * height
        dataset = disjoint_set.DisjointSet(ordered_arr)

        final = contrast_merge(pixels, dataset, width, height, 1)
        return Image.fromarray(final.reshape(height, width, -1), mode="RGB")

    
def contrast_merge(img, dataset, width, height, num_passes):
    for iters in range(num_passes):
        print(f"Pass {iters}")
        for elem in range(width * height):
            x = elem % width  # column
            y = elem // width  # row

            if x == 0 or x == width - 1 or y == 0 or y == height - 1:
                continue
            
            pixel = img[elem]

            contrasts = [
                (calculate_contrast(pixel, img[elem - width]), (elem - width)),  # Up
                (calculate_contrast(pixel, img[elem + width]), (elem + width)),  # Down
                (calculate_contrast(pixel, img[elem - 1]), (elem - 1)),         # Left
                (calculate_contrast(pixel, img[elem + 1]), (elem + 1)),         # Right
                (calculate_contrast(pixel, img[elem - width - 1]), (elem - width - 1)),  # Up-Left
                (calculate_contrast(pixel, img[elem - width + 1]), (elem - width + 1)),  # Up-Right
                (calculate_contrast(pixel, img[elem + width - 1]), (elem + width - 1)),  # Down-Left
                (calculate_contrast(pixel, img[elem + width + 1]), (elem + width + 1))   # Down-Right
            ]

            min_contrast = min(contrasts, key=lambda x: x[0])

            if (min_contrast[0] < 255): # make a tolerance
                dataset.setunion(elem, min_contrast[1])


    for elem in range(width * height):
        root = dataset.find(elem)
        img[elem] = img[root]

    return img


def calculate_contrast(pixel, neighbor):
    contrast = np.sum(np.abs(pixel - neighbor))
    if contrast == 0:
        return 255 * 3
    return contrast

listify("/Users/noahhan/github_projects/blender_addons/backdropper/images/poke.jpeg").show()

