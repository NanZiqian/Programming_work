import torchvision
from torch.utils.tensorboard import SummaryWriter

trans_totensor = torchvision.transforms.ToTensor()

train_set = torchvision.datasets.CIFAR10(root="./Python/dataset",train=True,
					transform=trans_totensor,download=True)
test_set = torchvision.datasets.CIFAR10(root="./Python/dataset",train=False,
					transform=trans_totensor,download=True)

writer = SummaryWriter("./Python/logs")
for i in range(10):
	img,target = test_set[i]
	writer.add_image("test_set",img,i)

writer.close()
