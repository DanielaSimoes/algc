/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstracto SET (set.c).
 A estrutura de dados de suporte do conjunto é uma estrutura, constituída pelo
 campo Cardinal para armazenar o número de elementos existentes no conjunto e o
 campo Head que é a cabeça da lista biligada dos elementos do conjunto. A lista
 de elementos do conjunto, que são caracteres alfabéticos maiúsculos, está
 ordenada por ordem crescente.

 Nome :                                                     NMec:

 Implementation file of the abstract data type SET (set.c). The data
 structure to store the set is composed with the integer field Cardinal for
 keeping the number of elements in the set and the pointer field Head, that
 represents the start point of the double-link list, for storing the set's
 elements, that are uppercase characters stored by increasing order.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "set.h"    /* Ficheiro de interface do TDA - ADT Interface file */

/************ Definição da Estrutura de Dados Interna do Conjunto ************/

typedef struct node *PtNode;

struct node    /* definição de um nó da lista biligada - node of a double-link list */
{
  char *PtElem;  /* ponteiro para o elemento - pointer to the element */
  PtNode PtNext;  /* ponteiro para o nó seguinte - pointer to the next element */
  PtNode PtPrev;  /* ponteiro para o nó anterior - pointer to the preview element */
};

struct set
{
  unsigned int Cardinal;   /* cardinal do conjunto - set's cardinal */
  PtNode Head;    /* cabeça da lista dos elementos do conjunto - pointer to set's list of elements */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;  /* inicialização do erro */

static char *ErrorMessages[] = {
                                 "sem erro - Without Error",
                                 "conjunto(s) inexistente(s) - Set(s) do not exist",
                                 "memoria esgotada - Out of memory",
                                 "ficheiro inexistente - File does not exist",
                                 "elemento inexistente no conjunto - Element does not exist",
                                 "elemento existente no conjunto - Element already exists",
                                };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alusão às Funções Auxiliares ************************/

static int ValidSets (PtSet, PtSet);
static PtNode CreateElement (char);
static void DestroyElement (PtNode *);
static PtNode PosInsert (PtSet, char);
static PtNode PosDelete (PtSet, char);

/*************************** Definição das Funções ****************************/

void SetClearError (void)
{
  Error = OK;
}

int SetError (void)
{
  return Error;
}

char *SetErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* não há mensagem de erro - no error message */
}

PtSet SetCreate (void)
{
    PtSet Set;

    if((Set = (PtSet) malloc (sizeof(struct set))) == NULL)
    {
        Error = NO_MEM;
        return NULL;
    }

    Error = OK;
    Set->Head = NULL;
    Set->Cardinal = 0;

  return Set;
}

void SetDestroy (PtSet *pset)
{

    PtSet set = *pset;

    if(set == NULL){
        Error = NO_SET;
        return;
    }

    while(set->Cardinal){
        char tmp = SetObserveElement(set, 1);
        SetDeleteElement(set, tmp);
    }

    free(set->Head);
    free(set);

    *pset = NULL;
    Error = OK;

}

PtSet SetCopy (PtSet pset)
{
    PtSet copy;

    if(pset == NULL){
        Error = NO_SET;
        return NULL;
    }

    if((copy = SetCreate()) == NULL){
        return NULL;
    }

    for (int i = 0; i <= pset->Cardinal; ++i) {
        SetInsertElement(copy, SetObserveElement(pset,i));
    }

    Error = OK;
    return copy;
}

int SetCardinal (PtSet pset)
{
  if (pset == NULL)  /* verifica se o conjunto existe - verifies is the set exists */
  {
    Error = NO_SET; return 0;
  }

  Error = OK;
  return pset->Cardinal;  /* devolve o cardinal - returns the cardinal */
}

