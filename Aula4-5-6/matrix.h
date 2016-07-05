/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstracto MATRIX (matrix.h). A matriz é
 identificada pela sua dimensão, ou seja, pelo número de linhas NL e pelo número
 de colunas NC e armazena elementos reais. A implementação providencia um
 construtor para criar uma matriz nula. É da responsabilidade da aplicação,
 invocar o destrutor, para libertar a memória atribuída ao objecto. O módulo
 providencia um controlo centralizado de erro, disponibilizando uma função para
 obter o último erro ocorrido, uma função para obter uma mensagem de erro
 elucidativa e uma função para limpar o erro. Providencia também operações para
 armazenar e recuperar matrizes para ficheiros.

 Autor : António Manuel Adrego da Rocha    Data : Março de 2016

 Interface file of the abstract data type MATRIX (matrix.h). The matrix is defined
 by its size, that is, by its number of lines NL and its number of columns and stores
 real elements. The implementation provides a constructor for creating an empty
 matrix with the required size. The application has the responsibility of calling
 the destructor to release the dynamic memory allocated to the matrix. The data-type
 has a central control error mechanism, providing operations for obtaining the last
 error occurred, for obtaining the correspondent message and for cleaning the error.
 The data-type has also operations to store and retrieve matrices from text files.

*******************************************************************************/

#ifndef _MATRIX
#define _MATRIX

/***************** Definição do Tipo Ponteiro para uma Matriz *****************/

typedef struct matrix *PtMatrix;

/************************ Definição de Códigos de Erro ************************/

#define  OK           0  /* operação realizada com sucesso - operation with success */
#define  NO_MATRIX    1  /* a(s) matriz(es) não existe(m) - matrix(matrices) do not exist */
#define  NO_MEM       2  /* memória esgotada - out of memory */
#define  NO_FILE      3  /* o ficheiro não existe - file does not exist */
#define  BAD_SIZE     4  /* dimensão errada - wrong size */
#define  BAD_INDEX    5  /* elemento inexistente na matriz - element does not exist in the matrix */
#define  DIF_SIZE     6  /* matrizes com dimensões diferentes - matrices with different sizes */
#define  NO_CHAINED   7  /* matrizes não encadeadas - matrices not chained */
#define  NULL_PTR     8  /* ponteiro nulo - null pointer */
#define  NO_SQUARE    9  /* matriz não quadrada - matrix not square */
#define  BAD_ROW     10  /* linha inexistente - line does not exist in the matrix */
#define  BAD_COLUMN  11  /* coluna inexistente - column does not exist in the matrix */

/*************************** Protótipos das Funções ***************************/

void MatrixClearError (void);
/*******************************************************************************
 Inicialização do erro. Error initialization.
*******************************************************************************/

int MatrixError (void);
/*******************************************************************************
 Devolve o código do último erro ocorrido. Returning the error code.
*******************************************************************************/

char *MatrixErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do último erro ocorrido.
 Returning an error message.
*******************************************************************************/

PtMatrix MatrixCreate (unsigned int pnl, unsigned int pnc);
/*******************************************************************************
 Cria uma matriz nula, com pnl linhas e pnc colunas, para armazenar elementos
 reais. Devolve a referência da matriz criada ou NULL, caso não consiga criar
 a matriz. Valores de erro: OK, BAD_SIZE ou NO_MEM.

 Creating the empty matrix with the required size. Returns the reference to the
 new matrix or NULL if there isn't enough memory. Error codes: OK, BAD_SIZE or NO_MEM.
*******************************************************************************/

void MatrixDestroy (PtMatrix *pmatrix);
/*******************************************************************************
 Destrói a matriz pmatrix, caso ela exista, e coloca a sua referência a NULL.
 Valores de erro: OK ou NO_MATRIX.

 Destroys the matrix and releases the memory. Error codes: OK or NO_MATRIX.
*******************************************************************************/

PtMatrix MatrixCopy (PtMatrix pmatrix);
/*******************************************************************************
 Copia a matriz pmatrix, caso ela exista. Devolve a referência da matriz criada ou
 NULL, caso não consiga criar a matriz. Valores de erro: OK, NO_MATRIX ou NO_MEM.

 Copies the matrix pmatrix returning a new matrix. Returns the reference to the
 new matrix or NULL if it isn't possible to make the operation. Error codes: OK,
 NO_MATRIX or NO_MEM.
*******************************************************************************/

