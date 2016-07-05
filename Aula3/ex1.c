#include <stdio.h>
#include <stdlib.h>

/* alusão da função que implementa o algoritmo pretendido */
/* allusion to the function that implements the algorithm */
int VerifyDifferences (int [], int);

/* variável global para contar as operações aritméticas executadas pelo algoritmo */
/* global variable for counting the arithmetic operations executed by the algorithm */
int Count = 0;

int main (void)
{
    /* declaração dos arrays de teste - usar o pretendido para cada execução */
    /* declaration of the test arrays - use each one for each execution */

    /* int Array[] = { 1, 3, 5, 7, 9, 11, 20, 25, 27, 29 }; */
    /* int Array[] = { 1, 3, 6, 9, 11, 13, 20, 25, 27, 29 }; */
    /* int Array[] = { 1, 3, 6, 10, 11, 13, 20, 25, 27, 29 }; */
    /* int Array[] = { 1, 3, 6, 10, 15, 17, 20, 25, 27, 29 }; */
    /* int Array[] = { 1, 3, 6, 10, 15, 21, 22, 25, 27, 29 }; */
    /* int Array[] = { 1, 3, 6, 10, 15, 21, 28, 30, 37, 39 }; */
    /* int Array[] = { 1, 3, 6, 10, 15, 21, 28, 36, 39, 49 }; */
    /* int Array[] = { 1, 3, 6, 10, 15, 21, 28, 36, 45, 49 }; */
    /* int Array[] = { 1, 3, 6, 10, 15, 21, 28, 36, 45, 55 }; */
    int Array[] = { 1, 3};

    int NElem = sizeof (Array) / sizeof (int); int Result;

    /* invocação do algoritmo pretendido */
    /* algorithm invocation */
    Result = VerifyDifferences (Array, NElem);

    /* apresentação do resultado e do número de operações aritméticas executadas pelo algoritmo */
    /* presenting the result and the number of arithmetic operations executed by the algorithm */
    if (Result) fprintf (stdout, "Verifica ");
    else fprintf (stdout, "Nao verifica ");

    fprintf (stdout, "e executou %10d operacoes aritmeticas\n", Count);

    exit (EXIT_SUCCESS);
}

/* implementação do algoritmo pretendido */
/* acrescentar a contagem das operações aritméticas executadas pelo algoritmo usando a variável global */

/* implementation of the pretended algorithm */
/* do not forget to count the arithmetic operations using the global variable */


int VerifyDifferences (int array[], int n)
{
    if(n<=2) return 0;
    int first = array[1] - array[0];
    Count = 1;
    int second = 0;
    for (int i = 1; i < n-1 ; i++) {
        Count = Count + 2;
        second = array[i+1] - array[i];
        if (second != (first+i))
            return 0;
    }
    return 1;
}





