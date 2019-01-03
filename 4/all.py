# imporujemy wszystkie potrzebne biblioteki
import pylab
import numpy as np

from math import sqrt
from numpy import linalg as LA

# pozwalają obsłużyć macierz rzadką
from scipy.sparse import csr_matrix, tril
from scipy.sparse.linalg import inv

tol = 1.0e-9  # tolerancja
N = 128  # wielkosc macierzy

# https://docs.scipy.org/doc/scipy/reference/generated/scipy.sparse.csr_matrix.html
A = csr_matrix((N, N), dtype=int).toarray()  # tworze miejsce na macierz rzadką
e = [0] * N
x = [0] * N  # wektor wynikowy
it = 60  # ilosc iteracji

# wypelnienie wektora z samymi 1
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

c = 0  # zmienna używana do liczenia złożoności


# funkcja licząca Gaussa-Seidela
def gauss_seidel(A, e, x, it, c, tol):
    D = tril(A)  # macierz dolnotrójkątna
    G = A - D  # macierz górnotrójkątna

    # nasza iteracja
    for i in range(it):
        c += 1
        x0 = x  # ustawiam, że wektor od której zaczniemy szukać będzie się równać wektorowi x
        x = inv(D).dot(e - G.dot(x))

        # sprawdzamy tolerancję
        tmp = abs((LA.norm(x) - LA.norm(x0))/LA.norm(x))*100
        if (tmp <= tol):
            break

    print("Złożoność GS: ")
    print(c)
    return x


wynik = gauss_seidel(A, e, x, it, c, tol)
k = [0] * N  # wektor przechowywujący wynik metody Gaussa-Seidela

# wynik zapisuje do pliku
file = open("wynik.txt", "w")
for x in range(0, N):
    if(x < N):
        k[x] = wynik[x, 0]  # przypisuje dokladny wynik obliczeń metodą Gaussa-Seidela
    # ustawiam dokładnosc zapisu do 7-cyfr
    file.write(str(np.around(wynik[x, 0], decimals=7)))
    file.write("\n")
file.close()


# funkcja licząca metodą gradientów sprzęzonych
def grad(A, e, tol, x, c):
    # warunki początkowe
    r = A.dot(x) - e
    norma = r.dot(r)  # norma r początkowego
    p = - r
    for i in range(it):  # iteracja
        c += 1
        a = norma / p.dot(A.dot(p))
        x += a * p
        r += a * A.dot(p)

        # sprawdzamy tolerancję
        b = r.dot(r) / norma
        norma = r.dot(r)
        if r.dot(r) < tol:  # sprawdzam czy miesci się w tolerancji
            break
        p = b * p - r

    print("zlozonosc gradientow sp: ")
    print(c)
    return x


xx = np.ones(N)
a = grad(A, e, tol, xx, c)  # wynik liczenia metodą gradientów sprzężonych

# zapis metody gradientów sprzężonych do pliku
file = open("wynik2.txt", "w")
for x in range(0, N):
    file.write(str(np.around(a[x], decimals=7)))
    file.write("\n")
file.close()

# macierze służące do przechowywania danych w celu przedstawienia graficznie zbierzności metod
b = [0] * (N)
bb = [0] * (N)

# iteruje od N doc 0 i liczę normę x(k) - x(k-1) dla obu metod
for i in range(N-1, 0, -1):
    b[i] = np.linalg.norm(a[i]-a[i-1])
    bb[i] = np.linalg.norm(k[i]-k[i-1])


# algorytm Choleskiego
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

    print("zlozonosc Choleskiego: ")
    print(c)
    # daje ona nam macierz wynikową gdzie wyniki są na głównej diagonali
    return L


cholesky(A, c)

# dla tolerancji 1.0e-2 wykresy pokrywają się
#pylab.legend(("red - GS", "blue - gradient"), loc='upper right')
pylab.plot(b, color="r", label="metoda gradientów sp")
pylab.plot(bb, color="b", label="Gauss-Seidel")
pylab.legend()
pylab.show()
