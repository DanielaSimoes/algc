#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void WriteMatrix (PtMatrix);

int main (void)
{
    PtMatrix mat1 = NULL, mat2 = NULL, mat3 = NULL;
    char filename[21]; unsigned int nl, nc, l, c; int st; double elem;

    system ("clear");
    printf ("\nLer matriz do ficheiro - Read matrix from a text file\n");
    do
    {
        printf ("Nome do ficheiro (Filename) -> ");
        st = scanf ("%20[^\n]", filename);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (st == 0);
    mat1 = MatrixCreateFile (filename);
    MatrixSize (mat1, &nl, &nc);

    printf ("\nMatriz lida do ficheiro %s com %d linhas e %d colunas\n", filename, nl, nc);
    printf ("\nMatrix acquired from text file %s with %d lines e %d columns\n", filename, nl, nc);
    WriteMatrix (mat1);

    printf ("\nLer matriz do teclado - Read matrix from keyboard\n");
    do
    {
        printf ("Número de linhas da matriz (number of lines)? "); scanf ("%d", &nl);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (nl <= 0) ;

    do
    {
        printf ("Número de colunas da matriz (number of columns)? "); scanf ("%d", &nc);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (nc <= 0) ;

    mat2 = MatrixCreate (nl, nc);

    for (l = 1; l <= nl; l++)
        for (c = 1; c <= nc; c++)
        {
            do
            {
                printf("Elemento (Element)[%d,%d] = ", l, c);
                st = scanf ("%lf", &elem);
                scanf ("%*[^\n]"); scanf ("%*c");
            } while (st == 0);
            MatrixModifyElement (mat2, l, c, elem);
        }

    printf ("\nMatriz lida do teclado - Matrix acquired from keyboard\n");
    WriteMatrix (mat2);

    printf ("\nEscrever matriz no ficheiro - Storing the matrix in a text file\n");
    do
    {
        printf ("Nome do ficheiro (Filename) -> ");
        st = scanf ("%20[^\n]", filename);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (st == 0);
    MatrixStoreFile (mat2, filename);

    mat3 = MatrixTranspose (mat2);
    printf ("\nMatriz transposta da matriz lida do telado - Transpose matrix read drom keyboard\n");
    WriteMatrix (mat3);

    MatrixDestroy (&mat3);
    mat3 = MatrixAddition (mat1, mat2);
    printf ("\nMatriz soma - Sum matrix\n");
    WriteMatrix (mat3);

    MatrixDestroy (&mat3);
    mat3 = MatrixSubtraction (mat1, mat2);
    printf ("\nMatriz diferenca - Difference matrix\n");
    WriteMatrix (mat3);


    MatrixDestroy (&mat3);
    mat3 = MatrixMultiplication (mat1, mat2);
    printf ("\nMatriz produto - Product matrix\n");
    WriteMatrix (mat3);

    printf ("\nDestruir as matrizes - Releasing the matrixes\n");
    MatrixDestroy (&mat1);
    MatrixDestroy (&mat2);
    MatrixDestroy (&mat3);

    WriteMatrix (mat3);

    return 0;
}

void WriteMatrix (PtMatrix pmat)
{
    unsigned int l, c, nl, nc;

    if (pmat == NULL) return;

    MatrixSize (pmat, &nl, &nc);

    for (l = 1; l <= nl; l++)
    {
        for (c = 1; c <= nc; c++)
            printf ("%6.1f ", MatrixObserveElement (pmat, l, c));
        printf ("\n");
    }
}