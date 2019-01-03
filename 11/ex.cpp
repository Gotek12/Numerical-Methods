#include <iostream>
#include <iomanip>
#include <fstream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_sf.h>

using namespace std;

const int N = 65;   //liczba wezlow

double funkcja(double x){
    return 1/(1 + (5*x*x));
}

int main(){
    int i, j;
    int s;
    double wezel = -1.0;
    cout << setprecision(16) << fixed;

    gsl_vector * b = gsl_vector_alloc(N);
    gsl_vector * a = gsl_vector_alloc(N);
    gsl_matrix * V = gsl_matrix_alloc(N, N);
    gsl_permutation * p = gsl_permutation_alloc(N);

    for(i = 0; i < N; i++){
        gsl_vector_set(b, i, funkcja(wezel + i*(1.0/32.0)) );
    }

    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            gsl_matrix_set(V, i, j, gsl_sf_pow_int((wezel + i*(1.0/32.0)), N-1-j) );

    gsl_linalg_LU_decomp(V, p, &s);
    gsl_linalg_LU_solve(V, p, b, a);

    for(i = 0; i < N; i++){
        cout << "a" << N-1-i << " = " << gsl_vector_get(a, i) << endl;
    }

    cout << "\n\n Wielomian interpolacyjny ma postac:" << endl;
    cout << "w(x) = ";
    for(i = 0; i < N; i++){
        if(i != N-1) cout << gsl_vector_get(a, i) << "x^" << N-1-i << "  +  ";
        else cout << gsl_vector_get(a, i) << "x^" << N-1-i << endl;
    }

    gsl_matrix_free(V);
    gsl_vector_free(b);
    gsl_vector_free(a);

    return 0;
}
