#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "abp.h"

int main (void)
{
    PtABPNode abp, node; int value, error, sum; unsigned int count; char op;

    system ("clear");
    abp = ABPCreate ();

    do
    {
        printf ("Inserir-Inserting/Remover-Removing/Terminar-Terminating-> ");
        scanf ("%c", &op);
        scanf ("%*[^\n]"); scanf ("%*c");
        op = toupper (op);
    } while (op != 'I' && op != 'R' && op != 'T');

    while (op != 'T')
    {
        printf ("Valor (Value) -> ");
        scanf ("%d", &value);
        scanf ("%*[^\n]"); scanf ("%*c");

        if (op == 'I')
        {
            ABPInsertRec (&abp, value);
            if ((error = ABPErrorCode ()) != OK) printf ("Erro a inserir (Error in inserting) -> %s\n", ABPErrorMessage ());
        }
        else	if (op == 'R')
        {
            ABPDeleteRec (&abp, value);
            if ((error = ABPErrorCode ()) != OK) printf ("Erro a remover (Error in removing) -> %s\n", ABPErrorMessage ());
        }
        else
        {
            printf ("Erro na operacao escolhida - Error on the chosen operation\n");
            error = 1;
        }

        if (!error)
        {
            printf ("--------------------------------------------------------------------------------------------\n");
            if (ABPEmpty (abp)) printf ("\nArvore vazia! - Empty tree!\n");
            else ABPDisplay (abp);
            printf ("--------------------------------------------------------------------------------------------\n");
        }

        printf ("Inserir-Inserting/Remover-Removing/Terminar-Terminating-> ");
        scanf ("%c", &op);
        scanf ("%*[^\n]"); scanf ("%*c");
        op = toupper (op);
    }

    printf ("--------------------------------------------------------------------------------------------\n");
    if (ABPEmpty (abp)) printf ("Arvore vazia! - Empty tree!\n");
    else
    {
        ABPDisplay (abp);
        printf ("--------------------------------------------------------------------------------------------\n");
        printf ("Numero de nos da arvore (number of nodes) = %d\n", ABPSize (abp));
        printf ("Altura da arvore (tree height) = %d\n", ABPHeight (abp));
    }
    printf ("--------------------------------------------------------------------------------------------\n");

    node = ABPMinRep (abp);
    if (ABPErrorCode ()) printf ("Menor elemento da arvore (minimum element) = %s\n", ABPErrorMessage ());
    else printf ("Menor elemento da arvore (minimum element) = %d\n", ABPElement (node));

    node = ABPMaxRep (abp);
    if (ABPErrorCode ()) printf ("Maior elemento da arvore (maximum element) = %s\n", ABPErrorMessage ());
    else printf ("Maior elemento da arvore (maximum element) = %d\n", ABPElement (node));

    sum = ABPTotalSum (abp);
    if (ABPErrorCode ()) printf ("Soma dos elementos da arvore (Soma of the elements) = %s\n", ABPErrorMessage ());
    else printf ("Soma dos elementos da arvore (sum of the elements) = %d\n", sum);


    count = ABPEvenCount (abp);
    if (ABPErrorCode ()) printf ("Contagem dos elementos pares da arvore (number of even elements) = %s\n", ABPErrorMessage ());
    else printf ("Contagem dos elementos pares da arvore (number of even elements) = %d\n", count);

    sum = ABPMultSum (abp, 5);
    if (ABPErrorCode ()) printf ("Soma dos elementos da arvore multiplos de 5 (sum of elements multiple of 5) = %s\n", ABPErrorMessage ());
    else printf ("Soma dos elementos da arvore multiplos de 5 (sum of elements multiple of 5) = %d\n", sum);

    count = ABPOddCount (abp);
    if (ABPErrorCode ()) printf ("Contagem dos elementos impares da arvore (number of odd elements) = %s\n", ABPErrorMessage ());
    else printf ("Contagem dos elementos impares da arvore (number of odd elements) = %d\n", count);

    printf ("--------------------------------------------------------------------------------------------\n");
    printf ("Arvore listada em ordem (inorder traversal) ");
    ABPInOrderRec (abp);
    printf ("\n");
    printf ("--------------------------------------------------------------------------------------------\n");

    sum = ABPEvenOrderSum (abp);
    if (ABPErrorCode ()) printf ("Soma dos elementos com numero de ordem par da arvore (sum of elements with even order number) = %s\n", ABPErrorMessage ());
    else printf ("Soma dos elementos com numero de ordem par da arvore (sum of elements with even order number) = %d\n", sum);

    printf ("--------------------------------------------------------------------------------------------\n");
    printf ("Elementos impares da arvore por ordem crescente (odd elements by increasing order) ");
    ABPOddPrint (abp);
    printf ("\n");
    printf ("--------------------------------------------------------------------------------------------\n");

    printf ("\n");

    ABPDestroy (&abp);

    return 0;
}
