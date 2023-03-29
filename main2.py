import numpy as np

def perceptron_learn(input_data, output_data, learning_rate, num_epochs):
    num_inputs = input_data.shape[1]
    weights = np.zeros(num_inputs)
    bias = 0.0
    for epoch in range(num_epochs):
        for i in range(input_data.shape[0]):
            input_vector = input_data[i]
            predicted_output = np.dot(input_vector, weights) + bias
            if predicted_output > 0:
                predicted_output = 1
            else:
                predicted_output = 0
            error = output_data[i] - predicted_output
            weights += learning_rate * error * input_vector
            bias += learning_rate * error
    return weights, bias

# Funkcja AND
input_data = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
output_data = np.array([0, 0, 0, 1])
learning_rate = 0.1
num_epochs = 100

weights_AND, bias_AND = perceptron_learn(input_data, output_data, learning_rate, num_epochs)

# Funkcja NOT
input_data = np.array([[0], [1]])
output_data = np.array([1, 0])
learning_rate = 0.1
num_epochs = 100

weights_NOT, bias_NOT = perceptron_learn(input_data, output_data, learning_rate, num_epochs)

print("Wagi perceptronu dla funkcji AND:", weights_AND)
print("Bias perceptronu dla funkcji AND:", bias_AND)

print("Wagi perceptronu dla funkcji NOT:", weights_NOT)
print("Bias perceptronu dla funkcji NOT:", bias_NOT)

