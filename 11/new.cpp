#include <iostream>
#include <iomanip>
#include <cmath>

//interpolacja wielomianowa - lagrangea
using namespace std;
const int N = 66; //wezly

class Lagrange
{
    double suma;
    double tmp;

  public:
    double f(double x)
    {
        return 1 / (1 + 5 * pow(x, 2));
    }

    //metoda licząca lagrangea
    double lag(double xi[], double yi[], double xx)
    {
        suma = 0.0;

        for (int i = 0; i < N; i++)
        {
            tmp = yi[i];
            for (int j = 0; j < N; j++)
            {
                if (j != i)
                    tmp = tmp * (xx - xi[j]) / (xi[i] - xi[j]);
            }
            suma += tmp;
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
        printf("%g %g\n", xi[i], yi[i]);
    }
    printf("#m=1,S=0\n");

    for (double xx = -0.9; xx < 1.0; xx += 0.001)
    {
        lagrange.lag(xi, yi, xx);
        printf("%g %g\n", xx, lagrange.lag(xi, yi, xx));
    }
    //cout << lagrange.lag(xi, yi);
    return 0;
}
