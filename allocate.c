#include <stdlib.h>
#include <stdio.h>
#include "variables.h"
#include "allocate.h"

extern int allocate_individuos(struct individuo **P)
{

  *P = NULL;

  *P = (struct individuo *) malloc(POBLACION*sizeof(struct individuo));

  if(!*P) 
  {
    fprintf(stderr, "cannot allocate individuos\n" );
    return 0;
  }    

  // Ahora asignamos memoria para el gen de cada individuo.
  for (int i = 0; i < POBLACION; i++) 
  {
    (*P)[i].binario    = (int **)   malloc(NUM_GEN * sizeof(int  *));
    (*P)[i].convertido = (double *) malloc(NUM_GEN * sizeof(double));

    if (!(*P)[i].binario) 
    {
      fprintf(stderr, "cannot allocate memory for binario[%d]\n", i);
      return 0;
    }

    for (int j = 0; j < NUM_GEN; j++) 
    {
      (*P)[i].binario[j] = (int *) malloc(GEN * sizeof(int));
      if (!(*P)[i].binario[j]) 
      {
        fprintf(stderr, "cannot allocate memory for binario[%d][%d]\n", i, j);
        return 0;
      }
    }
  }

  return 1;
}

extern void free_individuos(struct individuo **P)
{
  for (int i = 0; i < POBLACION; i++) 
  {
    for (int j = 0; j < NUM_GEN; j++)
      free((*P)[i].binario[j]);
    free((*P)[i].convertido);
    free((*P)[i].binario);
  }
  if(*P) free(*P);
}
