/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstrato POLINOMIO (polynomial.c).
 A estrutura de dados de suporte do polinómio é uma estrutura, constituída pelo
 campo de tipo inteiro Degree para armazenar o grau do polinómio e o campo de
 tipo ponteiro Poly, para representar a sequência atribuída dinamicamente, que
 vai armazenar os seus coeficientes reais.

 Nome :                                                     NMec:

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "polynomial.h"    /* Ficheiro de interface do TDA - ADT Interface file */

/************ Definição da Estrutura de Dados Interna do POLINOMIO ************/

struct poly
{
  unsigned int Degree;  /* grau do polinómio - polynomial degree */
  double *Poly;      /* ponteiro para os coeficientes do polinómio - pointer to polynomial's coefficients */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;  /* inicialização do erro */

static char *ErrorMessages[] = {
                                 "sem erro - Without Error",
                                 "polinomio(s) inexistente(s) - Polynomial(s) do not exist",
                                 "memoria esgotada - Out of memory",
                                 "ficheiro inexistente - File does not exist",
                                 "grau do polinomio errado - Wrong degree",
                                 "coeficiente inexistente no polinomio - Coefficient does not exist"
                               };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alusão às Funções Auxiliares ************************/

static int ValidPolys (PtPoly, PtPoly);
static void ReducePoly (PtPoly);

/*************************** Definição das Funções ****************************/

void PolyClearError (void)
{
  Error = OK;
}

int PolyError (void)
{
  return Error;
}

char *PolyErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;    /* não há mensagem de erro - no error message */
}

PtPoly PolyCreate (unsigned int pdegree)
{
    PtPoly Poly;

      /* cria o vector nulo - allocating the supporting record (struct) and its supporting array */
      if ((Poly = (PtPoly) malloc (sizeof (struct poly))) == NULL)
      { Error = NO_MEM; return NULL; }

      if ((Poly->Poly = (double *) calloc (pdegree + 1, sizeof (double))) == NULL)
      { free (Poly); Error = NO_MEM; return NULL; }

        Poly->Degree = pdegree;     /* armazenamento da dimensão - storing the size */

        Error = OK;
      return Poly;    /* devolve o vector criado - returning the new vector */

}

void PolyDestroy (PtPoly *ppoly)
{
    PtPoly TmpPoly = *ppoly;

    /* verifica se o vector existe - verifies if vector exists */
    if (TmpPoly == NULL) { Error = NO_POLY; return ; }

    /* libertação da memória dinâmica - free dynamic memory */
    free (TmpPoly->Poly);  /* liberta a memória ocupada pelas componentes  - free the supporting array */
    free (TmpPoly);    /* liberta a memória ocupada pelo vector - free the supporting record */

    Error = OK;
    *ppoly = NULL;  /* coloca a referência a nulo - free the pointer pointing it to null */
}

PtPoly PolyCopy (PtPoly ppoly)
{
    PtPoly Copy; int I;

    /* verifica se o vector existe - verifies if vector exists */
    if (ppoly == NULL) { Error = NO_POLY; return NULL; }

    /* criação do vector copia nulo - creating an empty vector */
    if ((Copy = PolyCreate (ppoly->Degree+1)) == NULL) return NULL;

    /* fazer a copia do vector - copying the components */
    for (I = 0; I < ppoly->Degree+1; I++) Copy->Poly[I] = ppoly->Poly[I];

    ReducePoly(Copy);

    return Copy;  /* devolve o vector copia - returning the new vector */
}

int PolyDegree (PtPoly ppoly)
{
    if(ppoly == NULL){
        Error = NO_POLY;
        return 0;
    }

    Error = OK;
    return ppoly->Degree;
}

void PolyModifyCoefficient (PtPoly ppoly, unsigned int ppos, double pvalue)
{

    if(ppoly == NULL){
        Error = NO_POLY;
    }

    if(ppos > ppoly->Degree){
        Error = BAD_INDEX;
    }

    Error = OK;
    ppoly->Poly[ppos] = pvalue;

}

