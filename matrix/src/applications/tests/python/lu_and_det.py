import numpy as np
from scipy.linalg import lu

# Simple
m = np.matrix([2, -1, -2, -4, 6, 3, -4, -2, 8])
m = m.reshape((3, 3))

print("Initial matrix:", m)
p, l, u = lu(m)
print("L", l)
print("U", u)
print("Determinant m:", np.linalg.det(m))
print("Determinant PLU:", np.linalg.det(p) * np.linalg.det(l) * np.linalg.det(u))

# Harder
import numpy as np
from scipy.linalg import lu
np.random.seed(0)
m = np.matrix([np.random.uniform(0.0, 1.0) for i in range(121)])
m = m.reshape((11,11))

print("Initial matrix:", m)
p, l, u = lu(m)
print("L", l)
print("U", u)
print("Determinant m:", np.linalg.det(m))
print("Determinant PLU:", np.linalg.det(p) * np.linalg.det(l) * np.linalg.det(u))