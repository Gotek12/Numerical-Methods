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
    double lag(double xi[], double yi[], double T)
    {
        double sum = 0.0;
        double tmp = 0.0;
        for (int i = 0; i < N; i++)
        {
            tmp = xi[i];
            for (int j = 0; j < N; j++)
            {
                /* To avoid division by zero. */
                if (j != i)
                    tmp = tmp * (T - xi[j]) / (xi[i] - xi[j]);
            }
            sum += tmp;
        }
        return sum;
    }
};

int main()
{
    Lagrange lagrange;
    double xi[N], yi[N];

    printf("#m=0,S=5\n");

    for (int i = 0; i < N; i++)
    {
        xi[i] = -1.0 + (i / 32.0);
        yi[i] = lagrange.f(xi[i]);
        printf("%g %g\n", xi[i], yi[i]);
    }
    printf("#m=1,S=0\n");

    for (double xx = -1.0; xx <= 1.0; xx += 0.01)
    {
        //lagrange.lag(xi, yi, xx);
        printf("%g %g\n", xx, lagrange.lag(xi, yi, xx));
    }

    return 0;
}
