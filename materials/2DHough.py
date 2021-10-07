#!/usr/bin/env python
# coding: utf-8

# In[4]:


from math import hypot, pi, cos, sin
from PIL import Image


def hough(image, width=1500, height=1200):
    image_threshold = 150
    image_w, image_h = image.size

    hough_2d = Image.new("L", (width, height))# convert image to monochrome黑白的
    pixel_im = image.load()
    pixel_hough_2d = hough_2d.load()

    #hypot : Return the Euclidean norm, sqrt(x*x + y*y). This is the length of the vector from the origin to point (x, y).
    diagonal = hypot(image_w, image_h)
    dr = diagonal / (height/2)
    dtheta = pi / width

    for x in range(0, image_w):
        for y in range(0, image_h):
            pixel = pixel_im[x, y]
            if pixel >= image_threshold:
                for rw in range(0, width):
                    theta = dtheta * rw
                    r = x*cos(theta) + y*sin(theta)
                    ry = height/2 + int(r/dr+0.5)
                    pixel_hough_2d[rw, ry] += 1
    return hough_2d


dart_image = Image.open("dart10.jpg").convert("L")
hough_2d = hough(dart_image)
hough_2d.show()



# In[ ]:
