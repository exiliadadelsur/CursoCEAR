#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <omp.h>

#include "variables.h"
#include "colores.h"
#include "funciones.h"


/******************************************************************************************************************************************/
static double binario_to_doble(int *binario, struct lim l)
{
  int k;
  int suma, exponente, numero;
  double decimal;

  suma = 0;
  decimal = 0;
  for (k = 0; k < GEN; k++)
  {
     numero = binario[k];
     exponente = (GEN - 1) - k;  
     suma = (numero) * pow(2, exponente);
     decimal += suma;  
  }

  return (l.max - l.min) * (decimal - (double)NUM_MIN) / ((double)NUM_MAX - (double)(NUM_MIN)) + l.min;
} 

/******************************************************************************************************************************************/

extern void inicializar(struct individuo *poblacion, int N)
{

  int i, k, j;
  int seed = 12345;

  srand(seed);  // La función srand() se utiliza para especificar la semilla de rand()

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < NUM_GEN; j++)
    {
      for (k = 0; k < GEN; k++)
        poblacion[i].binario[j][k] = rand() % 2;  // 0 o 1 de forma aleatoria
      poblacion[i].convertido[j] = binario_to_doble(poblacion[i].binario[j], limites[j]);
    }
  }

  return;
}

/******************************************************************************************************************************************/
extern struct individuo* keep_the_best(struct individuo *poblacion, int N)
{
  int i, best_position;
  double best_fitness;
  struct individuo best_individuo;

  best_position = 0;
  best_fitness  = poblacion[0].fitness;

  for(i=1;i<N;i++)
  {
    if (poblacion[i].fitness < best_fitness) 
    {
	best_position = i;
	best_fitness  = poblacion[i].fitness;
    }
  }
  
  // SWAP
  best_individuo = poblacion[best_position];
  poblacion[N-1] = best_individuo;

  return poblacion;
}

/******************************************************************************************************************************************/
extern struct individuo* seleccion(struct individuo *new_poblacion, struct individuo *poblacion, int N)
{
    int i, j;
    double sum, p;

    // Fitness total
    sum = 0;
    for (i = 0; i < N; i++)
        sum += poblacion[i].fitness;
   // Fitness relativo 
    for (i = 0; i < N; i++) 
        poblacion[i].rfitness = poblacion[i].fitness / sum;

    // Fitness acumulativo
    poblacion[0].cfitness = poblacion[0].rfitness;
    for (i = 1; i < N; i++)
        poblacion[i].cfitness = poblacion[i - 1].cfitness + poblacion[i].rfitness;

    // Selección por ruleta
    for (i = 0; i < N-1; i++)
    {
        p = (double)rand() / (RAND_MAX + 1.0); 

        while(1)
        {
	    j = (rand() % (N - 1)) + 1; 
            if (p < poblacion[j].cfitness)
            {
                new_poblacion[i] = poblacion[j];
                break;
            }
        }
    }

    // Asegura que el último individuo sea el mejor
    new_poblacion[N - 1] = poblacion[N - 1];

    return new_poblacion;
}
/******************************************************************************************************************************************/
//  cruce de bits
static void swap(int *x, int *y)
{
  int temp= *x;
  *x = *y;
  *y = temp;
  return;
}


/******************************************************************************************************************************************/
// cruce de los dos padres seleccionados.
static int Xover(int uno, int dos, int igen, struct individuo *poblacion)
{
  int i, cruzamientos;
  int puntocruce = (rand() % (GEN - 1)) + 1; 
	
  // select crossover point
  cruzamientos = 0;
  for (i = 0; i < puntocruce; i++)
  {
    swap(&poblacion[uno].binario[igen][i], &poblacion[dos].binario[igen][i]);
    cruzamientos++;
  }
		
  return cruzamientos;
}
/******************************************************************************************************************************************/
extern struct individuo*  crossover(struct individuo *poblacion, int N, double P_CRUZAMIENTO)
{
  double x;
  int mem, uno;
  int cruzamientos, ngen;
  
  cruzamientos = 0;
  for(ngen = 0; ngen<NUM_GEN; ngen++)
  {
    uno = -1;
    for(mem = 0; mem < N; ++mem)
    {
      x = rand()%1000/1000.0;

      if (x < P_CRUZAMIENTO)
      {
	if (uno != -1)
        {
          cruzamientos += Xover(uno, mem, ngen, poblacion);
          uno = -1;
	}else{
	  uno = mem;
	}
      } 
    } // For N
  } // For NUM_GEN

  return poblacion;
}

