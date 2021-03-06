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
  public:
    compNumber tmp;

    compNumber wartoscLosowana;

    //metoda zwracająca liczbę wielomianu lub
    //mliczaca 1 lub 2 pochodną w zależnosci od control
    //control = 1 - pierwsza pochodna
    //control = 2 - 2 pochodna
    compNumber pochodna(vecCompNumbers wartosci, int control)
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
                tmp = tmp * wartoscLosowana + wartosci[i];
                break;
            case 1:
                tmp = tmp * wartoscLosowana + wartosci[i] * i;
                break;
            case 2:
                tmp = tmp * wartoscLosowana + wartosci[i] * i * (i - 1);
                break;
            }
        }

        return tmp;
    }

    //r.kwadratowe
    void kwadrat(complex<double> a, complex<double> b, complex<double> c)
    {
        complex<double> delta = pow(b, 2) - (4.0 * a * c);
        complex<double> x1 = ((-b + sqrt(delta)) / (2.0 * a));
        complex<double> x2 = ((-b - sqrt(delta)) / (2.0 * a));

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
            cout << fixed << x.real() << " + " << x.imag() << "i" << endl;
        }
    }

    //wygladzanie
    void wygladzanie(vecCompNumbers &wartosci)
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
            wartosci[i - 1] = vecTmp[i] + (wartoscLosowana * wartosci[i]);
        }
    }

    compNumber laguerr(vecCompNumbers wartosci)
    {
        double n = wartosci.size() - 1;
        compNumber plus_czy_minus = pochodna(wartosci, 1) + sqrt((n - 1) * ((n - 1) * pochodna(wartosci, 1) * pochodna(wartosci, 1) - n * pochodna(wartosci, 0) * pochodna(wartosci, 2)));
        compNumber minus_czy_plus = pochodna(wartosci, 1) - sqrt((n - 1) * ((n - 1) * pochodna(wartosci, 1) * pochodna(wartosci, 1) - n * pochodna(wartosci, 0) * pochodna(wartosci, 2)));

        compNumber mianownik;
        if (abs(plus_czy_minus) > abs(minus_czy_plus))
        {
            mianownik = plus_czy_minus;
        }
        else
        {
            mianownik = minus_czy_plus;
        }

        return wartoscLosowana - (n * pochodna(wartosci, 0)) / mianownik;
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

            wartoscLosowana = z0;
            z0 = laguerr(wartosci);

            while (abs(pochodna(wartosci, 0)) > 1e-12)
            {
                wartoscLosowana = z0;
                z0 = laguerr(wartosci);
            }

            wartoscLosowana = z0;
            z0 = laguerr(vecTmp);

            while (abs(pochodna(vecTmp, 0)) > 1e-12)
            {
                wartoscLosowana = z0;
                z0 = laguerr(vecTmp);
            }

            wygladzanie(wartosci);

            //cout << fixed << z0.real() << " + " << z0.imag() << endl;
            check(z0);
        }

        kwadrat(wartosci[2], wartosci[1], wartosci[0]);
    }

  public:
    void test()
    {
        srand(time(NULL));
        vecCompNumbers wartosci;

        compNumber a0(16, 0);
        compNumber a1(-72, 0);
        compNumber a2(-28, 0);
        compNumber a3(558, 0);
        compNumber a4(-990, 0);
        compNumber a5(783, 0);
        compNumber a6(-486, 0);
        compNumber a7(243, 0);
        wartosci.push_back(a0);
        wartosci.push_back(a1);
        wartosci.push_back(a2);
        wartosci.push_back(a3);
        wartosci.push_back(a4);
        wartosci.push_back(a5);
        wartosci.push_back(a6);
        wartosci.push_back(a7);

        rozwiaz(wartosci);
        wartosci.clear();

        cout << endl
             << endl;

        compNumber x1(1, 0);
        compNumber x2(1, 0);
        compNumber x3(3, 0);
        compNumber x4(2, 0);
        compNumber x5(-1, 0);
        compNumber x6(-3, 0);
        compNumber x7(-11, 0);
        compNumber x8(-8, 0);
        compNumber x9(-12, 0);
        compNumber x10(-4, 0);
        compNumber x11(-4, 0);
        wartosci.push_back(x1);
        wartosci.push_back(x2);
        wartosci.push_back(x3);
        wartosci.push_back(x4);
        wartosci.push_back(x5);
        wartosci.push_back(x6);
        wartosci.push_back(x7);
        wartosci.push_back(x8);
        wartosci.push_back(x9);
        wartosci.push_back(x10);
        wartosci.push_back(x11);

        rozwiaz(wartosci);
        wartosci.clear();

        cout << endl
             << endl;

        compNumber y1(1, 0);
        compNumber y2(0, -1);
        compNumber y3(-1, 0);
        compNumber y4(0, 1);
        compNumber y5(1, 0);
        wartosci.push_back(y1);
        wartosci.push_back(y2);
        wartosci.push_back(y3);
        wartosci.push_back(y4);
        wartosci.push_back(y5);

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