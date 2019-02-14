#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double f(double x)
{
    return 1 / (1 + 5 * x * x);
}
int main()
{
    int size = 65;
    double tab[size];

    for (int i = 0; i < size; i++)
    {
        tab[i] = -1.0 + (i / 32.0);
    }

    size_t const size_x = 101;
    double L, x[size_x], tmp;
    double p;
    x[0] = -1;
    for (int k = 1; k < 101; k++)
    {
        tmp = (0.1 + x[k - 1]);
        x[k] = tmp;
    }
    for (int k = 0; k < 101; k++)
    {
        L = 1;
        for (int j = 0; j < size; j++)
        {
            L = 1;
            for (int i = 0; i < size; i++)
            {
                if (i != j)
                {
                    L *= (x[k] - tab[i]) / (tab[j] - tab[i]);
                }
            }
            p += L * f(tab[j]);
        }
        cout << setprecision(4) << fixed << p << endl;
        p = 0;
    }

    return 0;
}

//https://magnum34.com/interpolacja-wielomianowa-lagrange/