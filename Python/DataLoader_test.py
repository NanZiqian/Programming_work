import torchvision

from torch.utils.data import DataLoader
from torch.utils.tensorboard import SummaryWriter

test_data = torchvision.datasets.CIFAR10("./Python/dataset",train=False,download=True,
                                        transform=torchvision.transforms.ToTensor())

test_loader = DataLoader(dataset=test_data , batch_size = 64, shuffle = True,drop_last=False)

img,target = test_data[0]

writer = SummaryWriter("./Python/logs")
step = 0
for data in test_loader:
    imgs,targets = data
    # print(imgs.shape)
    # print(targets)
    # Result
    # torch.Size([64, 3, 32, 32])
    # tensor([9, 2, 4, 5, 7, 3, 9, 7, 2, 2, 5, 0, 3, 6, 8, 9, 9, 6, 0, 6, 2, 4, 6, 5,
            # 6, 8, 7, 0, 3, 7, 3, 8, 8, 3, 7, 0, 7, 5, 7, 1, 3, 7, 8, 8, 2, 0, 5, 3,
            # 2, 0, 9, 0, 9, 6, 6, 8, 3, 6, 7, 2, 3, 1, 4, 9])
    # ...
    writer.add_images("test_data",imgs,step)
    step = step + 1

writer.close()