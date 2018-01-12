#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX 42 // limite logico possivel de numeros para representar um numero complexo.

typedef struct NumeroComplexo_
{
    double real;
    double imaginario;
} NumeroComplexo;

typedef struct MatrizComplexa_
{
    NumeroComplexo** numero;
} MatrizComplexa;

void Aloca (MatrizComplexa *matriz_generica , int qt_coluna , int qt_linha);
void MultiplicaMatriz(MatrizComplexa *matriz_generica_a, MatrizComplexa *matriz_generica_b, MatrizComplexa *matriz_resposta, int qt_coluna_resposta, int qt_linha_resposta ,int qt_coluna_a);

