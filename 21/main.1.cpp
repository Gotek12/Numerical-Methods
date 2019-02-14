#include <math.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
const int iteracje = 12;            //min iteracji
const int ilPunktowStartowych = 10; //ilosc punktow startowyh
int test;

double P0[2], punktMin[2], S[2], gradient[2];
double minimum, Z;
double Hessian = 1.0, blad = 1.0;
double f(double *punkt);
void grad(double *punkt);
void wylicz();

int main()
{
    ofstream myfile;
    myfile.open("data.txt");
    srand(time(NULL)); // aby działało randomowe losowanie
    for (int j = 0; j < ilPunktowStartowych; j++)
    {
        //losowanie między <-10,10>
        for (int i = 0; i < 2; i++)
        {
            P0[i] = ((rand() % 21) - 10 + rand() / ((double)RAND_MAX));
        }

        //wypisanie wygenerowanych punktów
        cout << fixed << setprecision(5) << "(" << P0[0] << ", " << P0[1] << ")" << endl;

        Z = f(P0);
        int przeskok = 0;
        while ((Hessian < 1e-32) || (blad > 1e-32))
        {
            grad(P0);
            wylicz();
            przeskok++;
            for (int i = 0; i < 2; i++)
                P0[i] = punktMin[i];

            Z = minimum;
            if (przeskok == 50)
            {
                przeskok = 0;
                myfile << fixed << setprecision(10) << minimum << endl;
            }
        }

        printf("Test %lf \n\n", minimum);
    }
    myfile.close();
    return 0;
}

//funkcja Rosembrocka f(x,y) = (1-x)^2 + 100*(y-x^2)^2
//gdzie x[0] - to x
//      x[1] - to y
double f(double *punkt)
{
    return pow(1 - punkt[0], 2) + 100 * pow(punkt[1] - pow(punkt[0], 2), 2);
}

void grad(double *punkt)
{
    //df/dx
    gradient[0] = (400 * pow(punkt[0], 3) - 400 * punkt[0] * punkt[1] + 2.0 * punkt[0] - 2.0);
    //df/dy
    gradient[1] = (200 * punkt[1] - 200 * pow(punkt[0], 2));

    for (int i = 0; i < 2; i++)
    {
        S[i] = -gradient[i] / sqrt(pow(gradient[i], 2) + pow(gradient[1], 2));
    }
}

void wylicz()
{
    double P1[2], P2[2];
    double Hmin, D;
    double HessTab[3], error[3], z[3];
    int Jakobian = 0;

    test = 0;

    for (int i = 0; i < 2; i++)
    {
        P1[i] = P0[i] + Hessian * S[i];
        P2[i] = P0[i] + 2.0 * Hessian * S[i];
    }

    z[1] = f(P1);
    z[2] = f(P2);

    while ((Jakobian < iteracje) && (test == 0))
    {
        if (Z <= z[1])
        {
            z[2] = z[1];
            Hessian = Hessian / 2.0;

            for (int i = 0; i < 2; i++)
            {
                P2[i] = P1[i];
                P1[i] = P0[i] + Hessian * S[i];
            }
            z[1] = f(P1);
        }
        else
        {
            if (z[2] < z[1])
            {
                z[1] = z[2];
                Hessian = 2.0 * Hessian;

                for (int i = 0; i < 2; i++)
                {
                    P1[i] = P2[i];
                    P2[i] = P0[i] + 2.0 * Hessian * S[i];
                }
                z[2] = f(P2);
            }
            else
            {
                test = -1;
            }
        }
    }

    if (Hessian < 1e-32)
    {
        test = 1;
    }
    D = 4.0 * z[1] - 2.0 * Z - 2.0 * z[2];

    if (D < 0)
    {
        Hmin = Hessian * (4.0 * z[1] - 3.0 * Z - z[2]) / D;
    }
    else
    {
        test = 4;
        Hmin = Hessian / 3.0;
    }

    for (int i = 0; i < 2; i++)
    {
        punktMin[i] = P0[i] + Hmin * S[i];
    }

    minimum = f(punktMin);
    //cout << ":: " << minimum << " ::" << endl;
    HessTab[0] = fabs(Hmin);
    HessTab[1] = fabs(Hmin - Hessian);
    HessTab[2] = fabs(Hmin - 2.0 * Hessian);

    for (int i = 0; i < 3; i++)
    {
        if (HessTab[i] < Hessian)
        {
            Hessian = HessTab[i];
        }
    }

    if (Hessian < 1e-32)
    {
        test = 1;
    }

    error[0] = fabs(Z - minimum);
    error[1] = fabs(z[1] - minimum);
    error[2] = fabs(z[2] - minimum);

    if (error[0] < blad)
    {
        blad = error[0];
    }
    else if (error[1] < blad)
    {
        blad = error[1];
    }
    else if (error[2] < blad)
    {
        blad = error[2];
    }
    else if ((error[0] == 0) && (error[1] == 0) && (error[2] == 0))
    {
        blad = 0;
    }

    if (blad < 1e-32)
    {
        test = 2;
    }

    if ((test == 2) && (Hessian < 1e-32))
    {
        test = 3;
    }

    Jakobian++;
}
