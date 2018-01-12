#include "caminhos.h"

void Aloca (cidade *c)
{
    int i,j;
    c->matriz_custo = (int **) malloc( c->qt_linhas * sizeof( int *) );//aloca as linhas

    for(i=0; i<(c->qt_linhas); i++) //aloca as colunas da matriz
    {
        c->matriz_custo[i]= (int *) malloc( c->qt_colunas * sizeof( int ) );
    }

    for(i=0; i<(c->qt_linhas); i++)
    {
        for(j=0; j<(c->qt_colunas); j++) // coloca o valor de -2 em todas as cedulas da matriz
        {
            c->matriz_custo[i][j] = -2;
        }
    }

    c->matriz_custo[0][0] = 0; // marca o lugar de onde todos os caminhos começam

}
void limpa_estrutura(cidade *c)
{
    int i;
    for(i=0; i<(c->qt_linhas); i++)
    {
        free(c->matriz_custo[i]);
    }
    free(c->matriz_custo);
    c->matriz_custo = NULL;

}
void faz_matriz_custo(cidade *c,int linha,int coluna,int valor)
{
    int flag[4] = {0,0,0,0}; // falgs para chamadas recursivas

    if(linha-1>=0) // a celula acima existe ?
    {
        if(c->matriz_custo[linha-1][coluna]!=-1) // se existir ela e diferente de -1?
        {

            if(c->matriz_custo[linha-1][coluna] == -2 || (c->matriz_custo[linha-1][coluna] > (valor+1)))// ela é uma celula vazia ou uma celula prenchida errada?
            {
                c->matriz_custo[linha-1][coluna] = (valor+1);// então coloque o valor.
                flag[0] = 1;
            }

            else if(valor>(c->matriz_custo[linha-1][coluna]+1)) // parar este caminho pois é invalido
            {
                return ;
            }

        }
    }

    if(coluna+1 < c->qt_colunas) // a celula a direita existe ?
    {
        if(c->matriz_custo[linha][coluna+1]!=-1) // se existir ela e diferente de -1?
        {

            if(c->matriz_custo[linha][coluna+1] == -2 || (c->matriz_custo[linha][coluna+1] > (valor+1)))// ela é uma celula vazia ou uma celula prenchida errada?
            {
                c->matriz_custo[linha][coluna+1] = (valor+1);// então coloque o valor.
                flag[1] = 1;
            }

            else if(valor>(c->matriz_custo[linha][coluna+1]+1)) // parar este caminho pois é invalido
            {
                return ;
            }

        }
    }

    if(linha+1 < c->qt_linhas) // a celula a baixo existe ?
    {
        if(c->matriz_custo[linha+1][coluna]!=-1) // se existir ela e diferente de -1?
        {

            if(c->matriz_custo[linha+1][coluna] == -2 || (c->matriz_custo[linha+1][coluna] > (valor+1)))// ela é uma celula vazia ou uma celula prenchida errada?
            {
                c->matriz_custo[linha+1][coluna] = (valor+1);// então coloque o valor.
                flag[2] = 1;
            }

            else if(valor>(c->matriz_custo[linha+1][coluna]+1)) // parar este caminho pois é invalido
            {
                return ;
            }

        }
    }

    if(coluna-1 >= 0) // a celula a esquerda existe ?
    {
        if(c->matriz_custo[linha][coluna-1]!=-1) // se existir ela e diferente de -1?
        {

            if(c->matriz_custo[linha][coluna-1] == -2 || (c->matriz_custo[linha][coluna-1] > (valor+1)))// ela é uma celula vazia ou uma celula prenchida errada?
            {
                c->matriz_custo[linha][coluna-1] = (valor+1);// então coloque o valor.
                flag[3] = 1;
            }

            else if(valor>(c->matriz_custo[linha][coluna-1]+1)) // parar este caminho pois é invalido
            {
                return ;
            }

        }
    }
//////////////////////Faz as chamadas recursivas///////////////////////
    if(flag[0]!=0) // a cima da celula atual
    {

        faz_matriz_custo(c,(linha-1),coluna,(valor+1));
        teste+=1;
    }
    if(flag[1]!=0) // a direita dacelula atual
    {

        faz_matriz_custo(c,linha,(coluna+1),(valor+1));
        teste+=1;
    }
    if(flag[2]!=0) // a baixo da cedula atual
    {

        faz_matriz_custo(c,(linha+1),coluna,(valor+1));
        teste+=1;
    }
    if(flag[3]!=0)// a esquerda da cedula atual
    {

        faz_matriz_custo(c,linha,(coluna-1),(valor+1));
        teste+=1;
    }


}
void acha_qt_caminhos(cidade *c,int linha,int coluna,int *qt_caminhos)
{
    int flag[4] = {0,0,0,0}; // falgs para chamadas recursivas
    int buffer_valor=999999999; // valor inicial maximo para evitar problemas


    if(c->matriz_custo[linha][coluna]<0)
    {
        return;   //o ponto é valido? se não for ,finaliza.
    }
    else if(c->matriz_custo[linha][coluna]==0)
    {
        *qt_caminhos+=1;
        return;
    }

    if(linha-1>=0 && (c->matriz_custo[linha-1][coluna]>=0)) // a celula acima existe ?
    {
        flag[0]=1;
        buffer_valor=c->matriz_custo[linha-1][coluna];
    }

    if(linha+1 < c->qt_linhas && (c->matriz_custo[linha+1][coluna]>=0)) // a celula a baixo existe ?
    {
        if(c->matriz_custo[linha+1][coluna]<buffer_valor )//ela possui o menor valor do que as anteriores?
        {
            flag[0]=0;
            flag[1]=1;
            buffer_valor=c->matriz_custo[linha+1][coluna];
        }
        else if (c->matriz_custo[linha+1][coluna]==buffer_valor)// ela tem o mesmo valor da menor celula
        {
            flag[1]=1;
        }
    }
    if(coluna+1 < c->qt_colunas && (c->matriz_custo[linha][coluna+1]>=0)) // a celula a direita existe ?
    {
        if(c->matriz_custo[linha][coluna+1]<buffer_valor) //ela possui o menor valor do que as anteriores?
        {
            flag[0]=0;
            flag[1]=0;
            flag[2]=1;
            buffer_valor=c->matriz_custo[linha][coluna+1];
        }
        else if (c->matriz_custo[linha][coluna+1]==buffer_valor)// ela tem o mesmo valor da menor celula
        {
            flag[2]=1;
        }

    }
    if(coluna-1 >= 0 && (c->matriz_custo[linha][coluna-1]>=0)) // a celula a esquerda existe ?
    {
        if(c->matriz_custo[linha][coluna-1]<buffer_valor) //ela possui o menor valor do que as anteriores?
        {
            flag[0]=0;
            flag[1]=0;
            flag[2]=0;
            flag[3]=1;
        }
        else if (c->matriz_custo[linha][coluna-1]==buffer_valor)// ela tem o mesmo valor da menor celula
        {
            flag[3]=1;
        }
    }

//////////////////////////faz as chamadas recursivas ///////////////////////////////////////////////////
    if(flag[0]==1)
    {
        acha_qt_caminhos(c,linha-1,coluna,qt_caminhos);
    }
    if(flag[1]==1)
    {
        acha_qt_caminhos(c,linha+1,coluna,qt_caminhos);

    }
    if(flag[2]==1)
    {
        acha_qt_caminhos(c,linha,coluna+1,qt_caminhos);

    }
    if(flag[3]==1)
    {
        acha_qt_caminhos(c,linha,coluna-1,qt_caminhos);

    }

}

void marca_bloqueio(cidade *c,int linha , int coluna)
{
    c->matriz_custo[linha][coluna] = -1;
}

void imprime(cidade *c)
{
    int i,j;
    for(i=0; i<(c->qt_linhas); i++)
    {
        for(j=0; j<(c->qt_colunas); j++) // coloca o valor de -2 em todas as cedulas da matriz
        {
            printf("%d ",c->matriz_custo[i][j]);
        }
        printf("\n");
    }
}
