from PIL import Image, ImageFilter
import numpy as np
import disjoint_set


# proprocessing
# edge detection
# color reduction

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

    
def contrast_merge(img, dataset, width, height, num_passes, contrast_threshold=30):
    for iters in range(num_passes):
        print(f"Pass {iters}")
        changes = 0  # Track changes to enable early stopping
        
        for elem in range(width * height):
            x = elem % width  # column
            y = elem // width  # row

            # Ensure the pixel is not on the border
            if x == 0 or x == width - 1 or y == 0 or y == height - 1:
                continue
            
            pixel = img[elem]
            
            neighbors = [
                (elem - width, img[elem - width]),  # Up
                (elem + width, img[elem + width]),  # Down
                (elem - 1, img[elem - 1]),         # Left
                (elem + 1, img[elem + 1]),         # Right
                (elem - width - 1, img[elem - width - 1]),  # Up-Left
                (elem - width + 1, img[elem - width + 1]),  # Up-Right
                (elem + width - 1, img[elem + width - 1]),  # Down-Left
                (elem + width + 1, img[elem + width + 1])   # Down-Right
            ]
            
            min_contrast = 180
            min_neighbor_idx = None

            for neighbor_idx, neighbor_pixel in neighbors:
                contrast = calculate_hue_contrast(pixel, neighbor_pixel)
                if contrast < min_contrast:
                    min_contrast = contrast
                    min_neighbor_idx = neighbor_idx
                    changes += 1

            if min_contrast < 180:
                dataset.setunion(elem, min_neighbor_idx)

        # Early stopping if no changes occur
        if changes == 0:
            print("No changes in this pass, stopping early.")
            break
    
    # Final pass: Assign pixels to their root representative
    for elem in range(width * height):
        root = dataset.find(elem)
        img[elem] = img[root]

    return img



def calculate_contrast(pixel, neighbor):
    return np.sum(np.abs(pixel - neighbor))

def rgb_to_hue(pixel):
    r, g, b = pixel[0] / 255.0, pixel[1] / 255.0, pixel[2] / 255.0

    max_color = max(r, g, b)
    min_color = min(r, g, b)
    delta = max_color - min_color

    if delta == 0:
        return 0 

    if max_color == r:
        hue = (g - b) / delta
    elif max_color == g:
        hue = 2.0 + (b - r) / delta
    else:
        hue = 4.0 + (r - g) / delta

    hue *= 60
    if hue < 0:
        hue += 360

    return hue


def calculate_hue_contrast(pixel, neighbor):
    return abs(rgb_to_hue(pixel) - rgb_to_hue(neighbor)) % 360

final = listify("/Users/noahhan/github_projects/blender_addons/backdropper/images/poke.jpeg")

final.show()

final = final.convert("L")

final = final.filter(ImageFilter.FIND_EDGES)

final.save(r"backdropper/images/voronoi_edge_sample.png")
