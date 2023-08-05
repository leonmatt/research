'''
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
'''

# Import required modules
import numpy as np

from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

# Set nummpy random seed
seed = 42
np.random.seed(seed)

# Generate the data
X = np.random.rand(10000, 1)
Y = 72 + X * np.random.rand(10000, 1)

# Split the data so we can fit and test
X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size=0.2, random_state=seed)

# Initialize and fit the model to our generated data
LRModel = LinearRegression()
LRModel.fit(X_train, y_train)

# Test the model
y_prediction = LRModel.predict(X_test)

# Get the accuracy
mse = mean_squared_error(y_test, y_prediction)

print(f"The Model's Mean Squared Error is: {mse}")
