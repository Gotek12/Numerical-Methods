#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 10
#define Jmax 20   /** ilosc iteracji */
#define Max 50

double P0[MAX], Pmin[MAX];
double Ymin, Y0;
double H   = 1.0;
double Err = 1.0;
double S[MAX], G[MAX];
int Cond;
/** int ILE_PKT = 10;
* Gdy nie chce Ci sie podawac ilosci losowanych punktow to usun komentarz
* i odpowiedni linie w main()*/
double Delta = 1e-64;       /** tolerancja dla punktow */
double Epsilon = 1e-64;     /** tolerancja dla wartosci funkcji */


/** funkcja Rosenbrocka */
double f_Rosenbrocka(double *P){
    return ( (1 - P[0])*(1 - P[0]) + 100*(P[1] - P[0]*P[0])*(P[1] - P[0]*P[0]) );
}

void Gradient(double *P){
    /** gradient */
    G[0] = ( 400*P[0]*P[0]*P[0] - 400*P[0]*P[1] + 2*P[0] - 2.0 );
    G[1] = ( 200*P[1] - 200*P[0]*P[0] );

    /** "strona" gradientu */
    S[0] = -G[0]/sqrt( G[0]*G[0] + G[1]*G[1] );
    S[1] = -G[1]/sqrt( G[0]*G[0] + G[1]*G[1] );
}

void Quadmin(int NC, double Delta, double Epsilon){
    double P1[MAX];
    double P2[MAX];
    double H0, H1, H2, Hmin, E0, E1, E2, Y1, Y2, D;
    int i, J;

    Cond = 0;
    J = 0;

    for(i = 0; i < NC; i++){
        P1[i] = P0[i] + H * S[i];
        P2[i] = P0[i] + 2.0 * H * S[i];
    }

    Y1 = f_Rosenbrocka(P1);
    Y2 = f_Rosenbrocka(P2);

    while( (J < Jmax) && (Cond == 0) ){
        if ( Y0 <= Y1 ){
        Y2    = Y1;
        H     = H / 2.0;

        for (i = 0; i < NC; i++){
            P2[i] = P1[i];
            P1[i] = P0[i] + H * S[i];
        }
        Y1 = f_Rosenbrocka(P1);
        }
        else{
            if( Y2 < Y1 ){
                Y1 = Y2;
                H  = 2.0 * H;

                for (i = 0; i < NC; i++){
                   P1[i] = P2[i];
                   P2[i] = P0[i] + 2.0 * H * S[i];
                }
                Y2 = f_Rosenbrocka(P2);
            }
            else Cond = -1;
        }
    }

    if( H < Delta ) Cond = 1;
    D = 4.0 * Y1 - 2.0 * Y0 - 2.0 * Y2;

    if( D < 0 ) Hmin = H*( 4.0 * Y1 - 3.0 * Y0 - Y2 )/D;
    else{
        Cond = 4;
        Hmin = H / 3.0;
    }

    for(i = 0; i < NC; i++)
        Pmin[i] = P0[i] + Hmin * S[i];

    Ymin = f_Rosenbrocka(Pmin);

    H0 = fabs(Hmin);
    H1 = fabs(Hmin - H);
    H2 = fabs(Hmin - 2.0*H);

    if( H0 < H ) H = H0;
    if( H1 < H ) H = H1;
    if( H2 < H ) H = H2;
    if( H < Delta ) Cond = 1;

    E0 = fabs(Y0 - Ymin);
    E1 = fabs(Y1 - Ymin);
    E2 = fabs(Y2 - Ymin);

    if( E0 < Err ) Err = E0;
    else if( E1 < Err ) Err = E1;
    else if( E2 < Err ) Err = E2;
    else if( (E0 == 0) && (E1 == 0) && (E2 == 0) ) Err = 0;

    if( Err < Epsilon ) Cond = 2;
    if( (Cond == 2) && (H < Delta) ) Cond = 3;

    J++;
}

int main(){
    int NC = 2;                   /* Number of components of gradient    */
    int Count = 0;
    int i, j, ILE_PKT;

    printf("--------------------------------------------------------------------------- \n");
    printf("---------------------------- Metoda Gradientow ---------------------------- \n");
    printf("--------------------------------------------------------------------------- \n");
    printf("\nPodaj ilosc losowych punktow poczatkowych \n");
    scanf("%d", &ILE_PKT);

    printf("\n");
    printf("\n");

    printf("--------------------------------------------------------------------------- \n");
    printf("--- Rozpoczeto losowanie %d punktow w kwadracie [-100, 100]x[-100, 100] --- \n", ILE_PKT);
    printf("--------------------------------------------------------------------------- \n");

    printf("\n");
    printf("\n");

    srand(time(NULL));

    for(j = 0; j < ILE_PKT; j++){
        P0[0] = ( (rand()%201) - 100 + rand()/((double)RAND_MAX) );
        P0[1] = ( (rand()%201) - 100 + rand()/((double)RAND_MAX) );

        printf("Wylosowano punkt: \n");
        printf("(%.10lf, %.10lf) \n", P0[0], P0[1]);

        Y0 = f_Rosenbrocka(P0);

        while( (Count < Max) && (H < Delta) || (Err > Epsilon) ){
            Gradient(P0);
            Quadmin(NC, Delta, Epsilon);

            for(i = 0; i < NC; i++)
                P0[i] = Pmin[i];

            Y0 = Ymin;

            Count++;
        }

        printf("--------------------------------------------------------------------------- \n\n");
        printf("Minimum lokalne (lub globalne) jest w punkcie: \n");
        printf("(%.10lf, %.10lf) \n", Pmin[0], Pmin[1]);
        printf("Wartosc funkcji w minimum to: %lf \n\n", Ymin);
        printf("--------------------------------------------------------------------------- \n");

        if( Cond == 0 ) printf("Zbieznosc nie osiagnieta poniewaz osiagnieto maksymalna ilosc iteracji of \n");
        if( Cond == 1 ) printf("Osiagnieto zbieznosc odcietej \n");
        if( Cond == 2 ) printf("Osiagnieto zbieznosc odcietej \n");
        if( Cond == 3 ) printf("Osiagnieto zbieznosc dla obu wspolrzednych \n");
        if( Cond == 4 ) printf("Zbieznosc jest watpliwa, poniewaz pojawilo sie dzielenie przez 0 \n");

        printf("\n");
        printf("\n");
    }

    return 0;
}
