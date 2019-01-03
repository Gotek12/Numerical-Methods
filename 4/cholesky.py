import numpy as np
from scipy.sparse import csr_matrix, tril
from scipy.sparse.linalg import inv
from math import sqrt

N = 128  # wielkosc macierzy
A = csr_matrix((N, N), dtype=int).toarray()  # tworze miejsce na macierz rzadka
e = [0] * N
x = [0] * N  # wektor wynikowy

# wypelnienie macierzy wynikowej
for i in range(0, N):
    e[i] = 1

# wypelnienie macierzy
for x in range(0, N):
    A[x][x] = 4
    j = x + 1
    k = x + 4
    if j < N:
        A[x][j] = 1
        A[j][x] = 1
    if k < N:
        A[x][k] = 1
        A[k][x] = 1

c = 0


def cholesky(A, c):
    L = np.zeros_like(A)
    for x in range(N):
        for y in range(x+1):
            c += 1
            sum = np.dot(L[x, :y], L[y, :y])
            if (x == y):  # jesli diagonala
                L[x, y] = sqrt(max(A[x, x] - sum, 0))
            else:
                L[x, y] = (1.0 / L[y, y]) * (A[x, y] - sum)

    print(c)
    return L


k = cholesky(A, c)
print(k)

# https://www.coursesmojo.com/cholesky-decomposition/
# http://drsfenner.org/blog/2016/02/basic-cholesky-implementation/
# https://www.quantstart.com/articles/Cholesky-Decomposition-in-Python-and-NumPy
