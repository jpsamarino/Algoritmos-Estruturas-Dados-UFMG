//***********************João Pedro Samarino******Mat: 2013048933**************************************************
#include "lista.h"

void CriaLista(Lista *l)
{

    int i;
    l->primeiro = (Celula *)malloc(sizeof(Celula)); // aloca a celula cabeça
    l->primeiro -> proximo = (Celula **) malloc((sizeof(Celula*)*q_nivel)); //aloca os apontadores da celula cabeça
    l->primeiro->chave = 99;
    for(i=0; i<q_nivel; i++)
    {
        l->tamanho[i]=0; //tamanho dividido por niveis
        l->ultimo[i] = l->primeiro; // apontando o final de todos os niveis para a primeira celula
        l->primeiro -> proximo[i] = NULL; // zerando a referencia da primeira celula
    }

}
int Busca(int chave, Lista *l, Apontador *ListaH, int imprimir)
{
    int buffer_nivel;
    buffer_nivel = q_nivel-1;
    Apontador buffer_celula;
    buffer_celula = l->primeiro;

    while(buffer_nivel> -1)// entra até buffer_nivel = 0
    {
        if(imprimir!=0 && buffer_celula != l->primeiro)
        {
            printf("\n%d %d",buffer_celula->chave,buffer_nivel);
        }

        while((buffer_celula->proximo[buffer_nivel] != NULL) && (buffer_celula->proximo[buffer_nivel]->chave < chave))
        {
            //atribui valor no buffer apontador até a comparação do valor ser valido.
            buffer_celula = buffer_celula->proximo[buffer_nivel];

            if(imprimir!=0)
            {
                printf("\n%d %d",buffer_celula->chave,buffer_nivel);
            }
        }

        ListaH[buffer_nivel] = buffer_celula; // salva o apontador da celula anterior.


        if((buffer_celula->proximo[buffer_nivel] != NULL) && buffer_celula->proximo[buffer_nivel]->chave == chave && buffer_nivel == 0)
        {
            if(imprimir!=0)
            {
                buffer_celula = buffer_celula->proximo[buffer_nivel];
                printf("\n%d %d",buffer_celula->chave,buffer_nivel);
            }
            return 1; // retorna 1 se o valor ja existir
        }
        buffer_nivel--;//desce um nivel
    }

    return 0; // retorna 0 se o valor não existir.
}
int Insere(int x, int h, Lista *l)
{
    Apontador buffer_inserir[q_nivel] , temp;
    int i;
    i=h+1;

    if(!Busca(x,l,buffer_inserir,0))
    {
        printf("\n-----%d-----",buffer_inserir[0]->chave);
        temp = (Celula *)malloc(sizeof(Celula));
        temp->proximo = (Celula **) malloc((sizeof(Celula*)*i));
        temp->chave = x;

        for(i=0; i<=h; i++)
        {
            temp->proximo[i] = buffer_inserir[i]->proximo[i];
            buffer_inserir[i]->proximo[i] = temp;
            if(temp->proximo[i] == NULL)
            {
                l->ultimo[i] = temp;
            }
            l->tamanho[i]+=1;

        }
    }

    else
    {
        return 0;
    }
    return 1;
}
void imprime(int nivel , Lista *l)
{
    Apontador temp= l->primeiro->proximo[nivel];

    while(temp->proximo[nivel])
    {
        printf("\n%d",temp->chave);
        temp = temp->proximo[nivel];
    }
    printf("\n%d",temp->chave);
}