int SetInsertElement (PtSet pset, char pelem)
{
  PtNode NoTmp, NoIns;

  if (pset == NULL)  /* verifica se o conjunto existe - verifies if the set exists */
  {
    Error = NO_SET; return 0;
  }

  /* conjunto vazio ou elemento menor do que o primeiro elemento do conjunto */
  /* empty set or element "smaller" than the set's first element */
  if (pset->Head == NULL || pelem < *pset->Head->PtElem)
  {
    /* inserção sem sucesso, porque não é possível criar o elemento */
    /* insertion without success due to lack of memory to create the element */
    if ((NoTmp  = CreateElement (pelem)) == NULL) return 0;

    /* ligação do elemento à  cabeça da lista - linking the element in list's head */
    NoTmp->PtNext = pset->Head; pset->Head = NoTmp;
    if (NoTmp->PtNext != NULL) NoTmp->PtNext->PtPrev = NoTmp;
  }
  else
  {
    /* procurar se o elemento existe ou a sua posição de inserção caso não exista */
    /* search for the element or its insertion position */
    if ((NoIns = PosInsert (pset, pelem)) == NULL) return 0;
    /* inserção sem sucesso, porque o elemento já existe no conjunto */
    /* insertion without success because element already exists in the set */

    if ((NoTmp = CreateElement (pelem)) == NULL) return 0;
    /* inserção sem sucesso, porque não é possível criar o elemento */
    /* insertion without success due to lack of memory to create the element */

    /* inserir à frente de outro nó - insertion in front of another node */
    NoTmp->PtNext = NoIns->PtNext;
    if (NoTmp->PtNext != NULL) NoTmp->PtNext->PtPrev = NoTmp;
    NoTmp->PtPrev = NoIns; NoIns->PtNext = NoTmp;
  }

  pset->Cardinal++;  /* incrementa o cardinal do conjunto - cardinal increment */
  Error = OK;
  return 1;  /* inserção com sucesso - insertion with success */
}

int SetDeleteElement (PtSet pset, char pelem)
{
  PtNode NoRem;

  if (pset == NULL)  /* verifica se o conjunto existe - verifies if the set exists */
  {
    Error = NO_SET; return 0;
  }

  /* procurar se o elemento existe - search for the element */
  if ((NoRem = PosDelete (pset, pelem)) == NULL) return 0;
  /* remoção sem sucesso, porque o elemento ainda não existe no conjunto */
  /* deletion without success because element does not exist in the set*/

  if (NoRem == pset->Head)  /* primeiro elemento da lista - first element of the list */
  {
    if (NoRem->PtNext != NULL) NoRem->PtNext->PtPrev = NULL;
    pset->Head = NoRem->PtNext;
  }
  else  /* noutra posição da lista - in another position of the list */
  {
    NoRem->PtPrev->PtNext = NoRem->PtNext;
    if (NoRem->PtNext != NULL) NoRem->PtNext->PtPrev = NoRem->PtPrev;
  }

  DestroyElement (&NoRem);  /* liberta a memória ocupada pelo elemento  - frees the memory */
  pset->Cardinal--;  /* decrementa o cardinal do conjunto - cardinal decrement */
  Error = OK;
  return 1;  /* remoção com sucesso - deletion with success */
}

char SetObserveElement (PtSet pset, unsigned int ppos)
{
  PtNode NoTmp; unsigned int I;

  if (pset == NULL)  /* verifica se o conjunto existe - verifies if the set exists */
  {
    Error = NO_SET; return 0;
  }

  /* verifica se a posição é válida - verifies if the position is valid */
  if (ppos > pset->Cardinal)
  {
    Error = NO_ELEM; return 0;
  }

  /* varre a lista atè à posição pretendida - iterates the list until the required position */
  NoTmp = pset->Head;
  for (I = 1; I < ppos; I++) NoTmp = NoTmp->PtNext;

  if (NoTmp == NULL) return ' ';
  else return *NoTmp->PtElem;  /* devolve o elemento - returns the element */
}

int SetSearchElement (PtSet pset, char pelem)
{
  if (pset == NULL)  /* verifica se o conjunto existe - verifies if the set exists */
  {
    Error = NO_SET; return 0;
  }

  if (PosDelete (pset, pelem) != NULL) return 1;  /* o elemento existe - the element exists */

  Error = OK;
  return 0;  /* o elemento não existe - the element does not exist */
}

PtSet SetReunion (PtSet pset1, PtSet pset2)
{
    PtSet reunion;
    char c;

    if(!ValidSets(pset1,pset2)){
        return NULL;
    }

    if((reunion = SetCreate()) == NULL){
        return NULL;
    }

    /* Assumindo que não há elementos repetidos */
    for (int i = 0; i <= pset1->Cardinal ; ++i) {
        c = SetObserveElement(pset1, i);
        if(!SetSearchElement(reunion, c)){
            if(!SetInsertElement(reunion, c)){
                SetDestroy(&reunion);
                return NULL;
            }
        }
    }

    for (int j = 0; j <= pset2->Cardinal ; ++j) {
        c = SetObserveElement(pset2, j);
        if(!SetSearchElement(reunion, c)){
            if(!SetInsertElement(reunion, c)){
                SetDestroy(&reunion);
                return NULL;
            }
        }
    }

    Error = OK;
    return reunion;
}

