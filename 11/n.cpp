#include <iostream>
#include <iomanip>
#include <iostream>
#include <cmath>
using namespace std;
const int N = 66; //wezly
double f(double x)
{
    return 1 / (1 + 5 * pow(x, 2));
}

int main()
{

    /* Degree of P(x)  :  INPUT         */
    int K, J;          /* Loop counters                    */
    double X[N], Y[N]; /* INPUT : Abscissas of the points  */
                       /* INPUT : Ordinates of the points  */
    double Sum;
    double T; /* Independent variable             */
    double Term;
    int q; /* For comparison to end input loop */

    for (J = 0; J < N; J++)
    {
        X[J] = -1.0 + (J / 32.0);
        Y[J] = f(X[J]);
    }

    T = 0.6;
    Sum = 0.0; /* initialize variable */

    /* Form terms to be added  */
    for (K = 0; K < N; K++)
    {
        Term = Y[K];
        for (J = 0; J < N; J++)
        {
            /* To avoid division by zero. */
            if (J != K)
                Term = Term * (T - X[J]) / (X[K] - X[J]);
        }
        Sum += Term;
    }

    cout << Sum;
    return 0;
}
