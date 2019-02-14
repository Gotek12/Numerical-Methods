#include <iostream>
#include <iomanip>
#include <math.h>
#include <limits.h>
#include <fstream>

using namespace std;
const int N = 65; //wezly
const int D = 3;  //parametr

int dmumianNewtona(int n, int k)
{
    if (k == 0 || k == n)
        return 1;

    return dmumianNewtona(n - 1, k - 1) + dmumianNewtona(n - 1, k);
}

unsigned long binomial(unsigned long n, unsigned long k)
{
    unsigned long c = 1, i;

    if (k > n - k) // take advantage of symmetry
        k = n - k;

    for (i = 1; i <= k; i++, n--)
    {
        if (c / i > UINT_MAX / n) // return 0 on overflow
            return 0;

        c = c / i * n + c % i * n / i; // split c * n / i into (c / i * i + c % i) * n / i
    }

    return c;
}

int main()
{
    cout << dmumianNewtona(23, 5) << endl;
    cout << binomial(23, 5);
    return 0;
}