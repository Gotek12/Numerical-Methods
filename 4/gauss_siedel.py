# tworzenie macierzy rzadkiej
# https://austingwalters.com/gauss-seidel-method/
# https://cmdlinetips.com/2018/03/sparse-matrices-in-python-with-scipy/
import pylab
import numpy as np
from scipy.sparse import csr_matrix, tril
from scipy.sparse.linalg import inv

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
c = 0
# gauss_seidel


def gauss_seidel(A, e, x, it, c):
    L = tril(A)
    U = A - L
    # print(L.toarray())
    for i in range(it):
        c += 1
        x = inv(L).dot(e - U.dot(x))

    print(c)
    return x


wynik = gauss_seidel(A, e, x, it, c)
# for x in range(0, N):
#print(np.around(wynik[x, 0], decimals=7))
# print(wynik[:, 0])

k = [0] * N
file = open("wynik.txt", "w")
for x in range(0, N):
    if(x < N):
        k[x] = wynik[x, 0]
    file.write(str(np.around(wynik[x, 0], decimals=7)))
    file.write("\n")
file.close()

# sprobowac uzyc metody sparse.spdiags
# https://www.scipy-lectures.org/advanced/scipy_sparse/solvers.html
# https://github.com/nuhferjc/gauss-seidel/blob/master/gaussseidel.py
# https://pl.wikipedia.org/wiki/Metoda_Gaussa-Seidla

# liczymy ||x - (x-1)||
# for i in range(N, 0, -1):
#   print(i)

b = [0] * (N)
for i in range(N-1, 0, -1):
    print(np.linalg.norm(k[i]-k[i-1]))
    b[i] = np.linalg.norm(k[i]-k[i-1])

pylab.plot(b)
pylab.show()
