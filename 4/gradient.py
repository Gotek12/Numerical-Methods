# metoda gradientow-sprzerzonych
import numpy as np
from scipy.sparse import csr_matrix, tril
from scipy.sparse.linalg import inv, cg

N = 128  # wielkosc macierzy
A = csr_matrix((N, N), dtype=int).toarray()  # tworze miejsce na macierz rzadka
e = [0] * N
x = [0] * N  # wektor wynikowy
it = 60  # ilosc iteracji

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

# gradienty-sprzezone
a = cg(A, e, x0=None, tol=1e-09, maxiter=60, M=None, callback=None, atol=None)
print(a[0][1])

file = open("wynik2.txt", "w")
for x in range(0, N):
    file.write(str(np.around(a[0][x], decimals=7)))
    file.write("\n")
file.close()