PtSet SetIntersection (PtSet pset1, PtSet pset2)
{
    PtSet intersection;
    char ch;

    if(!ValidSets(pset1,pset2)){
        return NULL;
    }

    if((intersection = SetCreate()) == NULL){
        return NULL;
    }

    for (int i = 0; i <= pset1->Cardinal ; ++i) {
        ch = SetObserveElement(pset1, i);
        if(SetSearchElement(pset2, ch)){
            if(!SetSearchElement(intersection, ch)){
                if(!SetInsertElement(intersection, ch)){
                    SetDestroy(&intersection);
                    return NULL;
                }
            }
            SetInsertElement(intersection, ch);
        }
    }

    Error = OK;
    return intersection;
}

PtSet SetSymmetricDifference (PtSet pset1, PtSet pset2)
{
    PtSet result;

    if(!ValidSets(pset1,pset2)){
        return NULL;
    }

    if((result = SetCreate()) == NULL){
        return NULL;
    }

    for (int i = 0; i <= pset1->Cardinal ; ++i) {
        if(!SetSearchElement(pset2, SetObserveElement(pset1, i))) {
            if(!SetSearchElement(result, SetObserveElement(pset1, i))){
                if(!SetInsertElement(result, SetObserveElement(pset1, i))){
                    SetDestroy(&result);
                }
            }
        }
    }

    for (int j = 0; j <= pset2->Cardinal ; ++j) {
        if(!SetSearchElement(pset1, SetObserveElement(pset2, j))) {
            if(!SetSearchElement(result, SetObserveElement(pset2, j))){
                if(!SetInsertElement(result, SetObserveElement(pset2, j))){
                    SetDestroy(&result);
                }
            }
        }
    }

    Error = OK;
    return result;
}

int SetEquals (PtSet pset1, PtSet pset2)
{
    if(!ValidSets(pset1,pset2)){
        return 0;
    }

    if(pset1->Cardinal != pset2->Cardinal){
        return 0;
    }

    for (int i = 0; i < pset1->Cardinal ; ++i) {
       if(SetObserveElement(pset1,i) != SetObserveElement(pset2, i)){
           return 0;
       }
    }

    Error = OK;
    return 1;
}

void SetStoreFile (PtSet pset, char *pnomef)
{
  FILE *PtF; PtNode NoTmp;

  /* verifica se o vector existe - verifies if set exists */
  if (pset == NULL) { Error = NO_SET; return ; }

  /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
  if ((PtF = fopen (pnomef, "w")) == NULL)
  { Error = NO_FILE; return ; }

  /* escrita do cardinal do conjunto no ficheiro - - writing the set's cardinal */
  fprintf (PtF, "%u\n", pset->Cardinal);

  /* escrita dos elementos do conjunto no ficheiro - writing the set's elements */
  for (NoTmp = pset->Head; NoTmp != NULL; NoTmp = NoTmp->PtNext)
  fprintf (PtF, "%c\n", *NoTmp->PtElem);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro - closing the text file */
}

PtSet SetCreateFile (char *pnomef)
{
  PtSet Set; FILE *PtF; unsigned int Cardinal, I; char Elemento;

  /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
  if ( (PtF = fopen (pnomef, "r")) == NULL)
  { Error = NO_FILE; return NULL; }

  /* leitura do cardinal do conjunto do ficheiro - reading the set's cardinal from the text file */
  fscanf (PtF, "%u", &Cardinal); fscanf (PtF, "%*c");

  /* criação do set vazio - creating an empty set */
  if ((Set = SetCreate ()) == NULL)
  { fclose (PtF); return NULL; }

  /* leitura dos elementos do conjunto do ficheiro - reading the set's elements from the text file */
  for (I = 0; I < Cardinal ; I++)
  {
    fscanf (PtF, "%c", &Elemento); fscanf (PtF, "%*c");
    if (!SetInsertElement (Set, Elemento))
      {
        SetDestroy (&Set); fclose (PtF); return NULL;
      }
  }

  fclose (PtF);  /* fecho do ficheiro - closing the text file */
  Error = OK;
  return Set;  /* devolve o set criado - returning the new set */
}

/********************** Definição das Funções Auxiliares **********************/

