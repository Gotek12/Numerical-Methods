# metoda gradientow-sprzerzonych
import pylab
import numpy as np
from scipy.sparse import csr_matrix, tril
from scipy.sparse.linalg import inv, cg, norm
count = 0
N = 128  # wielkosc macierzy
A = csr_matrix((N, N), dtype=int).toarray()  # tworze miejsce na macierz rzadka
e = [0] * N
it = 60  # ilosc iteracji
tol = 1.0e-9
c = 0
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


def grad(A, e, tol, x, c):
    r = A.dot(x) - e
    p = - r
    rNorm = r.dot(r)
    for i in range(it):
        c += 1
        Ap = A.dot(p)
        alpha = rNorm / p.dot(Ap)
        x += alpha * p
        r += alpha * Ap
        rNorm2 = r.dot(r)
        beta = rNorm2 / rNorm
        rNorm = rNorm2
        if rNorm2 < tol:
            break
        p = beta * p - r

    print(c)
    return x


# ustaiamy wektor poczatkowy
x = np.ones(N)

a = grad(A, e, tol, x, c)
# print(a)
k = [0] * N
file = open("wynikgrad2.txt", "w")
for x in range(0, N):
    file.write(str(np.around(a[x], decimals=7)))
    file.write("\n")
file.close()

b = [0] * (N)
for i in range(N-1, 0, -1):
    # print(np.linalg.norm(a[i]-a[i-1]))
    b[i] = np.linalg.norm(a[i]-a[i-1])
pylab.plot(b, color="r")
pylab.show()
