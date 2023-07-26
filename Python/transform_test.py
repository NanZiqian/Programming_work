from PIL import Image
from torch.utils.tensorboard import SummaryWriter
from torchvision import transforms

writer = SummaryWriter("Python/logs")
img = Image.open("/Users/obersturrrm/Downloads/data/train/bees_image/16838648_415acd9e3f.jpg")

trans_totensor = transforms.ToTensor()# 不写transforms.
img_tensor = trans_totensor(img)
writer.add_image("Tensor",img_tensor)

# Normalize
print(img_tensor[0][0][0])
trans_norm = transforms.Normalize([0.5,0.5,0.5],[0.5,0.5,0.5])
img_norm = trans_norm(img_tensor)# trans_norm.forward(img)也可以
print(img_norm[0][0][0])
writer.add_image("Normalize",img_norm)

writer.close()