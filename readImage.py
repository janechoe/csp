from PIL import Image
image = Image.open("erb1.png")
pix  = image.load()
pix[0,0]
width, height = image.size
all_colors = []
# print(pix)
print width
print height
x = 0
y = 0
while y < height:
    x = 0
    while x < width:
        color = pix[x,y]
        # black = 0
        # green = 1
        # white = 2
        # other = 0
        if ( color==(0,0,0,255) or color == (255, 0, 0, 255) ):
            print 0
        elif (color ==(0, 255, 0, 255)):
            print 1
        elif (color == (255, 255, 255, 255) or color == (255, 0, 255, 255) ):
            print 2
        if color not in all_colors:
            all_colors.append(color)
        # print all_colors
        x = x + 1
    y = y+1
