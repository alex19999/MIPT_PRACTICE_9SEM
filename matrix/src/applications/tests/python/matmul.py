import numpy as np
m1 = np.matrix([i for i in range(35)])
m1 = m1.reshape((5, 7))
m2 = np.matrix([i for i in range(63)])
m2 = m2.reshape((7, 9))

print("Initial matrix 1:", m1)
print("Initial matrix 2:", m2)
print("Result (m1.matmul(m2)):", np.matmul(m1, m2))