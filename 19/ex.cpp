#include <iostream>
#include <iomanip>
#include <fstream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_spline.h>

using namespace std;

int main()
{
    int i;
    int SIZE = 0;
    string linia;

    // Zliczanie lini w pliku
    fstream wyniki;
    wyniki.open("dane.txt", ios::in);
    while (getline(wyniki, linia))
        SIZE++;
    wyniki.close();

    double x[SIZE], y[SIZE];
    wyniki.open("dane.txt", ios::in);
    for (i = 0; i < SIZE; i++)
    {
        wyniki >> x[i] >> y[i];
    }
    for (int i = 0; i < SIZE; i++)
    {
        cout << x[i] << " " << y[i] << endl;
    }
    wyniki.close();

    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    gsl_spline *spline = gsl_spline_alloc(gsl_interp_cspline, SIZE);

    gsl_spline_init(spline, x, y, SIZE);
    cout << SIZE;
    double xi, yi;
    wyniki.open("splajn_kubiczny.dat", ios::out | ios::trunc);
    wyniki.precision(9);
    for (xi = x[0]; xi < x[SIZE - 1]; xi += 0.0001)
    {
        yi = gsl_spline_eval(spline, xi, acc);
        wyniki << xi << "       " << yi << endl;
    }
    wyniki.close();

    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);

    return 0;
}
