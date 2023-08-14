'''
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
'''

# Import required modules
import numpy as np

from sklearn.tree import DecisionTreeRegressor
from sklearn.ensemble import AdaBoostRegressor
from sklearn.datasets import make_regression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
 
# Set nummpy random seed
seed = 42
np.random.seed(seed)

# Generate the data
X, Y = make_regression(n_samples=10000, n_features=3, random_state=seed)

# Split the data so we can fit and test
X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size=0.2, random_state=seed)

# Initialize and fit the model to our generated data
# Model that ensembles a bunch of decision trees using adaboost
BaseDTModel = DecisionTreeRegressor(max_depth=5)
adabooster = AdaBoostRegressor(BaseDTModel, n_estimators=500, random_state=seed)
adabooster.fit(X_train, y_train)

# Test the model
y_prediction = adabooster.predict(X_test)

# Get the accuracy
mse = mean_squared_error(y_test, y_prediction)

print(f"The Model's Mean Squared Error is: {mse}")
