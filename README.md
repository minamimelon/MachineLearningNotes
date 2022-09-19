# MachineLearningNotes
My notes on machine learning

# Files

## MultivariateLinearRegression

### MultivariateLinearRegressionUsingGradientDescent.ipynb
### MultivariateLinearRegressionUsingNormalEquation.ipynb
### TorchAutogardLinearRegression.ipynb

Instead of calculating derivatives myself, we use the torch.autograd to compute gradients.

## kNN

### kNNbyKDTree.cpp 

Implemented k-nearest neighbors algorithm by C++.

## NeuralNetworks

### BPNetworks.ipynb

Implemented backpropagation algorithm. Trained a 2-layer neural networks.

Its model file is trained.npz.

### MultiHiddenLayerNN.ipynb

Implemented a multilayer neural networks, of which activation functions are all sigmoid.

Using PyTorch only for matrix multiplication.

Verified that sigmoid activation function can cause vanishing gradient.

### MultiHiddenLayerNNReLU.ipynb

Replaced sigmoid funtions in MultiHiddenLayerNN.ipynb with ReLU except the last layer. Vanishing gradient solved.

Its model file is model_ReLU94.pth,whose test accuracy is 94%.

## PyTorchNN

### torchNN.ipynb & torchNNretrain.ipynb

Updated from BPNetworks.ipynb.

Using PyTorch to do matrix multiplication to speed up.

Its model file is trained_model_tensor.pt and trained_model_tensor2.pt

## NaiveBayes

### NaiveBayesClassifier.ipynb

## EnsembleLearning

### WeightedVote.ipynb

## Paddle

### image_recognition_paddle.ipynb

### text_classification_paddle.ipynb

Its model file is model_final.pdparams.

# References

[THE MNIST DATABASE of handwritten digits](http://yann.lecun.com/exdb/mnist/)