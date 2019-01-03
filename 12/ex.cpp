#include <iostream>
#include <iomanip>
#include <fstream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_sf.h>

using namespace std;

const int N = 65;   //liczba wezlow
const double h = 1.0/32.0;
const double mian = h*h;
const double wsp = 6*32*32;

double funkcja(double x){
    return 1/(1 + (5*x*x));
}

int main(){
    int i, j;
    double wezel = -1.0;
    double xi, yi;
    cout << setprecision(16) << fixed;

    gsl_vector * war_fun = gsl_vector_alloc(N);
    fstream wyniki;
    wyniki.open("warwwezlach.dat", ios::out | ios::trunc);
    wyniki.precision(9);
    for(i = 0; i < N; i++){
        gsl_vector_set(war_fun, i, funkcja(wezel + (i/32.0)));
        wyniki << wezel + (i/32.0) << "     " << funkcja(wezel + (i/32.0)) << endl;
    }
    wyniki.close();

    gsl_vector * b = gsl_vector_alloc(N-2);
    gsl_vector * diag = gsl_vector_alloc(N-2);
    gsl_vector * e = gsl_vector_alloc(N-3);
    gsl_vector * x_pom = gsl_vector_alloc(N-2);

    gsl_vector_set_all(diag, 4.0);
    gsl_vector_set_all(e, 1.0);

    for(i = 1; i < N-1; i++)
        gsl_vector_set(b, i-1, wsp*( gsl_vector_get(war_fun, i-1) - 2*gsl_vector_get(war_fun, i) + gsl_vector_get(war_fun, i+1) ) );

    gsl_linalg_solve_symm_tridiag(diag, e, b, x_pom);

    /**
    * Czyszczenie
    */
    gsl_vector_free(b);
    gsl_vector_free(diag);
    gsl_vector_free(e);

    /**
    * Obliczanie ksi
    */
    /*gsl_vector * ksi = gsl_vector_alloc(N);
    gsl_vector_set(ksi, 0, 0.0);
    for(i = 1; i < N-1; i++)
        gsl_vector_set(ksi, i, gsl_vector_get(x_pom, i-1));
    gsl_vector_free(x_pom);
    gsl_vector_set(ksi, N-1, 0.0);*/

    gsl_interp_accel * acc = gsl_interp_accel_alloc();
    gsl_spline * spline = gsl_spline_alloc(gsl_interp_cspline, N);

    double x[N], y[N];
    for(i = 0; i < N; i++){
        x[i] = wezel + (i/32.0);
        y[i] = funkcja(wezel + (i/32.0));
    }

    gsl_spline_init(spline, x, y, N);

    wyniki.open("wynikiiter.dat", ios::out | ios::trunc);
    wyniki.precision(9);
    for(xi = x[0]; xi < x[N-1]; xi += 0.0001){
        yi = gsl_spline_eval(spline, xi, acc);
        wyniki << xi << "       " << yi << endl;
    }
    wyniki.close();

    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);

    return 0;
}
