import glob
from PIL import Image
from wand.image import Image as WImage
import numpy as np

filelist = glob.glob('frames/*.ppm')

i=0
for fname in filelist:
    img = WImage(filename=fname)
    img.format = 'jpeg'
    img.save('jpeg/f' + i + '.jpg')
    i += 1

filelist = glob.glob('jpeg/*.jpg')
images = [(Image.open(filelist)) for fname in filelist]

images[0].save('output.gif', save_all=True, append_images=images[1:], optimize=False, duration=40, loop=0)
