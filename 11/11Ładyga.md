## Wojciech Ładyga - zadanie 11

Język technologia: c++  

Aby wyliczyć jawnie współczynniki wielomianu interpolacyjnego Lagrange's na podstawie zadanych węzłów i funkcji należało wyliczyć wartości funkcji na podstawie podanych węzłw, 
a następnie rozwiązać taki układu.
Wyliczone wyniki pozwoliły wygenerować odpowiedni wykres.

Aby narysować wykres zastosowałem polecenia

    ./a.out > interp.dat
    graph -T ps < interp.dat > interp.ps

Wykres został wygenerowany na przedziale <-1,1> przeskakując od -1 do 1 o 0.001, korzystając z interpolacji.

Generowanie wykresu oparłem o przykład ze strony https://www.gnu.org/software/gsl/doc/html/interp.html.   
Wykorzystywany jest tam gnu plotunit.

W tym zadaniu mamy do dyspozycji 65 węzłów gdyż zaczynając od -1 , -1+1/32 + ... ,  i przechodząc aż do 1 skaczemy o 1/32. Więc wyliczając mamy 65 mozliwych argumętów funkcji.  
Przykład wyliczenia ilości węzłów stosując exela:

![obrazek](e.png)

z formułą ``=-1+(CX/32)`` gdzie cx to numer komurek od 1-65

Kod programu:

    /*
    * @Author: Wojciech Ladyga 
    * @Date: 2019-01-29
    * @Description: Zad 11
    */
    #include <iostream>
    #include <iomanip>
    #include <cmath>

    //interpolacja wielomianowa - lagrangea
    using namespace std;
    const int N = 66; //wezly

    class Lagrange
    {
        double suma;
        double tmp;

    public:
        double f(double x)
        {
            return 1 / (1 + 5 * pow(x, 2));
        }

        //metoda licząca lagrangea
        double lag(double xi[], double yi[], double xx)
        {
            suma = 0.0;

            for (int i = 0; i < N; i++)
            {
                tmp = yi[i];
                for (int j = 0; j < N; j++)
                {
                    if (j != i)
                        tmp = tmp * (xx - xi[j]) / (xi[i] - xi[j]);
                }
                suma += tmp;
            }
        }
    };

    int main()
    {
        Lagrange lagrange;
        double xi[N], yi[N];

        printf("#m=0,S=2\n");

        for (int i = 0; i < N; i++)
        {
            xi[i] = -1.0 + (i / 32.0);
            yi[i] = lagrange.f(xi[i]);
            printf("%g %g\n", xi[i], yi[i]);
        }
        printf("#m=1,S=0\n");

        for (double xx = -0.9; xx < 1.0; xx += 0.001)
        {
            lagrange.lag(xi, yi, xx);
            printf("%g %g\n", xx, lagrange.lag(xi, yi, xx));
        }
        //cout << lagrange.lag(xi, yi);
        return 0;
    }


  
Wyniki działania programu to:  
gdzie  
    -linia ciągła reprezentuje interpolację  
    -x reprezentują węzły i wartości funkcji wyliczone na ich podstawie
![obrazek](wykres.png)  