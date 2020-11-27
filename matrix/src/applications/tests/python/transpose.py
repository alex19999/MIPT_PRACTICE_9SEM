import numpy as np
matrix = np.matrix([i for i in range(77)])
matrix = matrix.reshape((7, 11))

print("Initial matrix:", matrix)
print("Transposed matrix:", matrix.transpose())