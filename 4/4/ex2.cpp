#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace std;

const int N = 128;        //wielkosc macierzy
const int e = 1;          //reprezentant wektora e
const int dominujaca = 4; //glowna dominujaca, przez nia dzielimy el wynikowe po zsumowaniu

double *G_S()
{
    static double wynik[N]; //tablica wynikow
    fill_n(wynik, N, 0);    //wyzerowanie całego wektora wynikowego

    int x, y;                     //koordynaty
    for (int i = 0; i < 128; i++) //ilosc iteracji, teoretycznie czym więcej tym lepiej
    {
        double tmp[N];                              //tablica wynikow pomocniczych
        copy(begin(wynik), end(wynik), begin(tmp)); //wszystkie wyniki zapisuje do tablicy pomocniczej

        //przechodzimy po x i y
        for (x = 0; x < N; x++)
        {
            double suma = 0.0;
            for (y = 1; y < x; y++)
            {
                if (abs(y - x) == 1) //sprawdzamy czy jeden z el nie jest 1 a drugi 0
                {
                    suma += wynik[y];
                }
                else if (abs(y - x) == 4) //sprawdzamy czy jeden z el nie jest 4 a drugi 0
                {
                    suma += wynik[y];
                }
            }

            for (y = x + 1; y < N; y++)
            {
                if (abs(y - x) == 1)
                {
                    suma += tmp[y];
                }
                else if (abs(y - x) == 4)
                {
                    suma += tmp[y];
                }
            }

            wynik[x] = (e - suma) / dominujaca; //4 bo są to el dominujące więc dzielimy przez 4 //1 bo wartosci wynikowe to 1 vektor e
        }
    }
    return wynik;
}

int main()
{
    double *wynikGS = G_S();
    ofstream myfile;
    myfile.open("wynik1.txt");
    for (int k = 0; k < N; k++)
    {
        cout << setprecision(7) << fixed << wynikGS[k] << endl;
        myfile << setprecision(7) << wynikGS[k] << endl;
    }
    myfile.close();

    return 0;
}