double PolyObserveCoefficient (PtPoly ppoly, unsigned int ppos)
{
    if(ppoly == NULL){
      Error = NO_POLY;
        return 0;
    }else if(ppos > ppoly->Degree){
      Error = BAD_INDEX;
        return 0;
    }

    Error = OK;

    return ppoly->Poly[ppos];
}

int PolyIsNull (PtPoly ppoly)
{
    if(ppoly == NULL){
        Error = NO_POLY;
        return 0;
    }

    Error = OK;

    for (int i = 0; i <= ppoly->Degree; ++i) {
        if(ppoly->Poly[i])
            return 0;
    }

    return 1;

}

PtPoly PolySymmetrical (PtPoly ppoly)
{
    if(ppoly == NULL){
        Error = NO_POLY;
        return NULL;
    }

    PtPoly tmp;

    if((tmp = PolyCreate(ppoly->Degree)) == NULL){
        return NULL;
    }

    for (int i = 0; i <= ppoly->Degree ; ++i) {
      if(ppoly->Poly[i]!=0){
        tmp->Poly[i] = -ppoly->Poly[i];
      }
    }

    return tmp;
}

PtPoly PolyAddition (PtPoly ppoly1, PtPoly ppoly2)
{

    if(!ValidPolys(ppoly1,ppoly2))
        return NULL;

    if(ppoly1==NULL || ppoly2==NULL){
        Error = NO_POLY;
    }

    int smallestDegree;
    int biggestDegree;
    int biggest = 0; /* considera-se o ppoly1 */

    if(ppoly1->Degree > ppoly2->Degree){
        biggestDegree = ppoly1->Degree;
        smallestDegree = ppoly2->Degree;
    }else{
        biggestDegree = ppoly2->Degree;
        smallestDegree = ppoly1->Degree;
        biggest = 1;
    }

    PtPoly sum;

    if((sum = PolyCreate(biggestDegree)) == NULL){
        return NULL;
    }

    for (int i = 0; i <= smallestDegree ; ++i) {
        sum->Poly[i] = ppoly1->Poly[i] + ppoly2->Poly[i];
    }

    for (int j = smallestDegree + 1; j <= biggestDegree; ++j) {
        if(biggest)
            sum->Poly[j] = ppoly2->Poly[j];
        else
            sum->Poly[j] = ppoly1->Poly[j];
    }

    Error = OK;
    ReducePoly(sum);

    return sum;

}

PtPoly PolySubtraction (PtPoly ppoly1, PtPoly ppoly2)
{

    PtPoly sub;

    /* Check validity of polynomials */
    if (!ValidPolys(ppoly1, ppoly2))
        return NULL;

    int smallestDegree;
    int biggestDegree;
    int biggest = 0; /* considera-se o ppoly1 */

    if(ppoly1->Degree > ppoly2->Degree){
        biggestDegree = ppoly1->Degree;
        smallestDegree = ppoly2->Degree;
    }else{
        biggestDegree = ppoly2->Degree;
        smallestDegree = ppoly1->Degree;
        biggest = 1;
    }

    if((sub = PolyCreate(biggestDegree)) == NULL){
        return NULL;
    }

    for (int i = 0; i <= smallestDegree ; ++i) {
        sub->Poly[i] = ppoly1->Poly[i] - ppoly2->Poly[i];
    }

    for (int j = smallestDegree + 1; j <= biggestDegree; ++j) {
        if (biggest && sub->Poly[j] != 0)
            sub->Poly[j] = ppoly2->Poly[j] * (-1);
        else
            sub->Poly[j] = ppoly1->Poly[j];
    }

    ReducePoly(sub);
    Error = OK;
    return sub;

}

PtPoly PolyMultiplication (PtPoly ppoly1, PtPoly ppoly2)
{

    if(!ValidPolys(ppoly1,ppoly2))
        return NULL;

    if(ppoly1==NULL || ppoly2==NULL){
        Error = NO_POLY;
        return NULL;
    }

    PtPoly mul;

    int degree = ppoly1->Degree + ppoly2->Degree;

    if((mul = PolyCreate(degree)) == NULL){
        return NULL;
    }

    for (int i = 0; i <= ppoly1->Degree ; ++i) {
        for (int j = 0; j <= ppoly2->Degree ; ++j) {
            mul->Poly[i + j] += ppoly1->Poly[i] * ppoly2->Poly[j];
        }
    }

    Error = OK;

    ReducePoly(mul);

    return mul;

}

