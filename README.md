**WIP**: Partial implementation/initial work towards implementing Andrej Karpathy's 2D tensor for Eurekalabs.ai / LLM101n.

_Currently implemented_:
- tensor1d.cu contains the standard 1d tensor structure but with optional CUDA acceleration. Currently CUDA devices are auto-detected and utilized if available.
- ParseTest3.c contains some initial thoughts on how to structure the 2D tensor, particularly by way of parsing the input in a more elegant manner. Actual memory structure still needs to be implemented. Thoughts though are towards using a 1D array structure (essentially Karpathy's 'Tensor' structure (i.e a 1D array), but with strides for multidimensional locations as he has suggested).

Link to original repo: https://github.com/EurekaLabsAI/tensor
