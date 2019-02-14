#include <iostream>
#include <iomanip>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>

/*
//przydatne źródła
-wykłady
-https://www.gnu.org/software/gsl/doc/html/interp.html
-http://th-www.if.uj.edu.pl/zfs/gora/metnum17/wyklad07.pdf
-http://www.algorytm.org/procedury-numeryczne/interpolacja-lagrange-a.html
*/

//interpolacja wielomianowa - lagrangea
using namespace std;
const int N = 65; //wezly
double f(double x);
void lagrange(double xi[], double yi[]);
gsl_vector *lu(gsl_vector *x, gsl_vector *y, gsl_vector *a, gsl_permutation *permutation, gsl_matrix *countMat);

int main()
{
    double xi[N], yi[N];

    printf("#m=0,S=2\n");

    for (int i = 0; i < N; i++)
    {
        xi[i] = -1.0 + (i / 32.0);
        yi[i] = f(xi[i]);
        printf("%g %g\n", xi[i], yi[i]);
    }
    printf("#m=1,S=0\n");

    lagrange(xi, yi);

    return 0;
}

//funkcja
double f(double x)
{
    return 1 / (1 + 5 * pow(x, 2));
}

void lagrange(double xi[], double yi[])
{
    //ogolnie wielomian a(n)x^(n)+a(n-1)x^(n-1)+... = y

    gsl_vector *a = gsl_vector_alloc(N);                     //vector na wspolczynniki
    gsl_permutation *permutation = gsl_permutation_alloc(N); //wektor permutacji do dekompozycji LU
    //macierz pozwalająca umieścić odpowiednie wartości typu ax^n
    gsl_matrix *countMat = gsl_matrix_alloc(N, N);

    //umieszczanie danych w wektorach
    gsl_vector *x = gsl_vector_alloc(N);
    gsl_vector *y = gsl_vector_alloc(N);
    gsl_vector_view tmp_x = gsl_vector_view_array(xi, N);
    gsl_vector_view tmp_y = gsl_vector_view_array(yi, N);
    gsl_vector_memcpy(x, &tmp_x.vector);
    gsl_vector_memcpy(y, &tmp_y.vector);

    double yy;
    for (double xx = -1.0; xx <= 1.0; xx += 0.001)
    {
        yy = 0;
        for (int i = 0; i < N; i++)
        {
            yy += gsl_vector_get(lu(x, y, a, permutation, countMat), i) * pow(xx, N - 1 - i);
        }
        printf("%g %g\n", xx, yy);
    }

    //postac wielomianu interpolacyjnego
    for (int i = 0; i < N; i++)
    {
        cout << setprecision(4) << fixed << gsl_vector_get(lu(x, y, a, permutation, countMat), i);
        cout << "x^" << N - 1 - i;
        if (i != N - 1)
        {
            cout << " + ";
        }
    }
    cout << endl;
    //zwalnianie pamięci
    gsl_vector_free(x);
    gsl_vector_free(y);
    gsl_matrix_free(countMat);
    gsl_vector_free(a);
}

//funkcja przelicza wektor zawierający współczynniki
gsl_vector *lu(gsl_vector *x, gsl_vector *y, gsl_vector *a, gsl_permutation *permutation, gsl_matrix *countMat)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            gsl_matrix_set(countMat, i, j, pow(gsl_vector_get(x, i), N - 1 - j));
        }
    }

    //rozwiązujemy macierz stosując dekompozycje LU
    int tmp;
    gsl_linalg_LU_decomp(countMat, permutation, &tmp);
    gsl_linalg_LU_solve(countMat, permutation, y, a);

    return a;
}