import numpy as np
from scipy.linalg import solve


def gauss(A, b, x, n):

    L = np.tril(A)
    U = A - L
    for i in range(n):
        x = np.dot(np.linalg.inv(L), b - np.dot(U, x))
        # print(str(i).zfill(3)),
        # print(x)
    return x


A = np.array([[4.0, 1.0, 0.0], [1.0, 4.0, 1.0], [0.0, 1.0, 4.0]])
b = [1.0, 1.0, 1.0]
x = [1, 1, 1]

n = 60  # ilosc iteracji

a = gauss(A, b, x, n)
b = solve(A, b)
print(a)
# print(b)
