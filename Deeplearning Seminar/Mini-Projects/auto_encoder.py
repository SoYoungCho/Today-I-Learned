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

if torch.cuda.is_available():
    device = torch.device('cuda')
else:
    device = torch.device('cpu')


def get_dataloader(train_batch_size, val_batch_size):
    train_dataset = datasets.MNIST('./MNIST_Dataset', train = True,
                                   download= True, transform = transforms.ToTensor())
    validation_dataset = datasets.MNIST("./MNIST_Dataset", train = False,
                                    download=True, transform=transforms.ToTensor())

    train_loader = DataLoader(dataset = train_dataset, batch_size = train_batch_size, shuffle = True)
    validation_loader = DataLoader(dataset = validation_dataset, batch_size = val_batch_size, shuffle = True)
    return train_loader, validation_loader

class MNIST_AutoEncoder(nn.Module):
    def __init__(self, mode = 'training'):
        super(MNIST_AutoEncoder, self).__init__()
        self.mode mode
        self.encoder = nn.Sequential(
            nn.Linear(28*28, 512),
            nn.ReLU(True), #in-place
            nn.Linear(512,256),
            nn.ReLU(True)
        )
        self.decoder = nn.Sequential(
            nn.Linear(256, 512),
            nn.ReLU(True),  # in-place
            nn.Linear(512, 28*28),
            nn.Sigmoid()
        )
        self.encoder_outputs =[]

    def forward(self, x):
        encoder_out = self.encoder(x)
        decoder_out = self.decoder(encoder_out)
        if self.mode == 'test':
            self.encoder_outputs.append(encoder_out) #encoded vector 추적 가능.
        return decoder_out

epochs = 10
train_batch_size, val_batch_size = 10,2000
lr = 0.001

loss_list = []

train_loader, validation_loader = get_dataloader(train_batch_size, val_batch_size)

model = MNIST_AutoEncoder().to(device)
criterion = nn.MSELoss()
optimizer = optim.Adam(model.parameters(), lr = lr)

for epoch in range(epochs):
    print("epoch : ", epoch)
    for step, (img, label) in enumerate(train_loader):
        img, label = img.view(-1, 28*28).to(device), label.to(device)

        generated_img = model(img)

        optimizer.zero_grad()
        loss = criterion(generated_img, img)
        loss.backward()
        optimizer.step()

#%%
print(model.state_dict().keys())
trained_dict = model.state_dict()
from collections import OrderedDict

enc_state_dict = OrderedDict()
dec_state_dict = OrderedDict()

for k,v in trained_dict.items():
    if k.startswith('encoder'):
        enc_state_dict[k] = v

for k,v in trained_dict.items():
    if k.startswith('decoder'):
        dec_state_dict[k] = v

        #쓰다 놓침

#----------