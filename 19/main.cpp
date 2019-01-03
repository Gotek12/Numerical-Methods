#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <gsl/gsl_spline.h>

using namespace std;
void readFile();
void splajn();
//zmienne globalne przechowywujace x i y pobrane z pliku
vector<double> x, y;

int main()
{
    readFile();
    splajn();
    return 0;
}

//czytam z pliku
void readFile()
{
    fstream plik;
    plik.open("dane.txt", ios::in);
    if (plik.good() == true)
    {
        while (!plik.eof())
        {
            double tmpX, tmpY;
            plik >> tmpX >> tmpY;
            x.push_back(tmpX);
            y.push_back(tmpY);
        }
        plik.close();
    }
}

void splajn()
{
    int N = x.size() - 1;
    //convert vector to array
    double xx[N], yy[N];
    copy(x.begin(), x.end(), xx);
    copy(y.begin(), y.end(), yy);

    printf("#m=0,S=2\n");
    for (int i = 0; i < N; i++)
    {
        printf("%g %g\n", xx[i], yy[i]);
    }
    printf("#m=1,S=0\n");

    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    gsl_spline *spline = gsl_spline_alloc(gsl_interp_cspline, N);

    gsl_spline_init(spline, xx, yy, N);

    double j;
    //zapis splajnu do pliku
    ofstream myfile;
    myfile.open("wynik.txt");
    for (double i = xx[0]; i < xx[N - 1]; i += 0.01)
    {
        j = gsl_spline_eval(spline, i, acc);
        printf("%g %g\n", i, j);
        myfile << i << fixed << setprecision(5) << " " << j << endl;
    }
    myfile.close();

    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
}