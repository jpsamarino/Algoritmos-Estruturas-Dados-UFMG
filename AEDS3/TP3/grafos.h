#include "lista.h"
#include <math.h>
#include <pthread.h>
#define limit_p 2

typedef struct
{
    Lista* indicador;
    int *cores, *cores_f;
    int qt_v;
    int qt_cor;

} Grafo;

typedef struct
{
    Grafo g;
    int *buffer;

} Paralelo;
