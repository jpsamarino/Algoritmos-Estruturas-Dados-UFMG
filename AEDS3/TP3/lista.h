#include<stdlib.h>
#include<stdio.h>

typedef struct _Celula
{
    int chave;
    double x;
    double y;
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
void Insere_l(TipoChave ind, Apontador posicao,Lista *l,double x, double y);
void limpa_l(Lista *l,int celula_cabeca);
int Remove_l(Apontador posicao, Lista *l);
Apontador Busca_l(TipoChave chave, Lista *l);
