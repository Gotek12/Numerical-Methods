#include <iostream>
#include <iomanip>
#include <fstream>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_spline.h>

using namespace std;
const int N = 65; //wezly
double f(double x);
void splain();

int main()
{
    splain();
    return 0;
}

double f(double x)
{
    return 1 / (1 + 5 * pow(x, 2));
}

void splain()
{
    double xi[N], yi[N];

    printf("#m=0,S=17\n");

    for (int i = 0; i < N; i++)
    {
        xi[i] = -1.0 + (i / 32.0);
        yi[i] = f(xi[i]);
        printf("%g %g\n", xi[i], yi[i]);
    }
    printf("#m=1,S=0\n");

    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    gsl_spline *spline = gsl_spline_alloc(gsl_interp_cspline, N);
    gsl_spline_init(spline, xi, yi, N);

    double j;

    //zapis splajnu do pliku
    ofstream myfile;
    myfile.open("wynik.txt");
    for (double i = xi[0]; i < xi[N - 1]; i += 0.01)
    {
        j = gsl_spline_eval(spline, i, acc);
        printf("%g %g\n", i, j);
        myfile << fixed << setprecision(5) << i << " " << j << endl;
    }
    myfile.close();

    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
}