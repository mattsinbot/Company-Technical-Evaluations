import numpy as np

a = np.arange(0, 3)
np.random.shuffle(a)
print(a)

d = np.array([[1, 5, 6], [8, 6, 7], [6, 3, 1], [0, 1, 2], [5, 4, 5]])
d = d.T
print(d[a])
