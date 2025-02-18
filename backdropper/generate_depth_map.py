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
        img = img.convert("RGB")
        pixels = np.array(img)
        final = Image.fromarray(pixels, mode="RGB")
        parent = []
        dataset = disjoint_set.DisjointSet(pixels, parent)
        return final
    
def contrast_merge(num_sets):
    
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

