# metoda gradientow-sprzerzonych
import numpy as np
from scipy.sparse import csr_matrix, tril
from scipy.sparse.linalg import inv, cg, norm

N = 128  # wielkosc macierzy
A = csr_matrix((N, N), dtype=int).toarray()  # tworze miejsce na macierz rzadka
e = [0] * N
# x = [0] * N  # wektor wynikowy
it = 60  # ilosc iteracji
tol = 1.0e-9

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


def conjugate_grad(A, b, x=None):
    if not x:
        x = np.ones(N)
    r = np.dot(A, x) - b
    p = - r
    r_k_norm = np.dot(r, r)
    for i in range(2*N):
        Ap = np.dot(A, p)
        alpha = r_k_norm / np.dot(p, Ap)
        x += alpha * p
        r += alpha * Ap
        r_kplus1_norm = np.dot(r, r)
        beta = r_kplus1_norm / r_k_norm
        r_k_norm = r_kplus1_norm
        if r_kplus1_norm < 1e-5:
            break
        p = beta * p - r
    return x


k = conjugate_grad(A, e)
print(k)
