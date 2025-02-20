import cv2
import numpy as np
from scipy import stats

def get_mean_color(region):
    return np.mean(region, axis=(0, 1))

def get_mode_color(region):
    # Flatten the region and find the most frequent color
    region_flat = region.reshape(-1, region.shape[-1])
    mode_color = stats.mode(region_flat, axis=0)[0]
    return mode_color[0]

def contrast_measure(region):
    # Measure contrast using the standard deviation of pixel intensities
    return np.std(region)

def process_image(image_path):
    # Load image
    img = cv2.imread(image_path)
    
    # Convert to grayscale for edge detection
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    # Perform Canny edge detection
    edges = cv2.Canny(gray, 100, 200)

    # Create a mask for the non-edge regions (between edges)
    mask = np.ones_like(edges) * 255
    mask[edges != 0] = 0  # 0 for edges

    # Define a kernel to find contours and create regions for filling
    kernel = np.ones((5, 5), np.uint8)
    dilated_edges = cv2.dilate(edges, kernel, iterations=1)
    
    # Create the final result image
    result_img = img.copy()
    
    # Loop through each region and fill based on contrast
    for y in range(0, img.shape[0], 20):  # Step through rows in blocks
        for x in range(0, img.shape[1], 20):  # Step through columns in blocks
            region = img[y:y+20, x:x+20]
            if region.shape[0] == 0 or region.shape[1] == 0:
                continue

            # Determine the contrast of the region
            contrast = contrast_measure(region)
            
            if contrast < 20:  # Low contrast
                fill_color = get_mean_color(region)
            else:  # High contrast
                fill_color = get_mode_color(region)
            
            # Fill the region with the selected color
            result_img[y:y+20, x:x+20] = fill_color

    # Return the resulting image with filled regions
    return result_img

# Example usage:
image_path = 'your_image.jpg'
result = process_image(image_path)

# Save or show the result image
cv2.imwrite('result_image.jpg', result)
cv2.imshow('Processed Image', result)
cv2.waitKey(0)
cv2.destroyAllWindows()
