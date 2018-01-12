#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX 42

int teste;
typedef struct cidade_
{
  int** matriz_custo;
  int qt_linhas; // quantidade de ruas
  int qt_colunas; // quantidade de avenidas

}cidade;

void Aloca (cidade *c);
void limpa_estrutura(cidade *c);
void faz_matriz_custo(cidade *c,int linha,int coluna,int valor);
void acha_qt_caminhos(cidade *c,int linha,int coluna,int *qt_caminhos);
void marca_bloqueio(cidade *c,int linha , int coluna);
