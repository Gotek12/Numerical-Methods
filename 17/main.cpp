//metoda Laguerre'a
#include <iostream>
#include <complex>
#include <cmath>
#include <math.h>
#include <iomanip>
#include <vector>
#include <time.h>

using namespace std;

//http://staff.elka.pw.edu.pl/~rnowak2/zprwiki/doku.php?id=liczby_zespolone_complex

//definicja typu danych do przechowywania liczb zespolonych a+ib = z
typedef complex<double> compNumber;
//def kontenera do przechowywania liczb zespolonych
typedef vector<complex<double>> vecCompNumbers;

//klasa reprezentująca metodę laguerre'a
class Laguerre
{
    compNumber tmp;

    //metoda zwracająca liczbę wielomianu lub
    //mliczaca 1 lub 2 pochodną w zależnosci od control
    //control = 1 - pierwsza pochodna
    //control = 2 - 2 pochodna
    compNumber pochodna(vecCompNumbers wartosci, int control, compNumber z)
    {
        switch (control)
        {
        case 0:
            tmp = wartosci[wartosci.size() - 1];
            break;
        case 1:
            tmp = wartosci[wartosci.size() - 1] * (double)(wartosci.size() - 1);
            break;
        case 2:
            tmp = wartosci[wartosci.size() - 1] * (double)(wartosci.size() - 1) * (double)(wartosci.size() - 2);
            break;
        }
        for (double i = wartosci.size() - 2; i >= control; i--)
        {
            switch (control)
            {
            case 0:
                tmp = tmp * z + wartosci[i];
                break;
            case 1:
                tmp = tmp * z + wartosci[i] * i;
                break;
            case 2:
                tmp = tmp * z + wartosci[i] * i * (i - 1);
                break;
            }
        }

        return tmp;
    }

    //r.kwadratowe
    void kwadrat(complex<double> a, complex<double> b, complex<double> c)
    {
        complex<double> delta = pow(b, 2) - ((4.0, 0.0) * a * c);

        complex<double> x1 = ((-b + sqrt(delta)) / ((2.0, 0.0) * a));
        complex<double> x2 = ((-b - sqrt(delta)) / ((2.0, 0.0) * a));

        wypisz(x1, x2);
    }

    //wypisywanie wartosci z rownania kwadratowego
    void wypisz(complex<double> x1, complex<double> x2)
    {
        check(x1);
        check(x2);
    }

    //formatowanie wypisywania
    void check(complex<double> x)
    {
        if (x.real() == 0.0 && x.imag() == 0.0)
        {
            cout << "0" << endl;
        }
        else if (x.real() == 0.0 && x.imag() != 0.0)
        {
            cout << x.imag() << "i" << endl;
        }
        else if (x.imag() == 0.0 && x.real() != 0.0)
        {
            cout << x.real() << endl;
        }
        else
        {
            cout << x.real() << " + " << x.imag() << "i" << endl;
        }
    }

    //wygladzanie
    void wygladzanie(vecCompNumbers &wartosci, compNumber z)
    {
        vecCompNumbers vecTmp;

        for (int i = 0; i < wartosci.size(); i++)
        {
            vecTmp.push_back(wartosci[i]);
        }

        wartosci.resize(wartosci.size() - 1);
        wartosci[wartosci.size() - 1] = vecTmp[wartosci.size()];

        for (int i = wartosci.size() - 1; i > 0; i--)
        {
            wartosci[i - 1] = vecTmp[i] + (z * wartosci[i]);
        }
    }

    compNumber laguerr(vecCompNumbers wartosci, compNumber z)
    {
        double n = wartosci.size() - 1;
        compNumber plus_czy_minus = pochodna(wartosci, 1, z) + sqrt((n - 1) * ((n - 1) * pochodna(wartosci, 1, z) * pochodna(wartosci, 1, z) - n * pochodna(wartosci, 0, z) * pochodna(wartosci, 2, z)));
        compNumber minus_czy_plus = pochodna(wartosci, 1, z) - sqrt((n - 1) * ((n - 1) * pochodna(wartosci, 1, z) * pochodna(wartosci, 1, z) - n * pochodna(wartosci, 0, z) * pochodna(wartosci, 2, z)));

        compNumber mianownik;
        if (abs(plus_czy_minus) > abs(minus_czy_plus))
        {
            mianownik = plus_czy_minus;
        }
        else
        {
            mianownik = minus_czy_plus;
        }

        return z - (n * pochodna(wartosci, 0, z)) / mianownik;
    }

    void rozwiaz(vecCompNumbers wartosci)
    {
        vecCompNumbers vecTmp;

        for (int i = 0; i < wartosci.size(); i++)
        {
            vecTmp.push_back(wartosci[i]);
        }

        while (wartosci.size() > 3)
        {
            //losujemy punkt startowy
            compNumber z0(rand() / ((double)RAND_MAX), rand() / ((double)RAND_MAX));

            z0 = laguerr(wartosci, z0);

            while (abs(pochodna(wartosci, 0, z0)) > 1e-12)
            {
                z0 = laguerr(wartosci, z0);
            }

            z0 = laguerr(vecTmp, z0);

            while (abs(pochodna(vecTmp, 0, z0)) > 1e-12)
            {
                z0 = laguerr(vecTmp, z0);
            }

            wygladzanie(wartosci, z0);

            cout << fixed << z0.real() << " + " << z0.imag() << endl;
        }

        kwadrat(wartosci[2], wartosci[1], wartosci[0]);
    }

  public:
    void test()
    {
        srand(time(NULL));
        vecCompNumbers wartosci;
        double tab1[] = {16.0, -72.0, -28.0, 558.0, -990.0, 783.0, -486.0, 243.0};
        wartosci.assign(tab1, tab1 + 8);
        rozwiaz(wartosci);
        wartosci.clear();
    }
};

int main()
{
    Laguerre lag;
    lag.test();

    return 0;
}