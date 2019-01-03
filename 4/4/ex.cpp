#include <iostream>
#include <iomanip>
#include <fstream>
#include <fstream>
#include <cmath>

using namespace std;

const int N = 3;            //wielkosc macierzy
const int no_of_iter = 128; //ilosc iteracji, czym więcej tym dikladniejszy wynik

int main()
{
    double result[N];     //tablica wynikow
    double result_pom[N]; //tablica wynikow pomocniczych
    double suma = 0.0;    //
    for (int i = 0; i < N; i++)
        result[i] = 0; //wypelniam funkcje wynikową zerami

    int x, y;                            //koordynaty
    for (int i = 0; i < no_of_iter; i++) //przechodzimy przez wszytskie itracje
    {
        for (y = 0; y < N; y++)
            result_pom[y] = result[y]; //wszystkie wyniki zapisuje do ablicy pomocniczej

        //przechodzimy po x i y
        for (x = 0; x < N; x++)
        {
            suma = 0.0;
            for (y = 1; y < x; y++)
                if ((y - x == -1) || (y - x == 1) || (y - x == -4) || (y - x == 4)) //sprawdzamy czy jeden z el nie jest 1 lub 4 a drugi 0
                    suma += result[y];

            for (y = x + 1; y < N; y++)
                if ((y - x == -1) || (y - x == 1) || (y - x == -4) || (y - x == 4))
                    suma += result_pom[y];

            result[x] = 0.25 * (1 - suma); //0.25 bo są to el dominujące //1 bo wartosci wynikowe to 1
        }
    }

    cout << setprecision(5) << fixed;
    ofstream myfile;
    myfile.open("wynik.txt");
    for (int k = 0; k < N; k++)
    {
        cout << result[k] << endl;
        myfile << result[k] << endl;
    }

    myfile.close();

    return 0;
}
