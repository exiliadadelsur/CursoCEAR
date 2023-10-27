# CursoCEAR
Algoritmo genético implementado en la parametrización de la distribución de halos de materia oscura.

Para compilar:
```
    make 
```
Para ejecutar:
```
    ./main config.param
```
Para eliminar los archivos generados: 
```
 make clean
```
En el archivo **config.param** pueden editarse los parámetros de entrada. 
Los mismos se encuentran ordenados de la siguiente manera:

   * POBLACION: Número de individuos
   * MAX\_NUM\_GEN: Máximo número de generaciones
   * PXOVER: Probabilidad de cruzamiento
   * PMUTATION: Probabilidad de mutación
   * NUM\_GEN: Número de genes que tiene cada individuo
   * Límite inferior de $M_{min}$
   * Límite superior de $M_{min}$
   * Límite inferior de $\sigma_{logM}$
   * Límite superior de $\sigma_{logM}$
   * Límitee inferior de $M_{cut}$
   * Límite superior de $M_{cut}$
   * Límite inferior de $M_{1}$
   * Límite superior de $M_{1}$
   * Límite inferior de $\alpha$
   * Límite superior de $\alpha$
