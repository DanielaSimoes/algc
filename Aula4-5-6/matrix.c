/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstracto MATRIZ (matrix.c).
 A estrutura de dados de suporte da matriz é uma estrutura, constituída pelo
 campo NL para armazenar o número de linhas da matriz, o campo NC para armazenar
 o número de colunas da matriz e o campo de tipo ponteiro para ponteiro Matrix
 para armazenar os seus NLxNC elementos reais, que vão ser armazenados numa
 sequência bidimensional atribuída dinamicamente.

 Nome :                                                     NMec:

 Implementation file of the abstract data type MATRIX (matrix.c). The data
 structure to store the matrix is composed with the integer field NL for keeping
 the matrix's number of lines, the integer field NC for keeping the matrix's number
 of columns and the pointer field Matrix, that represents the allocated bi-dimensional
 array in dynamic memory, for storing the matrix's NLxNC real elements.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"  /* Ficheiro de interface do TDA - ADT Interface file */

/************* Definição da Estrutura de Dados Interna da MATRIZ **************/

struct matrix {
    unsigned int NL;
    /* numero de linhas da matriz - matrix's number of lines */
    unsigned int NC;
    /* numero de colunas da matriz - matrix's number of columns */
    double **Matrix;  /* ponteiro para a matriz a ser alocada - pointer to matrix's elements */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;
/* inicialização do erro */

static char *ErrorMessages[] = {
        "sem erro - Without error",
        "matriz(es) inexistente(s) - Matrix(Matrices) do not exist",
        "memoria esgotada - Out of memory",
        "ficheiro inexistente - File does not exist",
        "dimensao errada - Wrong size",
        "elemento inexistente na matriz - Element does not exist",
        "matrizes com dimensoes diferentes - Matrices with different sizes",
        "matrizes nao encadeadas - Matrices not chained",
        "ponteiro nulo - Null pointer",
        "matriz nao quadrada - Matrix not square",
        "linha inexistente - Line does not exist",
        "coluna inexistente - Column does not exist"
};

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alusão às Funções Auxiliares ************************/

static int EqualSizeMatrices(PtMatrix, PtMatrix);

static int ChainedMatrices(PtMatrix, PtMatrix);

static double Determinant(double *, unsigned int, unsigned int);

/*************************** Definição das Funções ****************************/

void MatrixClearError(void) {
    Error = OK;
}

int MatrixError(void) {
    return Error;
}

char *MatrixErrorMessage(void) {
    if (Error < N) return ErrorMessages[Error];
    else return AbnormalErrorMessage;  /* não há mensagem de erro - no error message */
}

PtMatrix MatrixCreate(unsigned int pnl, unsigned int pnc) {
    PtMatrix Matrix;
    unsigned int l, i;

    if(pnl == 0 || pnc == 0){
        Error = BAD_SIZE;
        return NULL;
    }

    if ((Matrix = (PtMatrix) malloc(sizeof(struct matrix))) == NULL) {
        Error = NO_MEM;
        return NULL;
    }

    /* Alocar os arrays */
    if ((Matrix->Matrix = (double **) calloc(pnl, sizeof(double))) == NULL) {
        free(Matrix);
        Error = NO_MEM;
        return NULL;
    }

    for (l = 0; l < pnl; ++l) {
        if ((Matrix->Matrix[l] = (double *) calloc(pnc, sizeof(double))) == NULL) {
            /* Libertar a memoria */
            for (i = 0; i < l; ++i) free(Matrix->Matrix[i]);

            free(Matrix->Matrix);
            free(Matrix);
            Error = NO_MEM;
            return NULL;

        }
    }

    Matrix->NL = pnl;
    Matrix->NC = pnc;
    Error = OK;

    return Matrix;
}

void MatrixDestroy(PtMatrix *pmat) {
    if (*pmat == NULL) {
        Error = NO_MATRIX;
        return;
    }

    for (int i = 0; i < (*pmat)->NL; ++i) {
        free((*pmat)->Matrix[i]);
    }
    free((*pmat)->Matrix);
    free(*pmat);
    *pmat = NULL;

    Error = OK;
}

PtMatrix MatrixCopy(PtMatrix pmat) {
    PtMatrix Copy;

    if (pmat == NULL) {
        Error = NO_MATRIX;
        return NULL;
    }

    if ((Copy = MatrixCreate(pmat->NL, pmat->NC)) == NULL) {
        Error = NO_MEM;
        free(Copy);
        return NULL;
    }

    for (int i = 0; i < pmat->NL; ++i) {
        for (int j = 0; j < pmat->NC; ++j) {
            Copy->Matrix[i][j] = pmat->Matrix[i][j];
        }
    }

    Error = OK;

    return Copy;
}

void MatrixSize(PtMatrix pmat, unsigned int *pnl, unsigned int *pnc) {
    /* verifica se a matriz existe - verifies if matrix exist */
    if (pmat == NULL) {
        Error = NO_MATRIX;
        *pnl = *pnc = 0;
    }
    else {
        Error = OK;
        *pnl = pmat->NL;
        *pnc = pmat->NC;
    }
}

void MatrixModifyElement(PtMatrix pmat, unsigned int pl, unsigned int pc, double pval) {
    /* verifica se a matriz existe - verifies if matrix exist */
    if (pmat == NULL) {
        Error = NO_MATRIX;
        return;
    }

    /* validação do elemento pretendido - validating the element position */
    pl--;
    if (pl >= pmat->NL) {
        Error = BAD_ROW;
        return;
    }
    pc--;
    if (pc >= pmat->NC) {
        Error = BAD_COLUMN;
        return;
    }

    Error = OK;
    /* escrita do valor na componente pretendida da matriz - storing the new value in the element */
    pmat->Matrix[pl][pc] = pval;
}

double MatrixObserveElement(PtMatrix pmat, unsigned int pl, unsigned int pc) {
    /* verifica se a matriz existe - verifies if matrix exist */
    if (pmat == NULL) {
        Error = NO_MATRIX;
        return 0.0;
    }

    /* validação do elemento pretendido - validating the element position */
    pl--;
    if (pl >= pmat->NL) {
        Error = BAD_ROW;
        return 0.0;
    }
    pc--;
    if (pc >= pmat->NC) {
        Error = BAD_COLUMN;
        return 0.0;
    }


    Error = OK;
    /* devolve o valor armazenado na componente pretendida da matriz - returning the element value */
    return pmat->Matrix[pl][pc];
}

PtMatrix MatrixTranspose(PtMatrix pmat) {
    PtMatrix Transpose;

    if (pmat == NULL) {
        Error = NO_MATRIX;
        return NULL;
    }

    if ((Transpose = MatrixCreate(pmat->NC, pmat->NL)) == NULL) {
        Error = NO_MEM;
        free(Transpose);
        return NULL;
    }

    for (int i = 0; i < pmat->NC; ++i) {
        for (int j = 0; j < pmat->NL; ++j) {
            Transpose->Matrix[i][j] = pmat->Matrix[j][i];
        }
    }

    Error = OK;
    return Transpose;
}

PtMatrix MatrixAddition(PtMatrix pmat1, PtMatrix pmat2) {
    if (pmat1 == NULL || pmat2 == NULL) {
        Error = NO_MATRIX;
        return NULL;
    }

    if (!EqualSizeMatrices(pmat1, pmat2)) {
        /* Erro já atribuído na função */
        return NULL;
    }

    PtMatrix Sum;

    if ((Sum = MatrixCreate(pmat1->NL, pmat1->NC)) == NULL) {
        Error = NO_MEM;
        free(Sum);
        return NULL;
    }

    for (int i = 0; i < pmat1->NL; ++i) {
        for (int j = 0; j < pmat1->NC; ++j) {
            Sum->Matrix[i][j] = (pmat1->Matrix[i][j] + pmat2->Matrix[i][j]);
        }
    }
    Error = OK;
    return Sum;
}

PtMatrix MatrixSubtraction(PtMatrix pmat1, PtMatrix pmat2) {
    if (!EqualSizeMatrices(pmat1, pmat2)) {
        /* Erro já atribuído na função */
        return NULL;
    }

    if ((pmat1->NC != pmat2->NC) || (pmat1->NL != pmat2->NL)) {
        Error = DIF_SIZE;
        return NULL;
    }

    PtMatrix Subtraction;

    if ((Subtraction = MatrixCreate(pmat1->NL, pmat1->NC)) == NULL) {
        Error = NO_MEM;
        free(Subtraction);
        return NULL;
    }

    for (int i = 0; i < pmat1->NL; ++i) {
        for (int j = 0; j < pmat1->NC; ++j) {
            Subtraction->Matrix[i][j] = (pmat1->Matrix[i][j] - pmat2->Matrix[i][j]);
        }
    }

    Error = OK;
    return Subtraction;
}

PtMatrix MatrixMultiplication(PtMatrix pmat1, PtMatrix pmat2) {
    if (pmat1 == NULL || pmat2 == NULL) {
        Error = NO_MATRIX;
        return NULL;
    }

    if (!ChainedMatrices(pmat1, pmat2)) {
        Error = NO_CHAINED;
        return NULL;
    }

    PtMatrix Multiplication;

    if ((Multiplication = MatrixCreate(pmat1->NL, pmat2->NC)) == NULL) {
        Error = NO_MEM;
        free(Multiplication);
        return NULL;
    }

    for (int i = 0; i < pmat1->NL; ++i) {
        for (int j = 0; j < pmat2->NC; ++j) {
            for (int k = 0; k < pmat2->NL; ++k) {
                Multiplication->Matrix[i][j] += pmat1->Matrix[i][k] * pmat2->Matrix[k][j];
            }
        }
    }

    return Multiplication;
}

PtMatrix MatrixMultByScalar(PtMatrix pmat, double pvalue) {
    if (pmat == NULL) {
        Error = NO_MATRIX;
        return NULL;
    }

    PtMatrix MultByScalar;

    if ((MultByScalar = MatrixCreate(pmat->NL, pmat->NC)) == NULL) {
        Error = NO_MEM;
        free(MultByScalar);
        return NULL;
    }

    for (int i = 0; i < pmat->NL; ++i) {
        for (int j = 0; j < pmat->NC; ++j) {
            MultByScalar->Matrix[i][j] += pmat->Matrix[i][j] * pvalue;
        }
    }
    Error = OK;
    return MultByScalar;
}

double MatrixDeterminant(PtMatrix pmat) {
    double determinant;

    if (pmat == NULL) {
        Error = NO_MATRIX;
        return 0;
    }

    /* validar se a matriz existe e é quadrada - verify if matrix exist and is square */
    if (!MatrixIsSquare(pmat)) {
        Error = NO_SQUARE;
        return 0;
    }

    double *array;

    /* preparar a invocação da função interna - prepare for invoking the internal function */
    if ((array = (double *) calloc(pmat->NC * pmat->NL, sizeof(double))) == NULL) {
        Error = NO_MEM;
        return 0;
    }


    int k = 0;

    for (int i = 0; i < pmat->NL; ++i) {
        for (int j = 0; j < pmat->NC; ++j) {
            array[k] = pmat->Matrix[i][j];
            if (k < sizeof(array)) k++;
        }
    }

    determinant = Determinant(array, pmat->NC, pmat->NL);
    Error = OK;

    /* libertar a memória dinâmica alocada e devolver o resultado - free the memory and return the result */
    return determinant;
}

int MatrixIsSquare(PtMatrix pmat) {
    if (pmat == NULL) {
        Error = NO_MATRIX;
        return 0;
    }

    Error = OK;
    return pmat->NL == pmat->NC;
}

int MatrixIsSymmetrical(PtMatrix pmat) {
    if (pmat == NULL) {
        Error = NO_MATRIX;
        return 0;
    }

    if (!MatrixIsSquare(pmat)) {
        Error = NO_SQUARE;
        return 0;
    }

    for (int i = 0; i < pmat->NL; ++i) {
        for (int j = 0; j < pmat->NC; ++j) {
            if (pmat->Matrix[i][j] != pmat->Matrix[j][i]) {
                return 0;
            }
        }

    }
    Error = OK;
    return 1;
}

int MatrixEquals(PtMatrix pmat1, PtMatrix pmat2) {
    unsigned int l, c;

    /* validação das matrizes - validating the existence of the two matrices */
    if (!EqualSizeMatrices(pmat1, pmat2)) return 0;

    Error = OK;
    /* comparação dos elementos das duas matrizes - comparing the respective elements */
    for (l = 0; l < pmat1->NL; l++)
        for (c = 0; c < pmat1->NC; c++)
            if (pmat1->Matrix[l][c] != pmat2->Matrix[l][c]) return 0;

    return 1;  /* as matrizes são iguais - the two matrices are equal */
}

PtMatrix MatrixSubMatrix(PtMatrix pmat, unsigned int pl, unsigned int pc) {
    if (pmat == NULL) {
        Error = NO_MATRIX;
        return 0;
    }

    if (pl > pmat->NL || pl < 1) {
        Error = BAD_ROW;
        return NULL;
    }

    if (pc > pmat->NC || pc < 1) {
        Error = BAD_COLUMN;
        return NULL;
    }

    PtMatrix New;

    if ((New = MatrixCreate(pmat->NL - 1, pmat->NC - 1)) == NULL) {
        return NULL;
    }

    int l = 0;
    int c = 0;
    for (int i = 0; i < pmat->NL; ++i) {
        for (int j = 0; j < pmat->NC; ++j) {
            if (i != pl - 1) {
                if (j != pc - 1) {
                    New->Matrix[l][c] = pmat->Matrix[i][j];
                    if (c < (New->NC-1)) {
                        c++;
                    } else if (l < (New->NL)) {
                        l++;
                        c=0;
                    }
                }
            }
        }
    }

    Error = OK;
    return New;
}

void MatrixStoreFile(PtMatrix pmat, char *pnomef) {
    FILE *PtF;
    unsigned int l, c;

    /* verifica se a matriz existe - verifies if matrix exists */
    if (pmat == NULL) {
        Error = NO_MATRIX;
        return;
    }

    /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
    if ((PtF = fopen(pnomef, "w")) == NULL) {
        Error = NO_FILE;
        return;
    }

    /* escrita da dimensão da matriz no ficheiro - writing the matrix's size */
    fprintf(PtF, "%d\t%d\n", pmat->NL, pmat->NC);

    /* escrita dos elementos da matriz no ficheiro - writing the matrix's elements */
    for (l = 0; l < pmat->NL; l++) {
        for (c = 0; c < pmat->NC; c++) fprintf(PtF, "%lf\t", pmat->Matrix[l][c]);
        fprintf(PtF, "\n");
    }

    Error = OK;
    fclose(PtF);  /* fecho do ficheiro - closing the text file */
}

PtMatrix MatrixCreateFile(char *pnomef) {
    PtMatrix Mat;
    FILE *PtF;
    unsigned int NL, NC, l, c;

    /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
    if ((PtF = fopen(pnomef, "r")) == NULL) {
        Error = NO_FILE;
        return NULL;
    }

    /* leitura da dimensão da matriz do ficheiro - reading the matrix's size from the text file */
    fscanf(PtF, "%d%d", &NL, &NC);
    if ((NL < 1) || (NC < 1)) {
        Error = BAD_SIZE;
        fclose(PtF);
        return NULL;
    }

    /* criação da matriz nula - creating an empty matrix */
    if ((Mat = MatrixCreate(NL, NC)) == NULL) {
        fclose(PtF);
        return NULL;
    }

    /* leitura dos elementos da matriz do ficheiro - reading the matrix's elements from the text file */
    for (l = 0; l < NL; l++) {
        for (c = 0; c < NC; c++) fscanf(PtF, "%lf", &Mat->Matrix[l][c]);
        fscanf(PtF, "%*[^\n]");
        fscanf(PtF, "%*c");
    }

    fclose(PtF);  /* fecho do ficheiro - closing the text file */
    return Mat;  /* devolve a matriz criada - returning the new matrix */
}

/*******************************************************************************
 Função auxiliar que verifica se as duas matrizes podem ser operadas (com excepção
 da operação de multiplicação), ou seja, se existem e se têm a mesma dimensão.
 Devolve 1 em caso afirmativo e 0 em caso contrário. Valores de erro: OK, NO_MATRIX
 ou DIF_SIZE.
*******************************************************************************/
static int EqualSizeMatrices(PtMatrix pmat1, PtMatrix pmat2) {
    /* verifica se as duas matrizes existem - verifies if the two matrices exist */
    if ((pmat1 == NULL) || (pmat2 == NULL)) {
        Error = NO_MATRIX;
        return 0;
    }

    /* verifica se a dimensão das duas matrizes é igual - verifies if they have the same size */
    if ((pmat1->NL != pmat2->NL) || (pmat1->NC != pmat2->NC)) {
        Error = DIF_SIZE;
        return 0;
    }

    Error = OK;
    return 1;  /* as duas matrizes existem e têm a mesma dimensão - they exist and have the same size */
}

/*******************************************************************************
 Função auxiliar que verifica se as duas matrizes podem ser multiplicadas, ou
 seja, se existem e se são encadeadas (o número de colunas da primeira é igual ao
 número de linhas da segunda). Devolve 1 em caso afirmativo e 0 em caso contrário.
 Valores de erro: OK, NO_MATRIX ou NO_CHAINED.

 Auxiliary function to verify if the two matrices can be multiplied, that is, if they
 exist and are chained (the number of columns of the first is equal to the number
 of lines of the second). Returns 1 in affirmative case and 0 otherwise. Error
 codes: OK, NO_MATRIX or DIF_SIZE.
*******************************************************************************/
static int ChainedMatrices(PtMatrix pmat1, PtMatrix pmat2) {
    /* verifica se as duas matrizes existem - verifies if the two matrices exist */
    if ((pmat1 == NULL) || (pmat2 == NULL)) {
        Error = NO_MATRIX;
        return 0;
    }

    /* verifica se as duas matrizes são encadeadas - verifies if they are chained */
    if (pmat1->NC != pmat2->NL) {
        Error = NO_CHAINED;
        return 0;
    }

    Error = OK;
    return 1;  /* as duas matrizes existem e são encadeadas - they exist and are chained */
}

/*******************************************************************************
 Função auxiliar que calcula o determinante de uma matriz quadrada usando o
 algoritmo de eliminação de Gauss. Transforma a matriz numa matriz triangular
 superior. Recebe um array unidimensional que armazena os elementos da matriz,
 linha a linha.

 Auxiliary function that calculates the determinant of a square matrix. It uses
 the Gauss elimination algorithm that transforma the matrix in a superior triangular
 matrix. It receives a one-dimension array that stores the matrix elements, line by line.
*******************************************************************************/
static double Determinant(double *pmatrix, unsigned int psize, unsigned int pn) {
    int AuxCol;
    unsigned int NC, NL, LC = pn - 1;
    double Elem;

    if (pn == 1) return *pmatrix;    /* condição de paragem - stop recursion condition */
    else {   /* procurar coluna com último elemento não nulo - search for column with last element not zero */
        AuxCol = LC;
        while (AuxCol >= 0 && *(pmatrix + LC * psize + AuxCol) == 0) AuxCol--;

        if (AuxCol >= 0)    /* se existir tal coluna - if such column exists */
        {
            if (AuxCol != LC)    /* se não for a última coluna - if it is not the last column */
                for (NL = 0; NL < pn; NL++)    /* trocar as colunas - change columns */
                {
                    Elem = *(pmatrix + NL * psize + LC);
                    *(pmatrix + NL * psize + LC) = *(pmatrix + NL * psize + AuxCol);
                    *(pmatrix + NL * psize + AuxCol) = -Elem;
                }

            /* dividir a última coluna pelo último elemento - divide the last column by the last element */
            for (NL = 0; NL < LC; NL++)
                *(pmatrix + NL * psize + LC) = *(pmatrix + NL * psize + LC) / *(pmatrix + LC * psize + LC);

            /* subtrair todas as colunas menos a última pela última coluna */
            /* multiplicada pelo último elemento da coluna a processar */
            /* process all other columns in order to eliminate the last element of the column */
            for (NC = 0; NC < LC; NC++)
                for (NL = 0; NL < LC; NL++)
                    *(pmatrix + NL * psize + NC) = *(pmatrix + NL * psize + NC) -
                                                   (*(pmatrix + NL * psize + LC) * *(pmatrix + LC * psize + NC));

            /* invocação recursiva para a matriz de dimensão N-1 */
            return *(pmatrix + LC * psize + LC) * Determinant(pmatrix, psize, pn - 1);
        }
        else return 0.0;
    }
}
