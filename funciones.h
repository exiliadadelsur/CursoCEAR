#ifndef FUNCIONES_H
#define FUNCIONES_H

extern void inicializar(struct individuo *population, int N);
extern struct individuo* evaluacion(struct individuo *population, int N, int flag);
extern struct individuo* keep_the_best(struct individuo *population, int N);
extern struct individuo* seleccion(struct individuo *new_poblacion, struct individuo *poblacion, int N);
extern struct individuo* crossover(struct individuo *poblacion, int N, double P_CRUZAMIENTO);
extern struct individuo* mutate(struct individuo *poblacion, int N, double P_MUTACION);

#endif
