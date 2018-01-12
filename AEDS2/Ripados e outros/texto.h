#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef char* TipoChave;

typedef struct TipoRegistro {
  TipoChave Palavra;
  int linha;
  int qt ;
} TipoItem;

typedef struct No_ {
  TipoItem Reg;
  struct No_ *Esq , *Dir;
}No;

typedef No* TipoArvore;
typedef No* Apontador;
int Vazia(TipoArvore arvore);
int Maior(TipoItem a,TipoItem b);
void Insere(TipoItem *x, Apontador *no);
int Busca(TipoChave c, Apontador *no);
void Remove(TipoChave c, Apontador *no);
void Imprime(Apontador no);
