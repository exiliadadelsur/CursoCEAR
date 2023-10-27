#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "variables.h"
#include "colores.h"

extern void init_variables(int argc, char **argv)
{
  FILE *pfin;
  char filename[200];
  int i;

  RED("Initializing variables...\n");

  sprintf(filename,"%s",argv[1]);
  if(!(pfin=fopen(filename,"r")))
  {
    sprintf(message,"can't open file `%s` \n",filename);RED(message);
    exit(0);
  }

  if(!fscanf(pfin,"%d  \n",&POBLACION))
  {
    sprintf(message,"can't read file `%s`\nneed POBLACION\n",filename);RED(message);
    exit(0);
  }
    
  if(!fscanf(pfin,"%d  \n",&MAX_NUM_GEN))
  {
    sprintf(message,"can't read file `%s`\nneed MAX_NUM_GEN\n",filename);RED(message);
    exit(0);
  }

  if(!fscanf(pfin,"%f  \n",&PXOVER))
  {
    sprintf(message,"can't read file `%s`\nneed PXOVER\n",filename);RED(message);
    exit(0);
  }

  if(!fscanf(pfin,"%f \n",&PMUTATION))
  {
    sprintf(message,"can't read file `%s`\nneed PMUTATION\n",filename);RED(message);
    exit(0);
  }

  if(!fscanf(pfin,"%d \n",&NUM_GEN))
  {
    sprintf(message,"can't read file `%s`\nneed NUM_GEN\n",filename);RED(message);
    exit(0);
  }

  limites = (struct lim *) malloc(NUM_GEN*sizeof(struct lim));

  for(i=0; i< NUM_GEN; i++)
  {
    if(!fscanf(pfin,"%lf  \n",&limites[i].min))
    {
      sprintf(message,"can't read file `%s`\n Gen %d need min\n",filename,i);RED(message);
      exit(0);
    }

    if(!fscanf(pfin,"%lf \n",&limites[i].max))
    {
      sprintf(message,"can't read file `%s`\n Gen %d need max\n",filename,i);RED(message);
      exit(0);
    }
  }

  BLUE("********** Information ***********\n");
  sprintf(message,"POBLACION   %d\n",POBLACION);BLUE(message);
  sprintf(message,"MAX_NUM_GEN %d\n",MAX_NUM_GEN);BLUE(message);
  sprintf(message,"PXOVER      %f\n",PXOVER);BLUE(message);
  sprintf(message,"PMUTATION   %f\n",PMUTATION);BLUE(message);
  sprintf(message,"NUM_GEN     %d\n",NUM_GEN);BLUE(message);

  for(i=0; i<NUM_GEN; i++)
  {  
    sprintf(message,"GEN %d - %.4lf Min %.4lf Max\n",i,limites[i].min,limites[i].max);YELLOW(message);
  }
 
  GREEN("END\n");
}

