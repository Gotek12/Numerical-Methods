#include <iostream>
#include <fstream>
#include <complex>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <vector>
#include <time.h>

using namespace std;

const double eps = 1e-12;

typedef complex<double> Complex;
typedef vector<complex<double> > wspolczynniki_w;

Complex WAR_wielomianu(wspolczynniki_w a, Complex z){
    double n = a.size()-1;
    Complex result = a[n];

    for(double i = n-1; i >= 0; i--)
        result = result*z + a[i];

    return result;
}

Complex Pochodna_w(wspolczynniki_w a, Complex z){
    double n = a.size()-1;
    Complex result = a[n]*n;

    for(double i = n-1; i >= 1; i--)
        result = result*z + a[i]*i;

    return result;
}

Complex D_Pochodna_w(wspolczynniki_w a, Complex z){
    double n = a.size()-1;
    Complex result = a[n] * n * (n-1);

    for (double i = n-1; i >= 2; i--)
        result = result*z + a[i]*i*(i-1);

    return result;
}

Complex Metoda_Laguerre(wspolczynniki_w a, Complex z){
    double n = a.size() - 1;

    Complex plus_czy_minus = Pochodna_w(a, z) + sqrt( (n - 1)*((n - 1)*Pochodna_w(a, z)*Pochodna_w(a, z) - n*WAR_wielomianu(a, z)*D_Pochodna_w(a, z)) );
    Complex minus_czy_plus = Pochodna_w(a, z) - sqrt( (n - 1)*((n - 1)*Pochodna_w(a, z)*Pochodna_w(a, z) - n*WAR_wielomianu(a, z)*D_Pochodna_w(a, z)) );

    Complex mianownik;

    if(abs(plus_czy_minus) > abs(minus_czy_plus)) mianownik = plus_czy_minus;
    else mianownik = minus_czy_plus;

    Complex licznik = n * WAR_wielomianu(a, z);

    return z - licznik/mianownik;
}

Complex WYGLADZ_WSP(wspolczynniki_w &a, Complex z){
    int i;
    wspolczynniki_w tmp;

    for(i = 0; i < a.size(); i++)
        tmp.push_back(a[i]);

    a.resize(a.size() - 1);
    a[a.size()-1] = tmp[a.size()];

    for(i = a.size() - 1; i > 0; i--)
        a[i-1] = tmp[i] + (z*a[i]);

    return 0;
}

void Rozwiaz_r_Kwadratowe( complex<double> a,complex<double> b, complex<double> c){
    complex<double>  x1, x2, delta;

    complex<double> d (2.0, 0.0);
    complex<double> e (4.0, 0.0);

    delta = (b*b) - (e*a*c);

    x1 = (-b + sqrt(delta))/(d*a);
    x2 = (-b - sqrt(delta))/(d*a);

    cout << x1.real() << " + " << x1.imag() << endl;
    cout << x2.real() << " + " << x2.imag() << endl;
}

void calculate(wspolczynniki_w a){
    wspolczynniki_w tmp;
    int i;

    for(i = 0; i < a.size(); i++)
        tmp.push_back(a[i]);

    i = 0;      // Jakby kto chcial zobaczyc ile bylo iteracji

    while(a.size() > 3){
        i++;
        /**
        * Startujemy z losowych punktow (jak cos to wpisac punkty recznie)
        */
        Complex z0(rand()/((double)RAND_MAX), rand()/((double)RAND_MAX));

        z0 = Metoda_Laguerre(a, z0);

        while(abs(WAR_wielomianu(a, z0)) > eps){
            z0 = Metoda_Laguerre(a, z0);
        }

        z0 = Metoda_Laguerre(tmp, z0);

        while(abs(WAR_wielomianu(tmp, z0)) > eps){
            z0 = Metoda_Laguerre(tmp, z0);
        }

        /**
        * Obnizanie wspolczynnika wielomianu
        */
        WYGLADZ_WSP(a, z0);

        cout << fixed << z0.real() << " + " << z0.imag() << endl;
    }
    i++;

    /**
    * Gdy "wyplaszczymy" nasz wielomian do wielomianu stopnia 2,
    * czyli rownania kwadratowego to nie ma sensu dalej go "wyplaszczac"
    * tylko rozwiazac zwykle rownanie postaci az^2 + bz + c = 0
    */
    Rozwiaz_r_Kwadratowe(a[2], a[1], a[0]);
}

int main(){
    srand(time(NULL));

    cout << setprecision(10) << fixed;

    wspolczynniki_w a;

    /**
    * Rownanie 243z^7 - 486z^6 + 783z^5 - 990z^4 + 558z^3 - 28z^2 - 72z + 16 = 0
    */
    double tab1[] = { 16, -72, -28, 558, -990, 783, -486, 243 };
    a.assign(tab1, tab1 + 8);
    cout << "Pierwiastki rownania 243z^7 - 486z^6 + 783z^5 - 990z^4 + 558z^3 - 28z^2 - 72z + 16 = 0" << endl << endl;
    calculate(a);
    cout << endl << endl <<endl;
    a.clear();

    /**
    * Rownanie z^10 + z^9 + 3z^8 + 2z^7 - z^6 - 3z^5 - 11z^4 - 8z^3 - 12z^2 - 4z - 4 = 0
    */
    double tab2[] = { -4, -4, -12, -8, -11, -3, -1, 2, 3, 1, 1 };
    a.assign(tab2, tab2 + 11);

    cout << "Pierwiastki rownania z^10 + z^9 + 3z^8 + 2z^7 - z^6 - 3z^5 - 11z^4 - 8z^3 - 12z^2 - 4z - 4 = 0" << endl <<endl;
    calculate(a);
    cout << endl << endl << endl;
    a.clear();

    /**
    * Rownanie z^4 + iz^3 - z^2 - iz + 1 = 0
    * Jako ze zrobilem to na wektorach w tym rownaniu musialem dodac wspolczynniki w ten sposob
    * (zeby nie bylo raka)
    */
    Complex a0(1, 0);
    Complex a1(0, -1);
    Complex a2(-1, 0);
    Complex a3(0, 1);
    Complex a4(1, 0);
    a.push_back(a0);
    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);
    a.push_back(a4);
    cout << "Pierwiastki rownania z^4 + iz^3 - z^2 - iz + 1 = 0" << endl << endl;
    calculate(a);
    cout << endl << endl << endl;
    a.clear();

    return 0;
}
