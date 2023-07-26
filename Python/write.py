from torch.utils.tensorboard import SummaryWriter

writer = SummaryWriter("Python/logs") # 在工作区下的logs文件夹中存放

for i in range(100):
	writer.add_scalar("y=2x",2*i,i)

from PIL import Image
image_path1 = "/Users/obersturrrm/Downloads/data/train/ants_image/0013035.jpg"
img1=Image.open(image_path1)
image_path2 = "/Users/obersturrrm/Downloads/data/train/bees_image/16838648_415acd9e3f.jpg"
img2=Image.open(image_path2)

import numpy as np
img_array = np.array(img1)
writer.add_image("test",img_array,1,dataformats='HWC')
img_array = np.array(img2)
writer.add_image("test",img_array,2,dataformats='HWC')

writer.close()

