import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from tqdm import trange
import gc

import torch
import torch.nn as nn
import torch.optim as optim

from torchvision import  datasets, transforms
from torchvision.datasets import MNIST
from torch.utils.data import Dataset, DataLoader


class MNIST_classifier_CNN(nn.module):
    def __init__(self):
        super(MNIST_classifier_CNN, self).__init__()
        self.conv1 = nn.Conv2d(1,9,3)
        self.relu1 = nn.ReLU(True)
        #26*26*9

        self.conv2 = nn.Conv2d(9,16,3)
        self.relu2 = nn.ReLU(True)
        self.pool2 = nn.MaxPool2d(2,2)
        #24*24*16

        self

        #12*12*16 (flatten화.)