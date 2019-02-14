#include <iostream>
#include <iomanip>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>

//interpolacja wielomianowa - lagrangea
using namespace std;
const int N = 65; //wezly

class Lagrange
{

  public:
    double f(double x)
    {
        return 1 / (1 + 5 * pow(x, 2));
    }

    //metoda licząca lagrangea
    void lag(double xi[], double yi[])
    {

        ///pozwala nam generować wartosci
        double yy;
        int i;
        for (double xx = -1.0; xx <= 1.0; xx += 0.1)
        {

            yy = 1;
            i = 0;
            for (int j = 0; j < N; j++)
            {
                if (j != i)
                {
                    yy *= (xx - xi[j]) / (xi[i] - xi[j]);
                }
            }
            yy += yy * yi[i];
            printf("%g %g\n", xx, yy);
            i++;
        }
    }
};

int main()
{
    Lagrange lagrange;
    double xi[N], yi[N];

    printf("#m=0,S=2\n");

    for (int i = 0; i < N; i++)
    {
        xi[i] = -1.0 + (i / 32.0);
        yi[i] = lagrange.f(xi[i]);
        //printf("%g %g\n", xi[i], yi[i]);
    }
    printf("#m=1,S=0\n");

    lagrange.lag(xi, yi);

    return 0;
}
