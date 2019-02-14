#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

const double dokladnosc = 100000;
const double MIN = 0.0000001;
const int ile_iter = 22;

/** Zadana funkcja */
double given_func(double x){
    return sin( M_PI*(1.0 + sqrt(x)) / (1.0 + x*x) )*exp(-x);
}

/** Metoda trapezow */
double M_Trapez(double podzial, double A){
    double integral;

    integral = (given_func(0) + given_func(A))/2;
    for(double i  = podzial; i < A; i += podzial)
        integral += given_func(i);

    return integral *= podzial;
}

/** Metoda Romberga */
double  M_Romberg(double A, int l_iteracji){
    int i;
    double *s = new double[l_iteracji];
    double var;
    for(i = 1; i < l_iteracji; i++)
        s[i] = 1;

    /** Iteracja */
    for(int k = 1; k < l_iteracji; k++){
        for(i = 1; i < k+1; i++){
            if(i == 1){
                var = s[i];
                s[i] = M_Trapez(A/pow(2, k-1), A);
            }
            else{
                s[k] = (pow(4, i-1)*s[i-1] - var)/(pow(4, i-1) - 1);
                var = s[i];
                s[i] = s[k];
            }
        }
    }

    return s[l_iteracji-1];
}

int main(){
    double dx;
    double A = 0.0;

    cout << setprecision(7) << fixed;

    /** Wyznaczanie A */
    while(exp(-A) > MIN){
        A++;
    }

    /** Podzial przedzialu <0, 17> */
    dx = A/dokladnosc;

    cout << "Calka obliczona metoda trapezow dla " << (int)dokladnosc << " podzialow: \n";
    cout << M_Trapez(dx, A) << endl;
    cout << "\n\n ************************************************************ \n\n" << endl;
    cout << "Calka obliczona metoda Romberga dla " << ile_iter << " iteracji: \n";
    cout << M_Romberg(A, ile_iter) << endl;

    return 0;
}