/*******************************************************************************
 Função auxiliar que verifica se os dois ponteiros são válidos. Devolve 1 em
 caso afirmativo e 0 em caso contrário.

 Auxiliary function to verify if the two sets can be operated, that is, if they
 exist. Returns 1 in affirmative case and 0 otherwise. Error codes: OK or NO_SET.
*******************************************************************************/
static int ValidSets (PtSet pset1, PtSet pset2)
{
  /* verifica se os dois conjuntos existem - verifies if the two sets exist */
  if ((pset1 == NULL) || (pset2 == NULL)) { Error = NO_SET; return 0; }

  Error = OK;
  return 1;  /* os dois conjuntos existem - they exist */
}

/*******************************************************************************
 Função auxiliar que cria o elemento do conjunto. Começa por criar um nó da
 lista biligada e depois cria o elemento, para onde copia o valor que se
 pretende armazenar. Devolve a referência do nó criado ou NULL, caso não consiga
 criar o nó ou o elemento, por falta de memória. Valores de erro: NO_MEM.

 Auxiliary function that creates the element. Starts by creating the list node
 and the element storing the character. Returns a reference to the new node or
 NULL if there isn't enough memory. Error codes: OK or NO_MEM.
*******************************************************************************/
static PtNode CreateElement (char pelem)
{
  PtNode NoTmp;

  if ((NoTmp = (PtNode) malloc (sizeof (struct node))) == NULL)
  {
    Error = NO_MEM; return NULL;
  }

  if ((NoTmp->PtElem = malloc (sizeof (char))) == NULL)
  {
    free (NoTmp);
    Error = NO_MEM; return NULL;
  }

  *NoTmp->PtElem = pelem;  /* copia o valor - copies the element */
  NoTmp->PtNext = NULL;  /* aponta para a frente para NULL - next node is NULL */
  NoTmp->PtPrev = NULL;  /* aponta para a trás para NULL - preview node is NULL */

  Error = OK;
  return NoTmp;  /* devolver a referência do nó criado - returns the new node */
}

/*******************************************************************************
 Função auxiliar que elimina o elemento do conjunto, indicando para esse feito
 o nó onde o elemento está dependurado. Começa por verificar se o nó é valido,
 após o que liberta a memória ocupada pelo elemento e pelo nó da lista. Como esta
 função é correctamente invocada, ela não precisa de actualizar a variável de erro.
*******************************************************************************/
static void DestroyElement (PtNode *pnode)
{
  if (*pnode == NULL) return;

  free ((*pnode)->PtElem);
  free (*pnode);
  *pnode = NULL;
}

/*******************************************************************************
 Função auxiliar que pesquisa um elemento no conjunto, para determinar a sua
 posição para eventual remoção do conjunto. Devolve o endereço do nó onde deve
 ser feita a remoção, ou NULL caso o elemento ainda não exista no conjunto.

 Auxiliary function that searches the list for an element deletion. Returns
 a pointer to the element's node or a NULL pointer if the element does not exist.
*******************************************************************************/
static PtNode PosDelete (PtSet pset, char pelem)
{
  PtNode Tmp;

  if (pset->Head == NULL) return NULL;  /* conjunto vazio - empty set */

  for (Tmp = pset->Head; Tmp != NULL; Tmp = Tmp->PtNext)
    if (*Tmp->PtElem == pelem) return Tmp;  /* elemento encontrado - element found */

  Error = NO_ELEM;
  return NULL;  /* elemento não encontrado - element not found */
}

/*******************************************************************************
 Função auxiliar que pesquisa um elemento no conjunto, para determinar a sua
 posição para eventual colocação no conjunto. Devolve o endereço do nó à frente
 do qual deve ser feita a inserção, ou NULL caso o elemento já exista no
 conjunto. A função é invocada sabendo à partida que o conjunto não está vazio
 ou que o elemento não vai ser inserido no início do conjunto.
*******************************************************************************/
static PtNode PosInsert (PtSet pset, char pelem)
{
  PtNode Tmp, NodePrev;

  for (Tmp = pset->Head; Tmp != NULL; NodePrev = Tmp, Tmp = Tmp->PtNext)
    if (*Tmp->PtElem >= pelem) break;

  /* se o elemento não foi encontrado então entra à frente do nó anterior */
  /* if the element is not found then it will be indicated the preview node */
  if (Tmp == NULL || *Tmp->PtElem > pelem) return NodePrev;
  else
  {
    Error = REP_ELEM;
    return NULL;  /* o elemento foi encontrado - element found */
  }
}
