from PIL import Image
image = Image.open("data/erb2.png")
pix  = image.load()
image_size = image.size
x = 0
y = 0
while x < image_size[0]:
    while y < image_size[1]:
        r, g, b, a = pix[x,y]
        print x, y, r, g, b
        y = y + 1
    y = 0
    x = x + 1
