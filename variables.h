#ifndef VARIABLES_H
#define VARIABLES_H

#define GEN 22					// cantidad de genes por individuo o sea 22, del tipo:
#define NDATOS 15

#define NUM_MIN 0
#define NUM_MAX 4194303

struct lim
{
  double min;
  double max;
};

struct individuo
{
  int **binario;
  double *convertido;
  double fitness;
  double rfitness;
  double cfitness;
};

extern struct lim *limites;
extern struct individuo *population;
extern struct individuo *newpopulation;

extern int POBLACION;
extern int MAX_NUM_GEN;
extern float PXOVER;
extern float PMUTATION;
extern int NUM_GEN;
extern char message[200];

#endif
