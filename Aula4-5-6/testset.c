#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "set.h"

void WriteSet (PtSet);

int main (void)
{
	PtSet set1 = NULL, set2 = NULL, set3 = NULL;
	char filename[21], car; int st;

	system ("clear");

	printf ("\nLer conjunto do ficheiro - Read set from a text file\n");
	do
	{
  		printf ("Nome do ficheiro (Filename) -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);

	set1 = SetCreateFile (filename);
	printf ("\nConjunto lido do ficheiro - Set acquired from text file %s\n", filename);
	WriteSet (set1);

	printf ("\nLer conjunto do teclado [# para terminar] - Read set from keyboard [# to stop]\n");
	set2 = SetCreate ();
	do
	{
		do
		{
			printf ("Elemento do conjunto (Set's element) ? "); st = scanf ("%c", &car);
			scanf ("%*[^\n]"); scanf ("%*c");
		} while (st == 0);
		car = toupper (car);
		if (isupper(car)) SetInsertElement (set2, car);
	} while (car != '#');

	printf ("\nConjunto lido do teclado - Set acquired from keyboard\n");
	WriteSet (set2);

	printf ("\nEscrever conjunto no ficheiro - Storing the set in a text file\n");
	do
	{
  		printf ("Nome do ficheiro (Filename) -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);
	SetStoreFile (set2, filename);

	set3 = SetReunion (set1, set2);
	printf ("\nConjunto Reuniao - Union set\n");
	WriteSet (set3);

	SetDestroy (&set3);
	set3 = SetIntersection (set1, set2);
	printf ("\nConjunto Interseccao - Intersection set\n");
	WriteSet (set3);

	SetDestroy (&set3);
	set3 = SetSymmetricDifference (set1, set2);
	printf ("\nConjunto Diferença - Symmetric Difference set\n");
	WriteSet (set3);

	printf ("\nDestruir os conjuntos - Releasing the sets\n");
	SetDestroy (&set1);
	SetDestroy (&set2);
	SetDestroy (&set3);

	WriteSet (set3);

	return 0;
}

void WriteSet (PtSet pset)
{
  unsigned int cardinal, i;

  if (pset == NULL) return;  /* verifica se o conjunto existe - verifies if set exists */

  cardinal = SetCardinal (pset);

  printf ("{ ");

  /* escrita no monitor dos elementos do conjunto - writing on screen the set's elements */
  for (i = 1; i <= cardinal; i++) printf ("%c ", SetObserveElement (pset, i));
  printf ("}\n");
}
