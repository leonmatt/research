'''
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
'''

# Import required modules
import numpy as np

from sklearn.linear_model import LogisticRegression
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

# Set nummpy random seed
seed = 42
np.random.seed(seed)

# Generate the data
X, Y = make_classification(n_samples=10000, n_features=10, n_informative=7, random_state=seed)

# Split the data so we can fit and test
X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size=0.2, random_state=seed)

# Initialize and fit the model to our generated data
LRModel = LogisticRegression()
LRModel.fit(X_train, y_train)

# Test the model
y_prediction = LRModel.predict(X_test)

# Get the accuracy
accuracy_score = accuracy_score(y_test, y_prediction)

print(f"The Model's Accuracy is: {accuracy_score * 100:.2f}%")
