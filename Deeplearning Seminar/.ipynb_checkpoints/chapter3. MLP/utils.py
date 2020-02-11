import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import torch

def dataset_generator():
    n_train_point = 5000
    x_train_data = np.random.uniform(low=-2, high=2, size=(n_train_point, 2))
    y_train_data = np.zeros(shape=(n_train_point))

    n_test_point = 2000
    x_test_data = np.random.uniform(low=-2, high=2, size=(n_test_point, 2))
    y_test_data = np.zeros(shape=(n_test_point))

    for data_idx in range(n_train_point):
        if x_train_data[data_idx, 1] >= 0.2 * x_train_data[data_idx, 0] - 1 and x_train_data[
            data_idx, 0] <= -1 + 0.1 * np.random.normal(0, 1, 1):
            y_train_data[data_idx] = 1.
        if x_train_data[data_idx, 1] <= -0.2 * x_train_data[data_idx, 0] + 1 and x_train_data[
            data_idx, 0] >= 1 + 0.1 * np.random.normal(0, 1, 1):
            y_train_data[data_idx] = 1.
        if np.power(x_train_data[data_idx, 0], 2) + np.power(x_train_data[data_idx, 1],
                                                             2) <= 0.25 + 0.1 * np.random.normal(0, 1, 1):
            y_train_data[data_idx] = 1.

    for data_idx in range(n_test_point):
        if x_test_data[data_idx, 1] >= 0.2 * x_test_data[data_idx, 0] - 1 and x_test_data[
            data_idx, 0] <= -1 + 0.1 * np.random.normal(0, 1, 1):
            y_test_data[data_idx] = 1.
        if x_test_data[data_idx, 1] <= -0.2 * x_test_data[data_idx, 0] + 1 and x_test_data[
            data_idx, 0] >= 1 + 0.1 * np.random.normal(0, 1, 1):
            y_test_data[data_idx] = 1.
        if np.power(x_test_data[data_idx, 0], 2) + np.power(x_test_data[data_idx, 1],
                                                            2) <= 0.25 + 0.1 * np.random.normal(0, 1, 1):
            y_test_data[data_idx] = 1.

    return x_train_data, y_train_data, x_test_data, y_test_data


def tester(x_train_data, y_train_data, model, trained_dict):
    if torch.cuda.is_available():
        device = torch.device('cuda')
    else:
        device = torch.device('cpu')

    x_train_data, y_train_data = x_train_data.cpu().numpy(), y_train_data.cpu().numpy().reshape(-1)
    cmap = cm.get_cmap('bwr_r', 2)

    model.load_state_dict(trained_dict)

    fig, ax2 = plt.subplots(figsize=(15, 15))
    ax2.scatter(x_train_data[:, 0], x_train_data[:, 1], marker='o', color=cmap(y_train_data), alpha=0.4)
    test_x1 = np.linspace(-2, 2, 500)
    test_x2 = np.linspace(-2, 2, 600)
    X1, X2 = np.meshgrid(test_x1, test_x2)

    test_X = np.dstack((X1, X2)).reshape(-1, 2)
    test_result = model(torch.tensor(test_X, dtype=torch.float))
    test_result = test_result.view(600, 500).detach().cpu().numpy()
    ax2.pcolor(X1, X2, test_result, cmap='bwr_r', alpha=0.2)
    ax2.axis('off')
    fig.savefig('./decision_boundary.png')