void MatrixSize (PtMatrix pmatrix, unsigned int *pnl, unsigned int *pnc);
/*******************************************************************************
 Devolve a dimensão da matriz pmatrix, caso ela exista. Valores de erro: OK,
 NO_MATRIX ou NULL_PTR.

 Returning the size of the matrix pmatrix - number of lines in pnl and number of
 columns in pnc, considering that the line is numbered from 1 to NL and the
 column is numbered from 1 to NC. Error codes: OK, NO_MATRIX ou NULL_PTR.
*******************************************************************************/

void MatrixModifyElement (PtMatrix pmatrix, unsigned int pl, unsigned int pc, double pval);
/*******************************************************************************
 Armazena pval na linha pl e na coluna pc da matriz pmatrix, sendo que a linha
 deve ser referenciada de 1 a NL e a coluna devem ser referenciada de 1 a NC.
 Valores de erro: OK, NO_MATRIX, BAD_ROW ou BAD_COLUMN.

 Storing the value pval in the line pl and in columns pc of the matrix pmatrix,
 considering that the line is numbered from 1 to NL and the
 column is numbered from 1 to NC. Error codes: OK, NO_MATRIX, BAD_ROW or BAD_COLUMN.
*******************************************************************************/

double MatrixObserveElement (PtMatrix pmatrix, unsigned int pl, unsigned int pc);
/*******************************************************************************
 Devolve o valor armazenado na linha pl e na coluna pc da matriz pmatrix, sendo
 que a linha deve ser referenciada de 1 a NL e a coluna devem ser referenciada
 de 1 a NC. Valores de erro: OK, NO_MATRIX, BAD_ROW ou BAD_COLUMN.

 Returning the value in the line pl and in columns pc of the matrix pmatrix.
 Error codes: OK, NO_MATRIX, BAD_ROW or BAD_COLUMN.
*******************************************************************************/

PtMatrix MatrixTranspose (PtMatrix pmatrix);
/*******************************************************************************
 Calcula a matriz transposta da matriz pmatrix. Devolve a referência da matriz
 transposta ou NULL, caso não consiga fazer a operação. Valores de erro: OK,
 NO_MATRIX ou NO_MEM.

 Build the transpose matrix of matrix pmatrix. Returns the reference to the new
 matrix or NULL if it isn't possible to make the operation. Error codes: OK,
 NO_MATRIX or NO_MEM.
*******************************************************************************/

