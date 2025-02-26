from PIL import Image, ImageFilter
image = Image.open(r"/Users/noahhan/github_projects/blender_addons/backdropper/images/poke.jpeg")

image = image.convert("L")

image = image.filter(ImageFilter.FIND_EDGES)

image.save(r"Edge_Sample.png")