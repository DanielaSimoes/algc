/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstracto VECTOR (vector.c).
 A estrutura de dados de suporte do vector é uma estrutura, constituída pelo
 campo de tipo inteiro NElem para armazenar o número de componentes do vector
 e o campo de tipo ponteiro Vector, para representar a sequência atribuída
 dinamicamente, que vai armazenar as suas componentes reais.

 Autor : António Manuel Adrego da Rocha    Data : Março de 2016

 Implementation file of the abstract data type VECTOR (vector.c). The data
 structure to store the vector is composed with the integer field NElem for keeping
 the vector's size and the pointer field Vector, that represents the allocated
 array in dynamic memory, for storing the vector's real components.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"  /* Ficheiro de interface do TDA - ADT Interface file */

/************** Definição da Estrutura de Dados Interna do Vector *************/

struct vector
{
    unsigned int NElem;  /* número de componentes do vector - vector's size */
    double *Vector;    /* ponteiro para a sequencia de componentes - pointer to vector's components */
};

/*********************** Controlo Centralizado de Error ************************/

static unsigned int Error = OK;  /* inicialização do erro */

static char *ErrorMessages[] = {
        "sem erro - Without Error",
        "vector(es) inexistente(s) - Vector(s) do not exist",
        "memoria esgotada - Out of memory",
        "ficheiro inexistente - File does not exist",
        "dimensao errada - Wrong size",
        "componente inexistente no vector - Component does not exist",
        "vectores com dimensoes diferentes - Vectors with different sizes"
};

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alusão às Funções Auxiliares ************************/

static int ValidVectors (PtVector, PtVector);

/*************************** Definição das Funções ****************************/

void VectorClearError (void)
{
  Error = OK;
}

int VectorError (void)
{
  return Error;
}

char *VectorErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* não há mensagem de erro - no error message */
}

PtVector VectorCreate (unsigned int pdim)
{
  PtVector Vector;

  /* valida a dimensão do vector - size validation */
  if (pdim < 1) { Error = BAD_SIZE; return NULL; }

  /* cria o vector nulo - allocating the supporting record (struct) and its supporting array */
  if ((Vector = (PtVector) malloc (sizeof (struct vector))) == NULL)
  { Error = NO_MEM; return NULL; }

  if ((Vector->Vector = (double *) calloc (pdim, sizeof (double))) == NULL)
  { free (Vector); Error = NO_MEM; return NULL; }

  Vector->NElem = pdim;     /* armazenamento da dimensão - storing the size */

  Error = OK;
  return Vector;    /* devolve o vector criado - returning the new vector */
}

void VectorDestroy (PtVector *pvec)
{
  PtVector TmpVector = *pvec;

  /* verifica se o vector existe - verifies if vector exists */
  if (TmpVector == NULL) { Error = NO_VECTOR; return ; }

  /* libertação da memória dinâmica - free dynamic memory */
  free (TmpVector->Vector);  /* liberta a memória ocupada pelas componentes  - free the supporting array */
  free (TmpVector);    /* liberta a memória ocupada pelo vector - free the supporting record */

  Error = OK;
  *pvec = NULL;  /* coloca a referência a nulo - free the pointer pointing it to null */
}

PtVector VectorCopy (PtVector pvec)
{
  PtVector Copy; int I;

  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return NULL; }

  /* criação do vector copia nulo - creating an empty vector */
  if ((Copy = VectorCreate (pvec->NElem)) == NULL) return NULL;

  /* fazer a copia do vector - copying the components */
  for (I = 0; I < pvec->NElem; I++) Copy->Vector[I] = pvec->Vector[I];

  return Copy;  /* devolve o vector copia - returning the new vector */
}

int VectorSize (PtVector pvec)
{
  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return 0; }

  Error = OK;
  return pvec->NElem;
}

void VectorModifyComponent (PtVector pvec, unsigned int ppos, double pval)
{
  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return ; }

  /* validação do elemento pretendido - validating the element position */
  if ((ppos < 0) || (ppos >= pvec->NElem)) { Error = BAD_INDEX; return ; }

  Error = OK;
  /* escrita do valor na componente pretendida do vector - storing the new value in the component */
  pvec->Vector[ppos] = pval;
}

double VectorObserveComponent (PtVector pvec, unsigned int ppos)
{
  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return 0; }

  /* validação do elemento pretendido - validating the element position */
  if ((ppos < 0) || (ppos >= pvec->NElem)) { Error = BAD_INDEX; return 0; }

  Error = OK;
  /* devolve o valor armazenado na componente pretendida do vector - returning the component value */
  return pvec->Vector[ppos];
}

int VectorIsNull (PtVector pvec)
{
  int I;

  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return 0; }
  Error = OK;

  /* verificação das componentes do vector - verifying the vector's components */
  for (I = 0; I < pvec->NElem; I++)
    if (pvec->Vector[I]) return 0;

  return 1;  /* o vector é um vector nulo - the vector is empty */
}

