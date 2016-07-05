/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstracto VECTOR (vector.h). O vector é
 composto pela sua dimensão e pelas suas componentes reais. A implementação
 providencia um construtor para criar um vector nulo com a dimensão pretendida.
 É da responsabilidade da aplicação, invocar o destrutor, para libertar a
 memória atribuída ao objecto. O módulo providencia um controlo centralizado de
 erro, disponibilizando uma função para obter o último erro ocorrido, uma função
 para obter uma mensagem de erro elucidativa e uma função para limpar o erro.
 Providencia também operações para armazenar e recuperar vectores para ficheiros.

 Autor : António Manuel Adrego da Rocha    Data : Março de 2016

 Interface file of the abstract data type VECTOR (vector.h). The vector is defined
 by its size and the real components stored in an array. The implementation provides
 a constructor for creating an empty vector with the required size. The application
 has the responsibility of calling the destructor to release the dynamic memory
 allocated to the vector. The data-type has a central control error mechanism,
 providing operations for obtaining the last error occurred, for obtaining the
 correspondent message and for cleaning the error. The data-type has also operations
 to store and retrieve vectors from text files.

*******************************************************************************/

#ifndef _VECTOR
#define _VECTOR

/****************** Definição do Tipo Ponteiro para um VECTOR *****************/

typedef struct vector *PtVector;

/************************ Definição de Códigos de Erro ************************/

#define  OK         0  /* operação realizada com sucesso - operation with success */
#define  NO_VECTOR  1  /* o(s) vector(es) não existe(m) - vector(s) do not exist */
#define  NO_MEM     2  /* memória esgotada - out of memory */
#define  NO_FILE    3  /* o ficheiro não existe - file does not exist */
#define  BAD_SIZE   4  /* dimensão do vector errada - wrong size */
#define  BAD_INDEX  5  /* elemento inexistente no vector - element does not exist in the vector */
#define  DIF_SIZE   6  /* vectores com dimensões diferentes - vectors with different sizes */

/*************************** Protótipos das Funções ***************************/

void VectorClearError (void);
/*******************************************************************************
 Inicialização do erro. Error initialization.
*******************************************************************************/

int VectorError (void);
/*******************************************************************************
 Devolve o código do último erro ocorrido. Returns the error code.
*******************************************************************************/

char *VectorErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do último erro ocorrido.
 Returns an error message.
*******************************************************************************/

PtVector VectorCreate (unsigned int pdim);
/*******************************************************************************
 Cria um vector nulo, de componentes reais, com a dimensão indicada por pdim.
 Devolve a referência do vector criado ou NULL, caso não consiga criar o vector,
 por falta de memória. Valores de erro: OK, BAD_SIZE ou NO_MEM.

 Creates the empty vector with the required size. Returns a reference to the
 new vector or NULL if there isn't enough memory. Error codes: OK, BAD_SIZE or NO_MEM.
*******************************************************************************/

void VectorDestroy (PtVector *pvector);
/*******************************************************************************
 Destrói o vector pvector, caso ele exista, e coloca a sua
 referência a NULL. Valores de erro: OK ou NO_VECTOR.

 Destroys the vector and releases the memory. Error codes: OK or NO_VECTOR.
*******************************************************************************/

PtVector VectorCopy (PtVector pvector);
/*******************************************************************************
 Copia o vector pvector, caso ele exista. Devolve a referência do vector cópia ou
 NULL, caso não consiga fazer a cópia. Valores de erro: OK, NO_VECTOR ou NO_MEM.

 Copies the vector pvector returning a new vector or NULL if there isn't enough
 memory. Error codes: OK, NO_VECTOR or NO_MEM.
*******************************************************************************/

int VectorSize (PtVector pvector);
/*******************************************************************************
 Devolve a dimensão do vector pvector. Valores de erro: OK ou NO_VECTOR.

 Returns the size of the vector pvector. Error codes: OK or NO_VECTOR.
*******************************************************************************/

