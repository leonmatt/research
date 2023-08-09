'''
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
'''

# Import required modules
import numpy as np

from sklearn.datasets import make_classification
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC
from sklearn.model_selection import train_test_split
from sklearn.metrics import precision_score, recall_score, f1_score, roc_auc_score

# Set nummpy random seed
seed = 42
np.random.seed(seed)

# Generate the data
X, Y = make_classification(n_samples=10000, n_features=10, n_informative=7, random_state=seed)

# Split the data so we can fit and test
X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size=0.2, random_state=seed)

# Scale the data
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Initialize and fit the model to our generated data
# Model that classifies using hyperplanes
SVCModel = SVC(kernel='linear')
SVCModel.fit(X_train, y_train)

# Test the model
y_prediction = SVCModel.predict(X_test)

# Get the accuracy
precision = precision_score(y_test, y_prediction)
print(f"Precision: {precision:.2f}")

recall = recall_score(y_test, y_prediction)
print(f"Recall: {recall:.2f}")

f1 = f1_score(y_test, y_prediction)
print(f"F1 Score: {f1:.2f}")
