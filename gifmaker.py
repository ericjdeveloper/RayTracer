import glob
from PIL import Image
from wand.image import Image as WImage
import numpy as np
import time

filelist = glob.glob('frames/*.ppm')
f_count = 0

for fname in filelist:
    img = WImage(filename=fname)
    frame_num = fname[7:-4]
    img.format = 'jpeg'
    img.save(filename='jpeg/' + frame_num + '.jpg')
    f_count += 1

images = []
for i in range(f_count):
 images.append((Image.open('jpeg/f'+ str(i) + '.jpg')))

images[0].save('output.mp4', save_all=True, append_images=images[1:], optimize=False, duration=40, loop=0)
