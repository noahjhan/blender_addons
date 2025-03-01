from PIL import Image, ImageFilter
import numpy as np
import backdropper.src.python.disjoint_set as disjoint_set

# proprocessing
# edge detection
# color reduction

def listify(path):
    with Image.open(path) as img:
        width, height = img.size
        img = img.convert("RGB")
        
        arr_3D = np.array(img)
        pixels = arr_3D.reshape(-1, arr_3D.shape[2])

        dataset = disjoint_set.DisjointSet(width * height)

        # final = contrast_merge(pixels, width, height, 2)
        final = toPseudoVoronoi(pixels, width, height, dataset)
        return Image.fromarray(final.reshape(height, width, -1), mode="RGB")

# img     ->  as 2D array [index][R, G, B]
# width   ->  image width
# height  ->  image height
# dataset ->  disjoint set of coordinates
# (index = x + (y * x))
# (size = width * height)
def toPseudoVoronoi(img, width, height, dataset):
    # generate array of edge coordinates
    # i.e. pixel at coordinate is edge if recently unioned
    num_passes = 1
    prev_num_sets = 0

    # is_edge = np.full((width * height), True)
    while dataset.numSets() > 5000: 
        if prev_num_sets == dataset.numSets():
            print("No changes made, exiting early...")
            break
        
        prev_num_sets = dataset.numSets()

        print(f"Iteration: {num_passes}")
        print(f"Number of Sets: {dataset.numSets()}")
        num_passes += 1

        for elem in range(width*height):
            # if not is_edge[elem]:
            #     continue
                
            x = elem % width  
            y = elem // width

            if x == 0 or x == width - 1 or y == 0 or y == height - 1:
                continue

            pixel = img[elem]

            adjacent = [
                (elem - width, img[elem - width]),           # Up
                (elem + width, img[elem + width]),           # Down
                (elem - 1, img[elem - 1]),                   # Left
                (elem + 1, img[elem + 1]),                   # Right
                (elem - width - 1, img[elem - width - 1]),  # Up-Left
                (elem - width + 1, img[elem - width + 1]),   # Up-Right
                (elem + width - 1, img[elem + width - 1]),   # Down-Left
                (elem + width + 1, img[elem + width + 1])    # Down-Right
            ]

            min_idx = elem
            min_contrast = 255 * 3

            for neighbor in adjacent:
                contrast = calculate_contrast(pixel, neighbor[1])
                hue_contrast = calculate_hue_contrast(pixel, neighbor[1])

                if contrast > 10:
                    continue

                if hue_contrast > 15:
                    continue

                if contrast < min_contrast and dataset.find(elem) != dataset.find(neighbor[0]):
                    min_contrast = contrast
                    min_idx = neighbor[0]
            
            dataset.setunion(elem, min_idx) # combine with lowest contrast neighbor
            # is_edge[elem] = False

    for elem in range(width*height):
        img[elem] = img[dataset.find(elem)]
    
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
