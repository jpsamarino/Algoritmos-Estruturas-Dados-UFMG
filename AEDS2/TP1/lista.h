//***********************João Pedro Samarino******Mat: 2013048933**************************************************
#include<stdlib.h>
#include<stdio.h>
#define q_nivel 5

typedef struct _Celula{
    int chave;
    struct _Celula ** proximo;
}Celula;

typedef Celula* Apontador;

typedef struct{

  Apontador primeiro,ultimo[q_nivel];
  int tamanho[q_nivel];
}Lista;
void imprime(int nivel, Lista *l);
void CriaLista(Lista *l);
void FLVazia(Lista *lista);
int Vazia(Lista lista);
int Busca(int chave, Lista *l, Apontador *ListaH, int imprimir);
int Insere(int chave, int h, Lista *l);
