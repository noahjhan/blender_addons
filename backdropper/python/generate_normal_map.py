import cv2
import numpy as np

def generate_normal_map(image_path, strength=1.0):
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    if img is None:
        raise ValueError("Image could not be loaded.")

    grad_x = cv2.Sobel(img, cv2.CV_64F, 1, 0, ksize=3)
    grad_y = cv2.Sobel(img, cv2.CV_64F, 0, 1, ksize=3)

    grad_x = grad_x * strength
    grad_y = grad_y * strength

    normal_map = np.zeros((img.shape[0], img.shape[1], 3), dtype=np.uint8)

    normal_map[..., 0] = np.clip(((grad_x + 255) / 2), 0, 255) 
    normal_map[..., 1] = np.clip(((grad_y + 255) / 2), 0, 255) 
    normal_map[..., 2] = 255 

    return normal_map

image_path = '/Users/noahhan/github_projects/blender_addons/backdropper/images/poke.png' 
normal_map = generate_normal_map(image_path)

cv2.imwrite('normal_map.png', normal_map)

cv2.imshow('Normal Map', normal_map)
cv2.waitKey(0)
cv2.destroyAllWindows()
