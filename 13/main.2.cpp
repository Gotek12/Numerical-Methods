#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <gsl/gsl_linalg.h>

using namespace std;
const int N = 65; //wezly
const int D = 3;  //parametr

/*
    //przydatne linki
    -http://th-www.if.uj.edu.pl/zfs/gora/metnum12/wyklad07.pdf
    -https://www.inf.usi.ch/faculty/hormann/papers/Floater.2007.BRI.pdf
*/

//klasa realizująca algorytm Floatera i Hormanna
class FH
{

  public:
    //nasza funkcja
    double f(double x)
    {
        return 1 / (1 + 5 * pow(x, 2));
    }

    void algFH(double xi[], double yi[])
    {
        //zapisanie do odpowiednich wektorow
        gsl_vector *x = gsl_vector_alloc(N);
        gsl_vector *y = gsl_vector_alloc(N);
        gsl_vector_view tmp_x = gsl_vector_view_array(xi, N);
        gsl_vector_view tmp_y = gsl_vector_view_array(yi, N);
        gsl_vector_memcpy(x, &tmp_x.vector);
        gsl_vector_memcpy(y, &tmp_y.vector);

        ofstream myfile;
        myfile.open("wynik.txt");
        for (double i = -1.0; i <= 1.0; i += 0.001)
        {
            printf("%g %g\n", i, rx(x, y, i));
            myfile << fixed << setprecision(5) << i << " " << rx(x, y, i) << endl;
        }
        myfile.close();

        gsl_vector_free(x);
        gsl_vector_free(y);
    }

  private:
    //wk gdzie i należy do jest miedzy k-d<=i<=k
    //a I = {0,1,2,...,n-d}

    //wzor ze strony
    //https://www.inf.usi.ch/faculty/hormann/papers/Floater.2007.BRI.pdf
    double wk(int k)
    {
        double wynik = 0.0;

        for (int i = 0; i < N - D; i++)
        {
            if ((k - D <= i) & (i <= k))
            {
                wynik += dmumianNewtona(D, k - i);
            }
        }

        return pow(-1, k - D) * wynik;
    }

    //funkcja jako gładka mieszanka wielomianow interpolayjnych
    double rx(gsl_vector *xk, gsl_vector *fk, double x)
    {
        //liczymy licznik i mianownik
        double l = 0.0, m = 0.0;
        for (int i = 0; i < N; i++)
        {
            l += (wk(i) / (x - gsl_vector_get(xk, i))) * gsl_vector_get(fk, i);
            m += wk(i) / (x - gsl_vector_get(xk, i));
        }

        return l / m;
    }

    //dwumian newtona wykorzystywany w wk
    int dmumianNewtona(int n, int k)
    {
        if (k == 0 || k == n)
            return 1;

        return dmumianNewtona(n - 1, k - 1) + dmumianNewtona(n - 1, k);
    }
};
//algorytm w postaci barycentrycznej
int main()
{
    FH fh;

    double xi[N], yi[N];
    printf("#m=0,S=2\n");
    //wyliczenie y na podstawie funkcji
    for (int i = 0; i < N; i++)
    {
        xi[i] = -1.0 + (i / 32.0);
        yi[i] = fh.f(xi[i]);
        printf("%g %g\n", xi[i], yi[i]);
    }
    printf("#m=1,S=0\n");
    fh.algFH(xi, yi);

    return 0;
}
