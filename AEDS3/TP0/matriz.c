#include "matriz.h"

void Aloca (MatrizComplexa *matriz_generica , int qt_coluna , int qt_linha)
{
    int i;
    matriz_generica->numero = (NumeroComplexo **) malloc( qt_linha * sizeof( NumeroComplexo *) );//aloca as linhas

    for(i=0; i<qt_linha; i++) //aloca as colunas da matriz
    {
        matriz_generica->numero[i]= (NumeroComplexo *) malloc( qt_coluna * sizeof( NumeroComplexo ) );
    }

}
void MultiplicaMatriz(MatrizComplexa *matriz_generica_a, MatrizComplexa *matriz_generica_b, MatrizComplexa *matriz_resposta, int qt_coluna_resposta, int qt_linha_resposta ,int qt_coluna_a)
{
    int linha ,coluna, comum; // variaveis para operaçoes internas
    NumeroComplexo buffer;
    buffer.imaginario=0;
    buffer.real=0;


    for ( linha = 0; linha < qt_linha_resposta; linha++)//varre linha
    {
        for ( coluna = 0; coluna < qt_coluna_resposta; coluna++)//varre coluna
        {
            for ( comum = 0; comum < qt_coluna_a; comum++)//realiza as operaçoes
            {
                buffer.real+=(matriz_generica_a->numero[linha][comum].real*matriz_generica_b->numero[comum][coluna].real)-(matriz_generica_a->numero[linha][comum].imaginario*matriz_generica_b->numero[comum][coluna].imaginario);
                buffer.imaginario+=(matriz_generica_a->numero[linha][comum].real*matriz_generica_b->numero[comum][coluna].imaginario)+(matriz_generica_b->numero[comum][coluna].real*matriz_generica_a->numero[linha][comum].imaginario);

            }

            matriz_resposta->numero[linha][coluna].real=buffer.real; //manda o valor final para a variavel resposta
            matriz_resposta->numero[linha][coluna].imaginario=buffer.imaginario;

            buffer.real=0; // zera os buffers
            buffer.imaginario=0;

        }
    }

}

