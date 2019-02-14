//implementacja Algorytm Levenberga-Marquardta dla funkcji Rosembrocka
#include <math.h>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;

const int iteracje = 12;
const int Max = 50;
const int ilPunktow = 10;
double e = 1e-12; //tolerancja dla punktow i wartosci

double P0[10], Pmin[10];
double Ymin = 0.0, Y0 = 0.0;
double H = 1.0;
double Err = 1.0;
double S[10], G[10];
int Cond = 0;

//funkcja Rosembrocka f(x,y) = (1-x)^2 + 100*(y-x^2)^2
//gdzie x[0] - to x
//      x[1] - to y
double f(double *x)
{
    return pow(1 - x[0], 2) + 100 * pow(x[1] - pow(x[0], 2), 2);
}

void grad(double *P)
{
    //df/dx
    G[0] = (400 * (pow(P[0], 3) + P[0] * P[1]) + 2.0 * P[0] - 2.0);
    //df/dy
    G[1] = (200 * (P[1] - pow(P[0], 2)));

    /** "strona" gradu */
    S[0] = -G[0] / sqrt(G[0] * G[0] + G[1] * G[1]);
    S[1] = -G[1] / sqrt(G[0] * G[0] + G[1] * G[1]);
}

void Quadmin(double e)
{
    double P1[10], P2[10];
    double H0 = 0.0, H1 = 0.0, H2 = 0.0, Hmin = 0.0, E0 = 0.0, E1 = 0.0, E2 = 0.0, Y1 = 0.0, Y2 = 0.0, D = 0.0;
    int J = 0;

    Cond = 0;
    J = 0;

    for (int i = 0; i < 2; i++)
    {
        P1[i] = P0[i] + H * S[i];
        P2[i] = P0[i] + 2.0 * H * S[i];
    }

    Y1 = f(P1);
    Y2 = f(P2);

    while ((J < iteracje) && (Cond == 0))
    {
        if (Y0 <= Y1)
        {
            Y2 = Y1;
            H = H / 2.0;

            for (int i = 0; i < 2; i++)
            {
                P2[i] = P1[i];
                P1[i] = P0[i] + H * S[i];
            }
            Y1 = f(P1);
        }
        else
        {
            if (Y2 < Y1)
            {
                Y1 = Y2;
                H = 2.0 * H;

                for (int i = 0; i < 2; i++)
                {
                    P1[i] = P2[i];
                    P2[i] = P0[i] + 2.0 * H * S[i];
                }
                Y2 = f(P2);
            }
            else
                Cond = -1;
        }
    }

    if (H < e)
        Cond = 1;
    D = 4.0 * Y1 - 2.0 * Y0 - 2.0 * Y2;

    if (D < 0)
        Hmin = H * (4.0 * Y1 - 3.0 * Y0 - Y2) / D;
    else
    {
        Cond = 4;
        Hmin = H / 3.0;
    }

    for (int i = 0; i < 2; i++)
        Pmin[i] = P0[i] + Hmin * S[i];

    Ymin = f(Pmin);

    H0 = fabs(Hmin);
    H1 = fabs(Hmin - H);
    H2 = fabs(Hmin - 2.0 * H);

    if (H0 < H)
        H = H0;
    if (H1 < H)
        H = H1;
    if (H2 < H)
        H = H2;
    if (H < e)
        Cond = 1;

    E0 = fabs(Y0 - Ymin);
    E1 = fabs(Y1 - Ymin);
    E2 = fabs(Y2 - Ymin);

    if (E0 < Err)
        Err = E0;
    else if (E1 < Err)
        Err = E1;
    else if (E2 < Err)
        Err = E2;
    else if ((E0 == 0) && (E1 == 0) && (E2 == 0))
        Err = 0;

    if (Err < e)
        Cond = 2;
    if ((Cond == 2) && (H < e))
        Cond = 3;

    J++;
}

int main()
{
    int test = 0;

    srand(time(NULL));

    for (int j = 0; j < ilPunktow; j++)
    {
        P0[0] = ((rand() % 201) - 100 + rand() / ((double)RAND_MAX));
        P0[1] = ((rand() % 201) - 100 + rand() / ((double)RAND_MAX));

        printf("(%.10lf, %.10lf) \n", P0[0], P0[1]);

        Y0 = f(P0);
        cout << fixed << setprecision(4) << Y0 << endl;

        int kk = 0;
        int z = 0;
        while ((test < Max) && (H < e) || (Err > e))
        {
            grad(P0);
            Quadmin(e);
            kk++;
            for (int i = 0; i < 2; i++)
                P0[i] = Pmin[i];

            Y0 = Ymin;
            if (kk == 50)
            {
                kk = 0;
                //cout << fixed << setprecision(8) << Y0 << endl;
            }
            test++;
            //cout << ++z << endl;
        }
        //cout << fixed << setprecision(8) << Y0 << endl;
        printf("Wartosc funkcji w minimum to: %lf \n\n", Ymin);
    }

    return 0;
}
