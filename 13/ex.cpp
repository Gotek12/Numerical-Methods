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

int silnia(int liczba){
    if(liczba < 2) return 1;
    return liczba*silnia(liczba-1);
}

double dwumian(int n, int k){
    return silnia(n)/(silnia(k)*silnia(n-k));
}

double funkcja(double x){
    return 1/(1 + (5*x*x));
}

double waga_k(int k, int d, int n){
    int i;
    double suma = 0;

    for(i = 0; i < n-d; i++)
        if( (k-d-1 < i) && (i < k+1) ) suma += dwumian(d, k-i);

    return gsl_sf_pow_int(-1, k-d)*suma;
}

double rx(double x, gsl_vector * w_wezla, gsl_vector * f_wezel, int SIZE){
    int k;
    double licznik = 0;
    double mianownik = 0;
    for(k = 0; k < SIZE; k++){
        if( x != gsl_vector_get(w_wezla, k) ) licznik += (waga_k(k, 3, N)/(x - gsl_vector_get(w_wezla, k)))*gsl_vector_get(f_wezel, k);
        if( x != gsl_vector_get(w_wezla, k) ) mianownik += waga_k(k, 3, N)/(x - gsl_vector_get(w_wezla, k));
    }

    return licznik/mianownik;
}

int main(){
    int i;
    double wezel = -1.0;
    double xi, yi;
    cout << setprecision(12) << fixed;

    gsl_vector * war_fun = gsl_vector_alloc(N);
    gsl_vector * wezly = gsl_vector_alloc(N);

    fstream wyniki;
    wyniki.open("warwwezlach.dat", ios::out | ios::trunc);
    wyniki.precision(9);
    for(i = 0; i < N; i++){
        gsl_vector_set(wezly, i, wezel+(i/32.0));
        gsl_vector_set(war_fun, i, funkcja(wezel + (i/32.0)));
        wyniki << gsl_vector_get(wezly, i) << "     " << gsl_vector_get(war_fun, i) << endl;
    }
    wyniki.close();

    double ix;
    wyniki.open("wyniki.dat", ios::out | ios::trunc);
    wyniki.precision(9);
    for(ix = -1; ix < 1.001; ix += 0.001){
        cout << rx(ix, wezly, war_fun, N) << endl;
        wyniki << ix << "        " << rx(ix, wezly, war_fun, N) << endl;
    }

    gsl_vector_free(war_fun);
    gsl_vector_free(wezly);

    return 0;
}
