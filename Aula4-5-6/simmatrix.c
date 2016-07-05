/*******************************************************************************

 Programa gráfico de simulação da funcionalidade do TDA MATRIX


 Autor : António Manuel Adrego da Rocha    Data : Março de 2016

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "matrix.h"  /* Ficheiro de interface do tipo de dados */

#define MAX_MATRIXES 19
#define MAX_OPTIONS 16

void Menu (void);
void ReadOption (int *);
void ReadMatrixIndex (int *, char *);
int ActiveMatrix (PtMatrix *, int);
int NotActiveMatrix (PtMatrix *, int);
void ReadFilename (char *);
void ReadMatrixSize (unsigned int *, unsigned int *);
void WriteErrorMessage (char *);
void WriteMessageResult (char *, double);
PtMatrix ReadMatrix (int, int);
void WriteMatrix (PtMatrix *, int);
void ChangeMatrix (PtMatrix);
double ReadValue (void);
unsigned int ReadRow (char *, unsigned int);
unsigned int ReadColumn (char *, unsigned int);

int main (void)
{
    PtMatrix MatrixArray[MAX_MATRIXES];
    int Option, l, Matrix1, Matrix2, Matrix3, Equals, Sym;
    unsigned int NL, NC, L, C;
    char FileName[21]; double Value;

    for (l = 0; l < MAX_MATRIXES; l++) MatrixArray[l] = NULL;

    do
    {

        /* limpar o ecran e apresentar menu */
        Menu ();

        /* limpar o erro entretanto ocorrido */
        MatrixClearError ();

        /* apresentar as matrizes activas */
        for (l = 0; l < MAX_MATRIXES; l++)
            if (MatrixArray[l] != NULL)
            {
                MatrixSize (MatrixArray[l], &NL, &NC);
                printf ("\e[1m\e[%d;47f Matriz %d x %d", 5+l, NL, NC);
                printf ("\e[0m");
            }

        /* ler opcao do utilizador */
        ReadOption (&Option);

        switch (Option)
        {
            case 1 :  ReadMatrixIndex (&Matrix1, "matriz");
                if (ActiveMatrix (MatrixArray, Matrix1)) break;
                ReadMatrixSize (&NL, &NC);
                MatrixArray[Matrix1] = ReadMatrix (NL, NC);
                if (MatrixError ()) WriteErrorMessage ("A criacao");
                break;

            case 2 :  ReadMatrixIndex (&Matrix1, "matriz");
                if (ActiveMatrix (MatrixArray, Matrix1)) break;
                ReadFilename (FileName);
                MatrixArray[Matrix1] = MatrixCreateFile (FileName);
                if (MatrixError ()) WriteErrorMessage ("A leitura");
                break;

            case 3 :  ReadMatrixIndex (&Matrix1, "matriz origem");
                do
                {
                    ReadMatrixIndex (&Matrix2, "matriz destino");
                } while (Matrix2 == Matrix1);
                if (ActiveMatrix (MatrixArray, Matrix2)) break;
                MatrixArray[Matrix2] = MatrixTranspose (MatrixArray[Matrix1]);
                if (MatrixError ()) WriteErrorMessage ("A transposicao");
                break;

            case 4 :  ReadMatrixIndex (&Matrix1, "primeira matriz");
                ReadMatrixIndex (&Matrix2, "segunda matriz");
                do
                {
                    ReadMatrixIndex (&Matrix3, "matriz soma");
                } while (Matrix3 == Matrix1 || Matrix3 == Matrix2);
                if (ActiveMatrix (MatrixArray, Matrix3)) break;
                MatrixArray[Matrix3] = MatrixAddition (MatrixArray[Matrix1], MatrixArray[Matrix2]);
                if (MatrixError ()) WriteErrorMessage ("A soma");
                break;

            case 5 :  ReadMatrixIndex (&Matrix1, "primeira matriz");
                ReadMatrixIndex (&Matrix2, "segunda matriz");
                do
                {
                    ReadMatrixIndex (&Matrix3, "matriz diferenca");
                } while (Matrix3 == Matrix1 || Matrix3 == Matrix2);
                if (ActiveMatrix (MatrixArray, Matrix3)) break;
                MatrixArray[Matrix3] = MatrixSubtraction (MatrixArray[Matrix1], MatrixArray[Matrix2]);
                if (MatrixError ()) WriteErrorMessage ("A diferenca");
                break;

            case 6 :  ReadMatrixIndex (&Matrix1, "primeira matriz");
                ReadMatrixIndex (&Matrix2, "segunda matriz");
                do
                {
                    ReadMatrixIndex (&Matrix3, "matriz produto");
                } while (Matrix3 == Matrix1 || Matrix3 == Matrix2);
                if (ActiveMatrix (MatrixArray, Matrix3)) break;
                MatrixArray[Matrix3] = MatrixMultiplication (MatrixArray[Matrix1], MatrixArray[Matrix2]);
                if (MatrixError ()) WriteErrorMessage ("A multiplicacao");
                break;

            case 7 :  ReadMatrixIndex (&Matrix1, "matriz");
                Value = MatrixDeterminant (MatrixArray[Matrix1]);
                if (MatrixError ()) WriteErrorMessage ("O calculo do determinante");
                else WriteMessageResult ("O determinante e igual a", Value);
                break;

            case 8 :  ReadMatrixIndex (&Matrix1, "primeira matriz");
                ReadMatrixIndex (&Matrix2, "segunda matriz");
                Equals = MatrixEquals (MatrixArray[Matrix1], MatrixArray[Matrix2]);
                if (MatrixError ()) WriteErrorMessage ("A comparacao");
                else
                {
                    if (Equals) printf("\e[31;1f| \e[1mAs matrizes %d e %d sao iguais", Matrix1, Matrix2);
                    else printf("\e[31;1f| \e[1mAs matrizes %d e %d nao sao iguais", Matrix1, Matrix2);
                    printf("\e[0m\e[32;1f| Prima uma tecla para continuar ");
                    scanf ("%*[^\n]"); scanf ("%*c");
                }
                break;

            case 9 :  ReadMatrixIndex (&Matrix1, "matriz origem");
                if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                do
                {
                    ReadMatrixIndex (&Matrix2, "matriz destino");
                } while (Matrix2 == Matrix1);
                if (ActiveMatrix (MatrixArray, Matrix2)) break;
                MatrixArray[Matrix2] = MatrixCopy (MatrixArray[Matrix1]);
                if (MatrixError ()) WriteErrorMessage ("A copia");
                break;

            case 10 : ReadMatrixIndex (&Matrix1, "matriz");
                if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                ReadFilename (FileName);
                MatrixStoreFile (MatrixArray[Matrix1], FileName);
                if (MatrixError ()) WriteErrorMessage ("O armazenamento");
                break;

            case 11 : ReadMatrixIndex (&Matrix1, "matriz");
                if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                ChangeMatrix (MatrixArray[Matrix1]);
                break;

            case 12 : ReadMatrixIndex (&Matrix1, "matriz");
                if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                WriteMatrix (MatrixArray, Matrix1);
                printf("\e[1m\e[31;1f| Matriz %d                     ", Matrix1);
                printf("\e[0m\e[32;1f| Prima uma tecla para continuar ");
                scanf ("%*[^\n]"); scanf ("%*c");
                break;

            case 13 : ReadMatrixIndex (&Matrix1, "matriz");
                if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                MatrixDestroy (&MatrixArray[Matrix1]);
                if (MatrixError ()) WriteErrorMessage ("A eliminacao");
                break;

            case 14 : ReadMatrixIndex (&Matrix1, "matriz origem");
                if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                do
                {
                    ReadMatrixIndex (&Matrix2, "matriz destino");
                } while (Matrix2 == Matrix1);
                if (ActiveMatrix (MatrixArray, Matrix2)) break;
                Value = ReadValue ();
                MatrixArray[Matrix2] = MatrixMultByScalar (MatrixArray[Matrix1], Value);
                if (MatrixError ()) WriteErrorMessage ("A multiplicacao por escalar");
                break;

            case 15 : ReadMatrixIndex (&Matrix1, "matriz");
                if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                Sym = MatrixIsSymmetrical (MatrixArray[Matrix1]);
                if (MatrixError ()) WriteErrorMessage ("A verificacao de simetrica");
                else
                {
                    if (Sym) printf("\e[31;1f| \e[1mA matriz %d e simetrica", Matrix1);
                    else printf("\e[31;1f| \e[1mA matriz %d nao e simetrica", Matrix1);
                    printf("\e[0m\e[32;1f| Prima uma tecla para continuar ");
                    scanf ("%*[^\n]"); scanf ("%*c");
                }
                break;

            case 16 : ReadMatrixIndex (&Matrix1, "matriz origem");
                if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                MatrixSize (MatrixArray[Matrix1], &NL, &NC);
                do
                {
                    ReadMatrixIndex (&Matrix2, "matriz destino");
                } while (Matrix2 == Matrix1);
                if (ActiveMatrix (MatrixArray, Matrix2)) break;
                L = ReadRow ("a eliminar", NL);
                C = ReadColumn ("a eliminar", NC);
                MatrixArray[Matrix2] = MatrixSubMatrix (MatrixArray[Matrix1], L, C);
                if (MatrixError ()) WriteErrorMessage ("A criacao de submatriz");
                break;
        }

    } while (Option != 0);

    for (l = 0; l < MAX_MATRIXES; l++)
        if (MatrixArray[l] != NULL) MatrixDestroy (&MatrixArray[l]);

    printf ("\e[34;1f");

    return 0;
}