PtVector VectorAddition (PtVector pvec1, PtVector pvec2)
{
  PtVector Add; int I;

  /* validação dos vectores - validating the existence of the two vectors */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* criação do vector soma nulo - creating an empty vector */
  if ((Add = VectorCreate (pvec1->NElem)) == NULL) { Error = NO_MEM; return NULL; }

  /* soma dos dois vectores - adding the respective components of the two vectors */
  for (I = 0; I < pvec1->NElem; I++)
    Add->Vector[I] = pvec1->Vector[I] + pvec2->Vector[I];

  return Add;  /* devolve o vector soma - returning the new vector */
}

PtVector  VectorSubtraction (PtVector pvec1, PtVector pvec2)
{
  PtVector Sub; int I;

  /* validação dos vectores - validating the existence of the two vectors */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* criação do vector diferença nulo - creating an empty vector */
  if ((Sub = VectorCreate (pvec1->NElem)) == NULL) { Error = NO_MEM; return NULL; }

  /* diferença dos dois vectores - subtracting the respective components of the two vectors */
  for (I = 0; I < pvec1->NElem; I++)
    Sub->Vector[I] = pvec1->Vector[I] - pvec2->Vector[I];

  return Sub;  /* devolve o vector diferença - returning the new vector */
}

PtVector  VectorMultiplication (PtVector pvec1, PtVector pvec2)
{
  PtVector Mult; int I;

  /* validação dos vectores - validating the existence of the two vectors */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* criação do vector produto nulo - creating an empty vector */
  if ((Mult = VectorCreate (pvec1->NElem)) == NULL) { Error = NO_MEM; return NULL; }

  /* produto dos dois vectores - multiplying the respective components of the two vectors*/
  for (I = 0; I < pvec1->NElem; I++)
    Mult->Vector[I] = pvec1->Vector[I] * pvec2->Vector[I];

  return Mult;  /* devolve o vector produto - returning the new vector */
}

double  VectorScalarMultiplication (PtVector pvec1, PtVector pvec2)
{
  int I; double Prod = 0.0;

  /* validação dos vectores - validating the existence of the two vectors */
  if (!ValidVectors (pvec1, pvec2)) return 0;

  /* cálculo do produto escalar - calculating the scalar product */
  for (I = 0; I < pvec1->NElem; I++)
    Prod += pvec1->Vector[I] * pvec2->Vector[I];

  Error = OK;
  return Prod;  /* devolve o produto escalar - returning the scalar product */
}

int  VectorEquals (PtVector pvec1, PtVector pvec2)
{
  int I;

  /* validação dos vectores - validating the existence of the two vectors */
  if (!ValidVectors (pvec1, pvec2)) return 0;
  Error = OK;

  /* comparação das componentes dos dois vectores - comparing the respective components */
  for (I = 0; I < pvec1->NElem; I++)
    if (pvec1->Vector[I] != pvec2->Vector[I]) return 0;

  return 1;  /* os vectores são iguais - the two vectors are equall */
}

void VectorStoreFile (PtVector pvec, char *pnomef)
{
  FILE *PtF; unsigned int I;

  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return ; }

  /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
  if ((PtF = fopen (pnomef, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimensão do vector no ficheiro - writing the vector's size */
  fprintf (PtF, "%u\n", pvec->NElem);

  /* escrita das componentes do vector no ficheiro - writing the vector's components */
  for (I = 0; I < pvec->NElem; I++) fprintf (PtF, "%lf\n", pvec->Vector[I]);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro - closing the text file */
}

PtVector VectorCreateFile (char *pnomef)
{
  PtVector Vector; FILE *PtF; unsigned int NElem, I;

  /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
  if ( (PtF = fopen (pnomef, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimensão do vector do ficheiro - reading the vector's size from the text file */
  fscanf (PtF, "%u", &NElem);
  if (NElem < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  /* criação do vector nulo - creating an empty vector */
  if ((Vector = VectorCreate (NElem)) == NULL) { fclose (PtF); return NULL; }

  /* leitura das componentes do vector do ficheiro - reading the vector's components from the text file */
  for (I = 0; I < NElem; I++) fscanf (PtF, "%lf", Vector->Vector+I);

  fclose (PtF);  /* fecho do ficheiro - closing the text file */
  return Vector;  /* devolve o vector criado - returning the new vector */
}

/*******************************************************************************
 Função auxiliar que verifica se os dois vectores podem ser operados, ou seja,
 se existem e se têm a mesma dimensão. Devolve 1 em caso afirmativo e 0 em caso
 contrário. Valores de erro: OK, NO_VECTOR ou DIF_SIZE.
*******************************************************************************/
static int ValidVectors (PtVector pvec1, PtVector pvec2)
{
  /* verifica se os dois vectores existem - verifies if the two vectors exist */
  if ((pvec1 == NULL) || (pvec2 == NULL)) { Error = NO_VECTOR; return 0; }

  /* verifica se a dimensão dos dois vectores é igual - verifies if they have the same size */
  if (pvec1->NElem != pvec2->NElem) { Error = DIF_SIZE; return 0; }

  Error = OK;
  return 1;  /* os dois vectores existem e têm a mesma dimensão - they exist and have the same size */
}