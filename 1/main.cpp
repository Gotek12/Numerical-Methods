/*
 * @Author: Wojciech Ladyga 
 * @Date: 2018-11-11
 * @Description: Cholesky Decomposition
 */
#include <iostream>
#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <iomanip>
using namespace std;

const int N = 7; //wielkosc naszej macierzy
//wartosci tworzace wektory
const int a = 1;
const int b = 4;

//Tridiagonal System
//https://www.gnu.org/software/gsl/doc/html/linalg.html#tridiagonal-systems
//Vectors
//https://www.gnu.org/software/gsl/doc/html/vectors.html#vector-allocation

void choleskyTridiagonal()
{
    //alokacja pamieci vektorow tworzacych diagonale
    gsl_vector *mainD = gsl_vector_alloc(N); //glwna diagonala
    //diagonala gorna(diagonala nad glowna) i dolna diagonala(diagonala pod glowna diagonala)
    //tworzymy jeden wektor gdyż wektory są jedakowe
    gsl_vector *upperLowerD = gsl_vector_alloc(N - 1); //gorna
    //vektor wyrazow wolnych
    gsl_vector *spare = gsl_vector_alloc(N);
    //vector przechowujący wyniki
    gsl_vector *result = gsl_vector_alloc(N);

    //wrzucanie wartosci do wektorow
    for (double i = 0; i < N; i++)
    {
        gsl_vector_set(mainD, i, 4.0);
        gsl_vector_set(spare, i, i + 1.0);
       if (i != 6)
        {
            gsl_vector_set(upperLowerD, i, 1.0);
        }
    }

    //metoda rozwiązująca macierze 3-diagonalne symetryczne za pomocą faktoryzacji Choleskiego
    gsl_linalg_solve_symm_tridiag(mainD, upperLowerD, spare, result);
    
    //wynik
    for (int i = 0; i < N; i++)
    {	
	//ustawienie precyzji wypisywania 
        cout << "x" << i << " = " << setprecision(5) << fixed << gsl_vector_get(result, i) << endl;
    }
    //https://www.wolframalpha.com/input/?i=%7B(4,1,0,0,0,0,0),(1,4,1,0,0,0,0),(0,+1,4,1,0,0,0),(0,+0,+1,4,1,0,0),(0,+0,+0,+1,4,1,0),+(0,+0,+0,+0,+1,4,1),+(0,+0,+0,+0,+0,+1,4)%7D*(a,b,c,d,e,f,g)%3D(1,2,3,4,5,6,7)

    //czyszczenie przydzielonej pamięci vektorom aby pozbyć się przeciekow pamieci i przyspieszyc dzialanie programu
    gsl_vector_free(mainD);
    gsl_vector_free(upperLowerD);
    gsl_vector_free(spare);
    gsl_vector_free(result);
}

int main()
{
    choleskyTridiagonal();
    return 0;
}