void Menu (void)
{
    system ("clear");

    printf("\e[2;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\e[3;1f|                                  Programa Grafico Para Simular Operacoes Sobre Matrizes                                  |\n");
    printf("\e[4;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\e[5;1f|  1 - Ler uma matriz (teclado)  | Matriz  0 =                |                                                            |\n");
    printf("\e[6;1f|  2 - Ler uma matriz (ficheiro) | Matriz  1 =                |                                                            |\n");
    printf("\e[7;1f|  3 - Transpor uma matriz       | Matriz  2 =                |                                                            |\n");
    printf("\e[8;1f|  4 - Somar matrizes            | Matriz  3 =                |                                                            |\n");
    printf("\e[9;1f|  5 - Subtrair matrizes         | Matriz  4 =                |                                                            |\n");
    printf("\e[10;1f|  6 - Multiplicar matrizes      | Matriz  5 =                |                                                            |\n");
    printf("\e[11;1f|  7 - Calcular determinante     | Matriz  6 =                |                                                            |\n");
    printf("\e[12;1f|  8 - Comparar matrizes         | Matriz  7 =                |                                                            |\n");
    printf("\e[13;1f|  9 - Copiar uma matriz         | Matriz  8 =                |                                                            |\n");
    printf("\e[14;1f| 10 - Armazenar uma matriz      | Matriz  9 =                |                                                            |\n");
    printf("\e[15;1f| 11 - Alterar uma matriz        | Matriz 10 =                |                                                            |\n");
    printf("\e[16;1f| 12 - Mostrar uma matriz        | Matriz 11 =                |                                                            |\n");
    printf("\e[17;1f| 13 - Apagar uma matriz         | Matriz 12 =                |                                                            |\n");
    printf("\e[18;1f| 14 - Multiplicar por escalar   | Matriz 13 =                |                                                            |\n");
    printf("\e[19;1f| 15 - Verificar simetrica       | Matriz 14 =                |                                                            |\n");
    printf("\e[20;1f| 16 - Criar submatriz           | Matriz 15 =                |                                                            |\n");
    printf("\e[21;1f|  0 - Terminar o programa       | Matriz 16 =                |                                                            |\n");
    printf("\e[22;1f|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| Matriz 17 =                |                                                            |\n");
    printf("\e[23;1f| Opcao ->                       | Matriz 18 =                |                                                            |\n");
    printf("\e[24;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\e[25;1f|                                               Janela de Aquisicao de Dados                                               |\n");
    printf("\e[26;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\e[27;1f|                                                                                                                          |\n");
    printf("\e[28;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\e[29;1f|                                        Janela de Mensagens de Erro e de Resultados                                       |\n");
    printf("\e[30;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\e[31;1f|                                                                                                                          |\n");
    printf("\e[32;1f|                                                                                                                          |\n");
    printf("\e[33;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void ReadOption (int *poption)
{
    do
    {
        printf("\e[23;1f| Opcao ->                       |");
        printf("\e[23;12f"); scanf ("%d", poption);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (*poption < 0 || *poption > MAX_OPTIONS);
}

void ReadMatrixIndex (int *pnm, char *pmsg)
{
    int MsgLen = strlen (pmsg);

    do
    {
        *pnm = -1;
        printf("\e[27;1f| Indice da %s ->                               ", pmsg);
        printf("\e[27;%df", 17+MsgLen); scanf ("%d", pnm);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (*pnm < 0 || *pnm >= MAX_MATRIXES);
}

int ActiveMatrix (PtMatrix pmatarray[], int pnmat)
{
    char Character;

    if (pmatarray[pnmat] != NULL)
    {
        do
        {
            printf("\e[1m\e[31;1f| A matriz %d ja existe!                     ", pnmat);
            printf("\e[0m\e[32;1f| Deseja apaga-la (s/n)? ");
            scanf ("%c", &Character); Character = tolower (Character);
            scanf ("%*[^\n]"); scanf ("%*c");
        } while (Character != 'n' && Character != 's');

        if (Character == 's') { MatrixDestroy (&pmatarray[pnmat]); return 0; }
        else  return 1;
    }
    else return 0;
}

int NotActiveMatrix (PtMatrix pmatarray[], int pnmat)
{
    if (pmatarray[pnmat] == NULL)
    {
        printf("\e[1m\e[31;1f| A matriz %d nao existe!                     ", pnmat);
        printf("\e[0m\e[32;1f| Prima uma tecla para continuar ");
        scanf ("%*[^\n]"); scanf ("%*c");
        return 1;
    }
    else return 0;
}

void ReadMatrixSize (unsigned int *pnl, unsigned int *pnc)
{
    do
    {
        *pnl = 0;
        printf("\e[27;1f| Nº de linhas da matriz ->                               ");
        printf("\e[27;29f"); scanf ("%d", pnl);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (*pnl < 1 || *pnl > 10);

    do
    {
        *pnc = 0;
        printf("\e[27;1f| Nº de colunas da matriz ->                              ");
        printf("\e[27;30f"); scanf ("%d", pnc);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (*pnc < 1 || *pnc > 10);
}

void ReadFilename (char *pfname)
{
    int Status;

    do
    {
        printf("\e[27;1f| Nome do ficheiro ->                               ");
        printf("\e[27;23f"); Status = scanf ("%20[^\n]", pfname);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (Status == 0);
}

void WriteErrorMessage (char *pmsg)
{
    printf("\e[31;1f| %s de matrizes nao foi efectuada devido a -> \e[1m%s", pmsg, MatrixErrorMessage ());
    printf("\e[0m\e[32;1f| Prima uma tecla para continuar ");
    scanf ("%*[^\n]"); scanf ("%*c");
}

void WriteMessageResult (char *pmsg, double pval)
{
    printf("\e[1m\e[31;1f| %s \e[1m%f", pmsg, pval);
    printf("\e[0m\e[32;1f| Prima uma tecla para continuar ");
    scanf ("%*[^\n]"); scanf ("%*c");
}

PtMatrix ReadMatrix (int pnl, int pnc)
{
    PtMatrix Mat; unsigned int L, C; int Status; double Element;

    /* cria a matriz nula */
    if ((Mat = MatrixCreate (pnl, pnc)) == NULL) return NULL;

    /* leitura das componentes da matriz do teclado */
    for (L = 1; L <= pnl; L++)
    {
        for (C = 1; C <= pnc; C++)
        {
            do
            {
                printf("\e[27;1f| Matriz[%d,%d]?                                          ", L, C);
                printf("\e[27;16f"); Status = scanf ("%lf", &Element);
                scanf ("%*[^\n]"); scanf ("%*c");
            } while (Status == 0);
            MatrixModifyElement (Mat, L, C, Element);
        }
    }

    return Mat;  /* devolve a matriz criada */
}

void WriteMatrix (PtMatrix pmatarray[], int pnm)
{
    unsigned int L, C, NL, NC;

    MatrixSize (pmatarray[pnm], &NL, &NC);

    printf("\e[1m");
    for (L = 1; L <= NL; L++)
    {
        printf("\e[%d;65f ", 6+L);
        for (C = 1; C <= NC; C++)
            printf ("%6.1f ", MatrixObserveElement (pmatarray[pnm], L, C));
    }
    printf("\e[0m");
}

void ChangeMatrix (PtMatrix pmat)
{
    unsigned int L, C, NL, NC; char Character; int Status; double Element;

    MatrixSize (pmat, &NL, &NC);

    do
    {
        do
        {
            L = -1;
            printf("\e[27;1f| Nº da linha do elemento da matriz ->                    ");
            printf("\e[27;40f"); scanf ("%d", &L);
            scanf ("%*[^\n]"); scanf ("%*c");
        } while (L < 1 || L > NL);

        do
        {
            C = -1;
            printf("\e[27;1f| Nº da coluna do elemento da matriz ->                   ");
            printf("\e[27;41f"); scanf ("%d", &C);
            scanf ("%*[^\n]"); scanf ("%*c");
        } while (C < 1 || C > NC);

        do
        {
            printf("\e[27;1f| Matriz[%d,%d]?                                          ", L, C);
            printf("\e[27;16f"); Status = scanf ("%lf", &Element);
            scanf ("%*[^\n]"); scanf ("%*c");
        } while (Status == 0);

        MatrixModifyElement (pmat, L, C, Element);

        do
        {
            printf("\e[27;1f| Deseja alterar mais algum elemento da matriz (s/n)?     ");
            printf("\e[27;55f"); scanf ("%c", &Character); Character = tolower (Character);
            scanf ("%*[^\n]"); scanf ("%*c");
        } while (Character != 'n' && Character != 's');
    } while (Character == 's');
}

double ReadValue (void)
{
    int Status; double Value;

    do
    {
        printf("\e[27;1f| Escalar a multiplicar ->                            ");
        printf("\e[27;28f"); Status = scanf ("%lf", &Value);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (Status == 0);

    return Value;
}

unsigned int ReadRow (char *pmsg, unsigned int psize)
{
    unsigned int Row = 0;

    do
    {
        printf("\e[27;1f| Nº da linha (%s) da matriz ->                    ", pmsg);
        printf("\e[27;41f"); scanf ("%d", &Row);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (Row < 1 || Row > psize);

    return Row;
}

unsigned int ReadColumn (char *pmsg, unsigned int psize)
{
    unsigned int Col = 0;

    do
    {
        printf("\e[27;1f| Nº da coluna (%s) da matriz ->                   ", pmsg);
        printf("\e[27;42f"); scanf ("%d", &Col);
        scanf ("%*[^\n]"); scanf ("%*c");
    } while (Col < 1 || Col > psize);

    return Col;
}