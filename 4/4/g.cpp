#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace std;
int n = 128;
const double tolerancja = 0.00001;

int main()
{

    int A[n][n];
    int b[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        A[i][i] = 4;
        b[i] = 1;

        int j = i + 1;
        int k = i + 1;
        if (j < n && k < n)
        {
            A[i][j] = 1;
            A[k][i] = 1;
        }

        int jj = i + 4;
        int kk = i + 4;
        if (jj < n && kk < n)
        {
            A[i][jj] = 1;
            A[kk][i] = 1;
        }
    }

    ofstream myfile;
    myfile.open("matrix.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            myfile << A[i][j] << " ";
        }
        myfile << endl;
    }
    myfile.close();

        return 0;
}