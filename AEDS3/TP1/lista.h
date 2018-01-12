#include<stdlib.h>
#include<stdio.h>

typedef struct _Celula
{
    int chave;
    int lfu;
    struct _Celula * proximo;
    struct _Celula * anterior;

} Celula;

typedef Celula* Apontador;

typedef struct
{
    Apontador primeiro;
    Apontador fim;

} Lista;

typedef int TipoChave;


void FLVazia(Lista *l);
void Insere_l(TipoChave x, Apontador posicao,Lista *l,int con_lfu);
void limpa_l(Lista *l);
void busca_l_lfu(Lista *l, Apontador *celula_v);
int Remove_l(Apontador posicao, Lista *l);
int Busca_l(TipoChave chave, Lista *l, Apontador *celula);
