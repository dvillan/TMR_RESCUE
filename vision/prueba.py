from PIL import Image

filename = "robot.png"

image = Image.open(filename)

new_image = image.rotate(180)

new_image.show()