/******* Implementação da Fila com Prioridade com um Amontoado Binário ********/
/***** Fila com Prioridade orientada aos mínimos Nome: pqueue_dijkstra.c  *****/

#include <stdio.h>
#include <stdlib.h>

#include "pqueue_dijkstra.h"  /* Interface */

/******* Definição do Estrutura de Dados da Fila com Prioridade ********/

struct pqueue  /* definição da Fila com Prioridade */
{
  unsigned int HeapSize;  /* capacidade de armazenamento da Fila - capacity of the priority queue */
  unsigned int NumElem;  /* número de elementos armazenados na Fila - number of elements stored in the priority queue */
  VERTEX *Heap;  /* ponteiro para o monte a alocar dinamicamente - pointer to the priority queue array */
};

/********************** Definição dos Subprogramas *********************/

PtPQueue PQueueCreate (unsigned int pdim)
{
    PtPQueue PQueue;

    if (pdim == 0) return NULL;

    /* alocar memória para a Fila com Prioridade - - memory alocation for the priority queue */
    if ((PQueue = (PtPQueue) malloc (sizeof (struct pqueue))) == NULL) return NULL;

    /* alocar memória para o array the armazenamento dos elementos - memory alocation for the element's array */
    if ((PQueue->Heap = (VERTEX *) calloc (pdim, sizeof (VERTEX))) == NULL)
    { free (PQueue); return NULL; }

    PQueue->HeapSize = pdim;  /* armazenar a dimensão da Fila - store the priority queue dimension */
    PQueue->NumElem = 0;  /* inicializar o número de elementos da Fila - initialize the number of elements */

    return PQueue;  /* devolver a referência da Fila acabada de criar - returning the new priority queue */
}


int PQueueDestroy (PtPQueue *ppqueue)
{
    PtPQueue TmpPQueue = *ppqueue;

    if (TmpPQueue == NULL) return NO_PQUEUE;

    free (TmpPQueue->Heap);  /* libertar a memória ocupada pelo monte - free the element's array */
    free (TmpPQueue);  /* libertar a memória ocupada pela Fila - free the priority queue */

    *ppqueue = NULL;  /* colocar a referência da Fila a NULL - priority queue pointing to null */

    return OK;
}


int PQueueInsert (PtPQueue ppqueue, VERTEX *pelem)
{
    unsigned int i;

    if (ppqueue == NULL) return NO_PQUEUE;
    if (ppqueue->NumElem == ppqueue->HeapSize) return PQUEUE_FULL;

    /* ajustar o monte, descendo os pais maiores do que o elemento */
    for (i = ppqueue->NumElem; i > 0 && ppqueue->Heap[(i-1)/2].Cost > pelem->Cost; i = (i-1)/2)
        ppqueue->Heap[i] = ppqueue->Heap[(i-1)/2];

    ppqueue->Heap[i] = *pelem;  /* colocar o novo elemento no monte - storing the new element in the heap */
    ppqueue->NumElem++;  /* incrementar o número de elementos do monte - increasing the number of elements of the heap */

    return OK;
}


int PQueueDeleteMin (PtPQueue ppqueue, VERTEX *pelem)
{
    unsigned int i, Son;  /* posição do pai e do filho */

    if (ppqueue == NULL) return NO_PQUEUE;
    if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
    if (pelem == NULL) return NULL_PTR;

    *pelem = ppqueue->Heap[0];  /* retirar a raiz do monte */
    ppqueue->NumElem--;  /* decrementar o número de elementos do monte - decreasing the number of elements of the heap */

    /* ajustar o monte, subindo os filhos menores do que o elemento */
    for (i = 0; i*2+1 <= ppqueue->NumElem; i = Son)
    {
        Son = 2*i+1;  /* primeiro filho - position of the first son */

        /* determinar o menor dos filhos */
        if (Son < ppqueue->NumElem && ppqueue->Heap[Son].Cost > ppqueue->Heap[Son+1].Cost)
            Son++;

        /* subir o menor filho do que o último elemento */
        if (ppqueue->Heap[Son].Cost < ppqueue->Heap[ppqueue->NumElem].Cost)
            ppqueue->Heap[i] = ppqueue->Heap[Son];
        else break;
    }

    /* recolocar o último elemento no monte - storing the last element in the empty position */
    ppqueue->Heap[i] = ppqueue->Heap[ppqueue->NumElem];

    return OK;
}


int PQueueDecrease (PtPQueue ppqueue, VERTEX *pelem)
{
    unsigned int i;

    if (ppqueue == NULL) return NO_PQUEUE;
    if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;

    /* procurar o elemento na fila com prioridade - look for the element */
    for (i = 0; i < ppqueue->NumElem; i++)
        if (ppqueue->Heap[i].Vertex == pelem->Vertex) break;

    if (i == ppqueue->NumElem) return NO_ELEM;

    for (; i > 0 && ppqueue->Heap[(i+1)/2-1].Cost > pelem->Cost; i = (i+1)/2-1){
        ppqueue->Heap[i] = ppqueue->Heap[(i+1)/2-1];
    }

    ppqueue->Heap[i] = *pelem;	/* colocar o novo valor do elemento */

    return OK;
}


int PQueueIsEmpty (PtPQueue ppqueue)
{
  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  return OK;
}

int PQueueDisplay (PtPQueue ppqueue)
{
  int I;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;

  for (I = 0; I < ppqueue->NumElem; I++)
    printf ("(%d-%d)  ", ppqueue->Heap[I].Vertex, ppqueue->Heap[I].Cost);
  printf ("\n");

  return OK;
}
