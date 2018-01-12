#include "lista.h"

typedef struct
{
    int tamanho_total;
    int tamanho_pagina;
    int qt_paginas_atual;
    Lista pagina;

} Memoria_principal;


int insere_lru(Memoria_principal* mp, int indicador);
int insere_fifo(Memoria_principal* mp, int indicador);
int insere_nova(Memoria_principal* mp, int indicador);
int insere_lfu(Memoria_principal* mp, int indicador);
int referencia_espacial(int tamanho_p,int inicio , int fim);
void prepara_memoria(Memoria_principal* mp, int tamanho_p, int tamanho_t);
void limpa_memoria(Memoria_principal* mp);
