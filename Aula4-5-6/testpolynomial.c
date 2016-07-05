#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polynomial.h"

void WritePoly (PtPoly);

int main (void)
{
	PtPoly poly1 = NULL, poly2 = NULL, poly3 = NULL;
	char filename[21]; int st, degree, i; double coef;

	system ("clear");
	printf ("\nLer polinomio do ficheiro - Read polynomial from a text file\n");
	do
	{
  		printf ("Nome do ficheiro (Filename) -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);

	poly1 = PolyCreateFile (filename);
	printf ("\nPolinomio lido do ficheiro - Polynomial acquired from text file %s\n", filename);
	WritePoly (poly1);

	poly2 = PolySymmetrical (poly1);
	printf ("\nPolinomio simetrico - Symmetrical polynomial\n");
	WritePoly (poly2);
	PolyDestroy (&poly2);

	printf ("\nLer polinomio do teclado - Read polynomial from keyboard\n");
	do
	{
		printf ("grau do polinomio (polynomial's degree)? "); scanf ("%d", &degree);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (degree < 0);

	poly2 = PolyCreate (degree);
    	for (i = 0; i <= degree; i++)
	{
		do
		{
			printf ("Coeficiente do polinomio (polynomial's coefficient)? "); st = scanf ("%lf", &coef);
			scanf ("%*[^\n]"); scanf ("%*c");
		} while (st == 0);
		PolyModifyCoefficient (poly2, i, coef);
	}

	printf ("\nPolinomio lido do teclado - Polynomial acquired from keyboard\n");
	WritePoly (poly2);

	printf ("\nEscrever polinomio no ficheiro - Storing the polynomial in a text file\n");
	do
	{
  		printf ("Nome do ficheiro (Filename) -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);
	PolyStoreFile (poly2, filename);

	poly3 = PolyAddition (poly1, poly2);
	printf ("\nPolinomio soma - Sum polynomial\n");
	WritePoly (poly3);

	PolyDestroy (&poly3);
	poly3 = PolySubtraction (poly1, poly2);
	printf ("\nPolinomio diferenca - Difference polynomial\n");
	WritePoly (poly3);

	PolyDestroy (&poly3);
	poly3 = PolyMultiplication (poly1, poly2);
	printf ("\nPolinomio produto - Product polynomial\n");
	WritePoly (poly3);

	printf ("\nDestruir os polinomios - Releasing the polynomials\n");
	PolyDestroy (&poly1);
	PolyDestroy (&poly2);
	PolyDestroy (&poly3);

	WritePoly (poly3);

	return 0;
}

void WritePoly (PtPoly ppol)
{
  int i, degree = PolyDegree (ppol); double coef;

  if (ppol != NULL)
  {
    /* escrita no monitor do coeficiente x^n */
    /* writing on screen the x^n coefficient */
    coef = PolyObserveCoefficient (ppol, degree);
    if (degree > 1) printf ("%5.2f x^%d", coef, degree);
    else if (degree == 1) printf ("%5.2f x", coef);

    /* escrita no monitor dos coeficientes x^n-1 ... x^2 para polinomios com grau > 1 */
    /* writing on screen the x^n-1 ... x^2 coefficients for polynomials with degree > 1 */
    if (degree > 1)
      for (i = degree-1; i > 1; i--)
      {
        coef = PolyObserveCoefficient (ppol, i);
        if (coef >= 0.0) printf (" + %5.2f x^%d", coef, i);
        else printf (" - %5.2f x^%d", fabs(coef), i);
      }

    /* escrita no monitor do coeficiente x para polinomios com grau > 1 */
    /* writing on screen the x coefficient for polynomials with degree > 1 */

    if (degree > 1)
    {
      coef = PolyObserveCoefficient (ppol, 1);
      if (coef >= 0.0) printf (" + %5.2f x", coef);
      else printf (" - %5.2f x", fabs(coef));
    }

    /* escrita no monitor do coeficiente independente */
    /* writing on screen the independent coefficient */
    if (degree > 0)
    {
      coef = PolyObserveCoefficient (ppol, 0);
      if (coef >= 0.0) printf (" + %5.2f\n", coef);
      else printf (" - %5.2f\n", fabs(coef));
    }
    else printf ("%5.2f\n", coef);
  }
}
