//https://www.gnu.org/software/gsl/doc/html/nls.html
#include <math.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << ((rand() % 101) - 50 + rand() / ((double)RAND_MAX));

    return 0;
}