/******************************************************************************************************************************************/
extern struct individuo*  mutate(struct individuo *poblacion, int N, double P_MUTACION)
{
  int i, j, ngen, mutaciones;
  double x;

  mutaciones = 0;
  for(ngen = 0; ngen<NUM_GEN; ngen++)
  {
    for (i = 0; i < N; i++)
    {
      for (j = 0; j < GEN; j++)
      {
	x = rand()%1000/1000.0;
	if (x < P_MUTACION)
        {
	  if(poblacion[i].binario[ngen][j]==0)
          {
	    poblacion[i].binario[ngen][j] = 1;
	  }else{
	    poblacion[i].binario[ngen][j] = 0;
	  }
	  mutaciones++;
        }
      }
    }
  }

  return poblacion;
}
/******************************************************************************************************************************************/
extern struct individuo* evaluacion(struct individuo *poblacion, int N, int flag)
{
    int i, j;
    double ferr, x, cont_c, y, cont_s, tot[NDATOS];
    double xdatos[NDATOS] = {1.42392490e+11, 2.63119934e+11, 4.86206116e+11, 8.98435873e+11,1.66017455e+12, 3.06775320e+12, 5.66874713e+12, 1.04749932e+13,1.93562141e+13, 3.57673763e+13, 6.60927391e+13, \
                         1.22129455e+14, 2.25676888e+14, 4.17016992e+14, 7.70584763e+14};
    double ydatos[NDATOS] = {0.31726043, 0.94421803, 1.15859209, 1.38576918, 1.94892396, 2.97030081, 4.65384047, 7.62377137, 12.56310207, 21.48565544, \
			35.30724591, 61.79522784, 106.46452163, 174.61538462, 293.5 }; 


    for (i = 0; i < N; i++)
    {
        if (flag == 1)
          for (j = 0; j < NUM_GEN; j++)
            poblacion[i].convertido[j] = binario_to_doble(poblacion[i].binario[j], limites[j]);

	poblacion[i].fitness = 0;

        for (j = 0; j < NDATOS; j++)
        {
            x = (log10(xdatos[j]) - log10(pow(10,poblacion[i].convertido[0]))) / poblacion[i].convertido[1];
            ferr = erf(x);
            cont_c = (double)0.5 * ((double)1 + ferr);
	    
	    if ((xdatos[j] >  pow(10,poblacion[i].convertido[2])) )//&& (pow(10,poblacion[i].convertido[3]) > pow(10,poblacion[i].convertido[2])))
	    {
            y = (xdatos[j] - pow(10,poblacion[i].convertido[2])) / (pow(10,poblacion[i].convertido[3]) - pow(10,poblacion[i].convertido[2]));
            cont_s = pow(y, poblacion[i].convertido[4]);
	    }else{
	    cont_s = 0.0;}
	 
            tot[j] = cont_c + cont_s;
	//    printf("Individuo %d ", i);
        //    printf("tiene %lf de galaxias ",tot[j]);
        //    printf("en el bin %d\n", j);

	    poblacion[i].fitness +=  ((tot[j] - ydatos[j])*(tot[j] - ydatos[j])) / (ydatos[j]) ;  
	   
        }
	poblacion[i].fitness = (poblacion[i].fitness/(double)(NDATOS-1-NUM_GEN)); 
	printf("El fitness del individuo %d es %lf\n",i,poblacion[i].fitness);

    }

    return poblacion;
}


/******************************************************************************************************************************************/