PtMatrix MatrixAddition (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Soma as duas matrizes pmatrix1 e pmatrix2. Devolve a referência da matriz soma ou NULL,
 caso não consiga fazer a adição. Valores de erro: OK, NO_MATRIX, DIF_SIZE ou NO_MEM.

 Matrix addition. Returns the reference to the new matrix or NULL if there it
 isn't possible to make the operation. Error codes: OK, NO_MATRIX, DIF_SIZE or NO_MEM.
*******************************************************************************/

PtMatrix MatrixSubtraction (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Subtrai as duas matrizes pmatrix1 e pmatrix2. Devolve a referência da matriz diferença
 ou NULL, caso não consiga fazer a subtracção. Valores de erro: OK, NO_MATRIX,
 DIF_SIZE ou NO_MEM.

 Matrix subtraction. Returns the reference to the new matrix or NULL if it isn't
 possible to make the operation. Error codes: OK, NO_MATRIX, DIF_SIZE or NO_MEM.
*******************************************************************************/

PtMatrix MatrixMultiplication (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Multiplica as duas matrizes pmatrix1 e pmatrix2 usando o algoritmo directo. Devolve
 a referência da matriz produto ou NULL, caso não consiga fazer a multiplicação.
 Valores de erro: OK, NO_MATRIX, NO_CHAINED ou NO_MEM.

 Matrix multiplication. Returns the reference to the new matrix or NULL if it
 isn't possible to make the operation. Error codes: OK, NO_MATRIX, NO_CHAINED or NO_MEM.
*******************************************************************************/

PtMatrix MatrixMultByScalar (PtMatrix pmat, double pvalue);
/*******************************************************************************
 Multiplica a matriz pmatrix pelo escalar pvalue. Devolve a referência da matriz
 produto ou NULL, caso não consiga fazer a multiplição.
 Valores de erro: OK, NO_MATRIX ou NO_MEM.

 Matrix multiplication by a scalar. Returns the reference to the new matrix or
 NULL if it isn't possible to make the operation. Error codes: OK, NO_MATRIX or NO_MEM.
*******************************************************************************/

double MatrixDeterminant (PtMatrix pmatrix);
/*******************************************************************************
 Calcula e devolve o determinante da matriz pmatrix, caso ela seja quadrada, usando
 o algoritmo de eliminação de Gauss. Valores de erro: OK, NO_MATRIX, NO_SQUARE ou NO_MEM.

 Computes the determinante of the matrix pmatrix if and only if it is square,
 using the Gauss algorithm. Error codes: OK, NO_MATRIX, NO_SQUARE or NO_MEM.
*******************************************************************************/

int MatrixIsSquare (PtMatrix pmatrix);
/*******************************************************************************
 Determina se a matriz pmatrix é uma matriz quadrada. Devolve 1 em caso
 afirmativo e 0 no caso contrário. Valores de erro: OK ou NO_MATRIX.

 Verifies if matrix pmatrix is square. Returns 1 in affirmative case and 0 otherwise.
 Error codes: OK or NO_MATRIX.
*******************************************************************************/

int MatrixIsSymmetrical (PtMatrix pmatrix);
/*******************************************************************************
 Determina se a matriz pmatrix é uma matriz simétrica (i.e. se é igual à sua
 transposta (mas sem criar a matriz transposta). Devolve 1 em caso afirmativo e
 0 no caso contrário. Valores de erro: OK, NO_MATRIX ou NO_SQUARE.

 Verifies if matrix pmatrix is symmetrical (i.e. if it is equal to its transpose),
 but without creating the transpose matrix. Returns 1 in affirmative case and 0
 otherwise. Error codes: OK, NO_MATRIX or NO_SQUARE.
*******************************************************************************/

int MatrixEquals (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Compara se as duas matrizes pmatrix1 e pmatrix2 são idênticas. Devolve 1 em caso
 afirmativo e 0 em caso contrário. Valores de erro: OK, NO_MATRIX ou DIF_SIZE.

 Verifies if two matrices are equal (same size and all elements are equal).
 Returns 1 in affirmative case and 0 otherwise. Error codes: OK, NO_MATRIX or DIF_SIZE.
*******************************************************************************/

PtMatrix MatrixSubMatrix (PtMatrix pmat, unsigned int pl, unsigned int pc);
/*******************************************************************************
 Cria a submatriz a partir da matriz pmatrix sem linha pl e a coluna pc, tendo em
 atenção que a linha deve ser referenciada de 1 a NL e a coluna devem ser
 referenciada de 1 a NC. Devolve a referência da matriz produto ou NULL, caso não
 consiga fazer a operação. Valores de erro: OK, NO_MATRIX, BAD_ROW, BAD_COLUMN, BAD_SIZE ou NO_MEM.

 Build the submatrix obtained from matrix pmat without the line pl and the column
 pc, considering that the lines are numbered from 1 to NL and the columns are
 numbered from 1 to NC. Returns the reference to the new matrix or NULL if it isn't
 possible to make the operation. Error codes: OK, NO_MATRIX, BAD_ROW, BAD_COLUMN, BAD_SIZE or NO_MEM.
*******************************************************************************/

void MatrixStoreFile (PtMatrix pmatrix, char *pfname);
/*******************************************************************************
 Armazena a matriz pmatrix, caso ela exista, no ficheiro pfname. O ficheiro tem na
 primeira linha o número de linhas e o número de colunas da matriz, seguido das
 linhas de elementos da matrix. Valores de erro: OK, NO_MATRIX ou NO_FILE.

 Storing matrix pmatrix in text file pfname. The first line of the file is the
 number of lines followed by the number of columns. The following lines are the
 elements separated by spaces. Error codes: OK, NO_MATRIX or NO_FILE.
*******************************************************************************/

PtMatrix MatrixCreateFile (char *pfname);
/*******************************************************************************
 Cria uma matriz a partir de informação lida do ficheiro pfname. Devolve a
 referência da matriz criada ou NULL, caso não consiga criar a matriz.
 Valores de erro: OK, NO_FILE, BAD_SIZE ou NO_MEM.

 Creating a new matrix from text file pfname. Returns a reference to the new
 matrix or NULL if it isn't possible to make the operation. Error codes: OK,
 NO_FILE, BAD_SIZE or NO_MEM.
*******************************************************************************/

#endif