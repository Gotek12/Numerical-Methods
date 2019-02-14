//metoda Laguerre'a
#include <iostream>
#include <complex>
#include <cmath>
#include <math.h>
#include <vector>

using namespace std;

//http://staff.elka.pw.edu.pl/~rnowak2/zprwiki/doku.php?id=liczby_zespolone_complex

//definicja typu danych do przechowywania liczb zespolonych a+ib = z
typedef complex<double> compNumber;
//def kontenera do przechowywania liczb zespolonych
typedef vector<complex<double>> vecCompNumbers;

//klasa reprezentująca metodę laguerre'a
class Laguerre
{
  private:
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

    //wypisywanie wartosci z rownania kwadratowego
    void wypisz(complex<double> x1, complex<double> x2)
    {
        check(x1);
        check(x2);
    }

    //formatowanie wypisywania
    void check(complex<double> x)
    {
        if ((x.real() == 0.0 || x.real() == -0.0) && (x.imag() == 0.0 || x.imag() == -0.0))
        {
            cout << fixed << "0" << endl;
        }
        else if ((x.real() == 0.0 || x.real() == -0.0) && (x.imag() != 0.0 || x.imag() != -0.0))
        {
            cout << fixed << x.imag() << "i" << endl;
        }
        else if ((x.imag() == 0.0 || x.imag() == -0.0) && (x.real() != 0.0 || x.real() != -0.0))
        {
            cout << fixed << x.real() << endl;
        }
        else
        {
            cout << fixed << x.real() << " + " << x.imag() << "i" << endl;
        }
    }

    compNumber laguerr(vecCompNumbers wartosci)
    {
        compNumber sq = sqrt((double)(wartosci.size() - 2) * ((double)(wartosci.size() - 2) * pochodna(wartosci, 1) * pochodna(wartosci, 1) - (double)(wartosci.size() - 1) * pochodna(wartosci, 0) * pochodna(wartosci, 2)));
        compNumber firstP = pochodna(wartosci, 1);

        if (abs(firstP + sq) > abs(firstP - sq))
        {
            return wartoscLosowana - ((double)(wartosci.size() - 1) * pochodna(wartosci, 0)) / (firstP + sq);
        }
        else
        {
            return wartoscLosowana - ((double)(wartosci.size() - 1) * pochodna(wartosci, 0)) / (firstP - sq);
        }
    }

    //los 0 - 1
    double randZeroToOne()
    {
        return rand() / (RAND_MAX + 1.);
    }

  public:
    //wyliczamy rozwiązania funkcji
    void rozwiaz(vecCompNumbers wartosci)
    {

        while (wartosci.size() > 3)
        {
            //losujemy punkt startowy
            compNumber los(randZeroToOne(), randZeroToOne());

            wartoscLosowana = los;
            los = laguerr(wartosci);

            while (abs(pochodna(wartosci, 0)) > 1e-12)
            {
                wartoscLosowana = los;
                los = laguerr(wartosci);
            }

            //wygladzanie
            vecCompNumbers vecTmp = wartosci;
            wartosci.resize(wartosci.size() - 1);
            wartosci[wartosci.size() - 1] = vecTmp[wartosci.size()];

            for (int i = wartosci.size() - 1; i > 0; i--)
            {
                wartosci[i - 1] = vecTmp[i] + (wartoscLosowana * wartosci[i]);
            }
            check(los);
        }

        //jesli odpowiednio wygladzimy to możemy rozwiązać równaie kwadratowe
        complex<double> delta = pow(wartosci[1], 2) - (4.0 * wartosci[2] * wartosci[0]);
        complex<double> x1 = ((-wartosci[1] + sqrt(delta)) / (2.0 * wartosci[2]));
        complex<double> x2 = ((-wartosci[1] - sqrt(delta)) / (2.0 * wartosci[2]));

        wypisz(x1, x2);
    }
};

int main()
{
    Laguerre lag;
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

    lag.rozwiaz(wartosci);
    wartosci.clear();

    cout << endl;

    compNumber x1(-4, 0);
    compNumber x2(-4, 0);
    compNumber x3(-12, 0);
    compNumber x4(-8, 0);
    compNumber x5(-11, 0);
    compNumber x6(-3, 0);
    compNumber x7(-1, 0);
    compNumber x8(2, 0);
    compNumber x9(3, 0);
    compNumber x10(1, 0);
    compNumber x11(1, 0);
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

    lag.rozwiaz(wartosci);
    wartosci.clear();

    cout << endl;

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

    lag.rozwiaz(wartosci);
    wartosci.clear();

    return 0;
}