void VectorModifyComponent (PtVector pvector, unsigned int ppos, double pval);
/*******************************************************************************
 Armazena pval no índice ppos do vector pvector.
 Valores de erro: OK, NO_VECTOR ou BAD_INDEX.

 Stores the value pval in the position ppos of the vector pvector.
 Error codes: OK, NO_VECTOR or BAD_INDEX.
*******************************************************************************/

double VectorObserveComponent (PtVector pvector, unsigned int ppos);
/*******************************************************************************
 Devolve o valor armazenado no índice ppos do vector pvector.
 Valores de erro: OK, NO_VECTOR ou BAD_INDEX.

 Returns the value in the position ppos of the vector pvector.
 Error codes: OK, NO_VECTOR or BAD_INDEX.
*******************************************************************************/

int VectorIsNull (PtVector pvector);
/*******************************************************************************
 Verifica se o vector pvector é um vector nulo. Devolve 1 em caso afirmativo e 0
 em caso contrário. Valores de erro: OK ou NO_VECTOR.

 Verifies if vector pvector is empty (all components are zero). Returns 1 in
 affirmative case and 0 otherwise. Error codes: OK or NO_VECTOR.
*******************************************************************************/

PtVector VectorAddition (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Soma os dois vectores pvector1 e pvector2. Devolve a referência do vector soma ou NULL,
 caso não consiga fazer a adição. Valores de erro: OK, NO_VECTOR, DIF_SIZE ou NO_MEM.

 Vector addition returning a new vector. Error codes: OK, NO_VECTOR, DIF_SIZE or NO_MEM.
*******************************************************************************/

PtVector VectorSubtraction (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Subtrai os dois vectores pvector1 e pvector2. Devolve a referência do vector
 diferença ou NULL, caso não consiga fazer a subtracção. Valores de erro: OK,
 NO_VECTOR, DIF_SIZE ou NO_MEM.

 Vector subtraction returning a new vector. Error codes: OK, NO_VECTOR, DIF_SIZE or NO_MEM.
*******************************************************************************/

PtVector VectorMultiplication (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Faz o produto vectorial dos dois vectores pvector1 e pvector2. Devolve a referência
 do vector produto ou NULL, caso não consiga fazer a multiplicação. Valores de
 erro: OK, NO_VECTOR, DIF_SIZE or NO_MEM.

 Vector multiplication returning a new vector. Error codes: OK, NO_VECTOR, DIF_SIZE or NO_MEM.
*******************************************************************************/

double VectorScalarMultiplication (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Devolve o produto escalar dos dois vectores pvector1 e pvector2, ou 0, caso não
 possa realizar o produto. Valores de erro: OK, NO_VECTOR ou DIF_SIZE.

 Scalar vector multiplication. Error codes: OK, NO_VECTOR or DIF_SIZE.
*******************************************************************************/

int VectorEquals (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Compara se os dois vectores pvector1 e pvector2 são idênticos. Devolve 1 em caso
 afirmativo e 0 em caso contrário. Valores de erro: OK, NO_VECTOR ou DIF_SIZE.

 Verifies if two vectors are equal (same size and all components are equal).
 Returns 1 in affirmative case and 0 otherwise. Error codes: OK, NO_VECTOR or DIF_SIZE.
*******************************************************************************/

void VectorStoreFile (PtVector pvector, char *pfname);
/*******************************************************************************
 Armazena o vector pvector, caso ele exista, no ficheiro pfname. O ficheiro tem na
 primeira linha o número de componentes do vector, seguido das componentes, uma
 por linha. Valores de erro: OK, NO_VECTOR ou NO_FILE.

 Stores vector pvector in text file pfname. Error codes: OK, NO_VECTOR or NO_FILE.
*******************************************************************************/

PtVector VectorCreateFile (char *pfname);
/*******************************************************************************
 Cria um vector a partir de informação lida do ficheiro pfname. Devolve a
 referência do vector criado ou NULL, caso não consiga criar o vector.
 Valores de erro: OK, NO_FILE, BAD_SIZE ou NO_MEM.

 Creates a new vector from text file pfname. Returns a reference to the new vector
 or NULL if there isn't enough memory. Error codes: OK, NO_FILE, BAD_SIZE or NO_MEM.
*******************************************************************************/

#endif