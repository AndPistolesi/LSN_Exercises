
#!/usr/bin/env python

import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow import keras

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation
from tensorflow.keras import backend as K
from tensorflow.keras.utils import get_custom_objects

import numpy as np

# target parameters of f(x) = m*x + b
m = 2 # slope
b = 1 # intersect
input = open("input.dat", "r")
sigma = float(input.readline()) #data noise
Ne = int(input.readline()) #Number of epochs
Nt = int(input.readline()) #Number of train data
input.close()

# generate training inputs
np.random.seed(0)
x_train = np.random.uniform(-1, 1, Nt)
x_valid = np.random.uniform(-1, 1, int(Nt/10))
x_valid.sort()
y_target = m * x_valid + b # ideal (target) linear function

y_train = np.random.normal(m * x_train + b, sigma) # actual measures from which we want to guess regression parameters
y_valid = np.random.normal(m * x_valid + b, sigma)

# compose the NN model


model = tf.keras.Sequential()
model.add(Dense(1, input_shape=(1,)))

# compile the model choosing optimizer, loss and metrics objects
model.compile(optimizer='sgd', loss='mse', metrics=['mse'])

# get a summary of our composed model
model.summary()

# fit the model using training dataset
# over 10 epochs of 32 batch size each
# report training progress against validation data
history = model.fit(x=x_train, y=y_train, 
          batch_size=32, epochs=Ne,
          shuffle=True, # a good idea is to shuffle input before at each epoch
          validation_data=(x_valid, y_valid))




# evaluate model
score = model.evaluate(x_valid, y_valid, batch_size=32, verbose=1)

# print performance
print()
print('Test loss:', score[0])
print('Test accuracy:', score[1])

# evaluate model with the exact curve
score = model.evaluate(x_valid, y_target, batch_size=32, verbose=1)

# print performance
print()
print('Test loss:', score[0])
print('Test accuracy:', score[1])


# return weights and biases
model.get_weights()

out = open("NN1.out", "a")

out.write(str(history.history['loss'][len(history.history['loss']) - 1 ]))
out.write("\t")
out.write(str(history.history['val_loss'][len(history.history['val_loss']) - 1]))
out.write("\n")

out.close()
