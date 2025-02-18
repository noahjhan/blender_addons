#generate depth layer:
    #find low contrast areas
    #generate and scale squares until collision
    # proportion of square * light level = depth

#disjoint set?

#for each pixel in image
#merge with neighbor/set with lowest contrast

from PIL import Image
import numpy as np
import disjoint_set

pixels = []

from PIL import Image
import numpy as np

def listify(path):
    with Image.open(path) as img:
        width, height = img.size
        print(width)
        print(height)
        print(width * height)
        img = img.convert("RGB")
        pixels_3D = np.array(img)
        pixels = pixels_3D.reshape(-1, pixels_3D.shape[2])
        pixels_reshape = pixels.reshape(width, height, -1)
        final = Image.fromarray(pixels_reshape, mode="RGB")
        dataset = disjoint_set.DisjointSet(pixels)
        contrast_merge(dataset, width, height)
        return final
    
def contrast_merge(dataset, width, height):
    for elem in range(width * height):
        x = elem % width  # Get the x-coordinate (column)
        y = elem // width  # Get the y-coordinate (row)

        # Skip the first and last rows, and the first and last columns
        if x == 0 or x == width - 1 or y == 0 or y == height - 1:
            continue
        
        # Get the pixel value for the current position
        pixel = dataset.getValue(elem)

        contrasts = [
            (calculate_contrast(pixel, dataset.getValue(elem - width)), (elem - width)),      # Up
            (calculate_contrast(pixel, dataset.getValue(elem + width)), (elem + width)),      # Down
            (calculate_contrast(pixel, dataset.getValue(elem - 1)), (elem - 1)),             # Left
            (calculate_contrast(pixel, dataset.getValue(elem + 1)), (elem + 1)),             # Right
            (calculate_contrast(pixel, dataset.getValue(elem - width - 1)), (elem - width - 1)), # Up-Left (diagonal)
            (calculate_contrast(pixel, dataset.getValue(elem - width + 1)), (elem - width + 1)), # Up-Right (diagonal)
            (calculate_contrast(pixel, dataset.getValue(elem + width - 1)), (elem + width - 1)), # Down-Left (diagonal)
            (calculate_contrast(pixel, dataset.getValue(elem + width + 1)), (elem + width + 1))  # Down-Right (diagonal)
        ]

        # Find the minimum contrast value and its associated coordinate
        min_contrast = min(contrasts, key=lambda x: x[0])  # Get the tuple with the minimum contrast value
        
        # Union operation to set the value
        dataset.setunion(elem, min_contrast[1])  # min_contrast[1] gives the coordinate with minimum contrast
        
        # Print the size of the set at the current element
        print(dataset.size(elem))   
    # coord = col + (row * width)
    # for each non-edge pixel
    #   merge with pixel most similar

    # for each merge operation
    #   reduce total_sets by one
    #   end when total_sets = num_sets

def calculate_contrast(pixel, neighbor):
    sum = 0
    for i in range(3):
        sum += np.abs(pixel[i] - neighbor[i])
    return sum

listify("/Users/noahhan/github_projects/blender_addons/backdropper/images/poke.jpeg").show()

