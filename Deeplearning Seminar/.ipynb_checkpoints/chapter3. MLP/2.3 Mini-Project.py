##### Check Overfitting for various n_neuron
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import datetime

import torch
import torch.nn as nn
import torch.optim as optim

from utils import dataset_generator, tester

np.random.seed(0)
torch.manual_seed(0)

if torch.cuda.is_available():
    device = torch.device('cuda')
else:
    device = torch.device('cpu')

x_train_data, y_train_data, x_test_data, y_test_data = dataset_generator()


fig, (ax1, ax2) = plt.subplots(1, 2, figsize = (30,15))
cmap = cm.get_cmap('bwr_r', 2)
ax1.grid()
ax2.grid()
ax1.set_title("Train Dataset", fontsize=30)
ax2.set_title("Test Dataset", fontsize= 30)
fig.subplots_adjust(top=0.9, bottom=0.1, left=0.1, right = 0.9,
                    wspace=0.05)
ax1.scatter(x_train_data[:,0], x_train_data[:,1], marker = 'o', color = cmap(y_train_data), alpha = 0.4)
ax2.scatter(x_test_data[:,0], x_test_data[:,1], marker = 'o', color = cmap(y_test_data), alpha = 0.4)
plt.show()


class MLP_Classifier(nn.Module):
    def __init__(self):
        super(MLP_Classifier, self).__init__()
        self.fc1 = nn.Linear(2, 10)
        self.fc2 = nn.Linear(10, 2)
        self.ReLU = nn.ReLU()

    def forward(self, x):
        x = self.ReLU(self.fc1(x))
        x = self.ReLU(self.fc2(x))
        return x


lr = 0.001
epochs = 1000

criterion = nn.BCELoss()
optimizer = torch.optim.SGD(model.parameters(), lr=lr)

loss_list = []

#for neuron_idx in range(len(num_neuron_list)):

#loss_mat.append(loss_list)


trained_dict = model.state_dict()
model = MLP_Classifier().to(device)
tester(x_train_data, y_train_data, model, trained_dict)

for i in range(epochs):