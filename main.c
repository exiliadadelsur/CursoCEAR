#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <omp.h>

#include "variables.h"
#include "timer.h"
#include "colores.h"
#include "io.h"
#include "allocate.h"
#include "funciones.h"


int generacion = 0;
struct individuo mejorind, aa_mejorind;

int main(int argc, char **argv)
{
  
  init_variables(argc,argv);

  if(!allocate_individuos(&population)) exit(1);
  if(!allocate_individuos(&newpopulation)) exit(1);
  printf("Se inicializa la población \n");
  inicializar(population, POBLACION);   
  population = evaluacion(population, POBLACION, 0);
  population = keep_the_best(population, POBLACION);

  while(generacion<MAX_NUM_GEN)
  {  
    printf("Generacion %d\n", generacion);
    //printf("El mejor fit anterior %lf\n", population[POBLACION-1].fitness);

    newpopulation = seleccion(newpopulation, population, POBLACION);

    newpopulation = crossover(newpopulation, POBLACION, PXOVER);
    newpopulation = mutate(newpopulation, POBLACION, PMUTATION);
    newpopulation = evaluacion(newpopulation, POBLACION, 1);
    newpopulation = keep_the_best(newpopulation, POBLACION);
    //printf("mejor fit actual %lf\n", newpopulation[POBLACION-1].fitness);

   if (population[POBLACION-1].fitness < newpopulation[POBLACION-1].fitness)
   {
    newpopulation[POBLACION-1] = population[POBLACION-1];
    printf("Se hizo cambio del último individuo por el de la generación anterior\n");
}
    
    if(newpopulation[POBLACION-1].fitness < 0.15) 
{
    sprintf(message,"			Se converge en la generacion %d\n",generacion);GREEN(message);
    sprintf(message,"	          El fitness del mejor individuo es: %lf\n",newpopulation[POBLACION-1].fitness);YELLOW(message);
    sprintf(message,"                          El valor de Mmin es %lf\n",newpopulation[POBLACION-1].convertido[0]);CYAN(message);
    sprintf(message,"                       El valor de sigmalogM es %lf\n",newpopulation[POBLACION-1].convertido[1]);CYAN(message);
    sprintf(message,"                          El valor de Mcut es %lf\n",newpopulation[POBLACION-1].convertido[2]);CYAN(message);
    sprintf(message,"                           El valor de M1 es %lf\n",newpopulation[POBLACION-1].convertido[3]);CYAN(message);
    sprintf(message,"                         El valor de alpha es %lf\n",newpopulation[POBLACION-1].convertido[4]);CYAN(message);

    break;
}
    generacion++;
 
    for (int i = 0; i < POBLACION - 1; i++) 
    {
    double x = (rand() % 1000) / 1000.0;
    if (x < 0.2) {
        population[i] = newpopulation[i];
    }
    }

   population[POBLACION - 1] = newpopulation[POBLACION - 1];

  }

    if (generacion >= MAX_NUM_GEN)
    {
    sprintf(message,"No se logró la convergencia solicitada en las %d generaciones\n", generacion);RED(message);
    }


  //free_individuos(&population);
  //free_individuos(&newpopulation);

  return(EXIT_SUCCESS);
}