int PolyEquals (PtPoly ppoly, PtPoly ppoly2)
{
    bool sameDegree = false;
    bool sameElem = false;
    ReducePoly(ppoly);
    ReducePoly(ppoly2);

    if(ppoly->Degree == ppoly2->Degree){
        sameDegree = true;
    }else{
        return 0;
    }

    for (int i = 0; i <= ppoly2->Degree; ++i) {
        if(ppoly->Poly[i]!=ppoly2->Poly[i]){
            sameElem = false;
            return 0;
        }
    }

    return 1;
}

void PolyStoreFile (PtPoly ppoly, char *pnomef)
{
    FILE *PtF; unsigned int I;

    if (ppoly == NULL) { Error = NO_POLY; return ; }

    if ((PtF = fopen (pnomef, "w")) == NULL) { Error = NO_FILE; return ; }

    fprintf (PtF, "%u\n", ppoly->Degree);

    /* escrita das componentes do vector no ficheiro - writing the vector's components */
    for (I = 0; I <= ppoly->Degree; I++) fprintf (PtF, "%lf\n", ppoly->Poly[I]);

    Error = OK;
    fclose (PtF);  /* fecho do ficheiro - closing the text file */}

PtPoly PolyCreateFile (char *pnomef)
{
    PtPoly Poly; FILE *PtF; unsigned int Degree, I;

    if ( (PtF = fopen (pnomef, "r")) == NULL) { Error = NO_FILE; return NULL; }

    /* leitura da dimensão do vector do ficheiro - reading the vector's size from the text file */
    fscanf (PtF, "%u", &Degree);

    /* criação do vector nulo - creating an empty vector */
    if ((Poly = PolyCreate (Degree)) == NULL) { fclose (PtF); return NULL; }

    /* leitura das componentes do vector do ficheiro - reading the vector's components from the text file */
    for (I = 0; I <= Degree; I++) fscanf (PtF, "%lf", Poly->Poly+I);

    fclose (PtF);  /* fecho do ficheiro - closing the text file */
    Error = OK;
    return Poly;  /* devolve o vector criado - returning the new vector */
}

double PolyEvaluation (PtPoly ppoly, double px)
{
    if(ppoly == NULL){
        Error = NO_POLY;
        return 0;
    }

    double result = 0;
    for (int i = 0; i <= ppoly->Degree ; ++i) {
        result += ppoly->Poly[i]*pow(px, (i));
    }

    return result;
}

/*******************************************************************************
 Função auxiliar que verifica se os dois polinómios existem. Devolve 1 em caso
 afirmativo e 0 em caso contrário. Valores de erro: OK ou NO_POLY.
*******************************************************************************/

static int ValidPolys (PtPoly ppoly1, PtPoly ppoly2)
{
  /* verifica se os dois polinómios existem - verifies if the two polynomials exist */
  if ((ppoly1 == NULL) || (ppoly2 == NULL)) { Error = NO_POLY; return 0; }

  Error = OK;
  return 1;  /* os dois polinómios existem - they exist */
}

/*******************************************************************************
 Função auxiliar que reduz o polinómio ao menor grau possível. Valores de erro:
 NO_POLY.

 Auxiliary function to reduce the polynomial to its least degree. Error codes: NO_POLY.

*******************************************************************************/

static void ReducePoly (PtPoly ppoly)
{
    unsigned int Degree;

    /* verifica se o polinómio existe - verifies if the polynomial exists */
    if (ppoly == NULL) { Error = NO_POLY; return ; }

    Degree = ppoly->Degree;

    while (Degree > 0 && ppoly->Poly[Degree] == 0.0) Degree--;

    if (Degree != ppoly->Degree)
        ppoly->Poly = (double *) realloc (ppoly->Poly, (Degree+1) * sizeof (double));

    ppoly->Degree = Degree;
    Error = OK;
}
