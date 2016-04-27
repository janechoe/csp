from PIL import Image
image = Image.open("erb2.png")
pix  = image.load()
image_size = image.size
x = 0
y = 0
r_stored = 0;
g_stored = 0;
b_stored = 0;
print(image_size);
"""
while x < image_size[0]:
    while y < image_size[1]:
        r, g, b, a = pix[x,y]
        if (r_stored != r and g_stored != g and b_stored != b):
            print x,y,r,g,b
            r_stored = r
            g_stored = g
            b_stored = b
        #print r, g, b
        y = y + 1
    y = 0
    x = x + 1 """
