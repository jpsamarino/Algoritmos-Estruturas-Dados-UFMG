#include "lista.h"

void FLVazia(Lista *l)
{

    l->primeiro = (Celula *)malloc(sizeof(Celula)); // aloca a celula cabeça
    l->primeiro -> proximo = NULL; //aloca os apontadores da celula cabeça
    l->primeiro -> anterior = NULL;
    l->primeiro->chave = -1;
    l->fim = l->primeiro;


}
Apontador Busca_l(TipoChave chave, Lista *l)
{
    int i; // usado para calcular a eferencia temporal
    i=0;
    Apontador celula;
    celula = l->primeiro;

    while((celula->proximo != NULL) && (celula->chave != chave))
    {
        //atribui valor no buffer apontador até a comparação do valor ser valido.
        celula = celula->proximo;
        i++;
    }

    if(celula->chave == chave)
    {
        return celula;
    }

    return NULL; // retorna -1 se o valor não existir.
}
void Insere_l(TipoChave ind, Apontador posicao,Lista *l,double x, double y)
{

    Apontador temp;
    temp = (Celula *)malloc(sizeof(Celula)); // aloca espaço da celula.
    temp->proximo = posicao; // aloca apontadores.
    temp->anterior = posicao->anterior;
    posicao->anterior = temp;
    temp->chave = ind;
    temp->x = x;
    temp->y = y;

    if(temp->anterior==NULL)
    {
        l->primeiro =  temp;
    }

    else
    {
        temp->anterior->proximo = temp;
    }

    if(posicao->chave == -1)
    {
        temp->proximo = NULL;
        free(posicao);
    }

    if(temp->proximo==NULL)
    {
        l->fim = temp;
    }

}
int Remove_l(Apontador posicao, Lista *l)
{
    if(posicao!=NULL)
    {
        if(posicao->anterior!=NULL)
        {
            posicao->anterior->proximo = posicao->proximo;

        }

        else
        {
            l->primeiro = posicao->proximo;

            if(l->primeiro == NULL)
            {
                FLVazia(l);
                return 1;
            }

        }

        if(posicao->proximo!=NULL)
        {
            posicao->proximo->anterior = posicao->anterior;

        }

        else
        {
            l->fim = posicao->anterior;
        }

        free(posicao);

        return 1;//excluiu com sucesso.
    }

    else
    {
        return -1;//não é possivel excluir
    }

}
void limpa_l(Lista *l,int celula_cabeca)//exclui tds itens e aloca a celula cabeça novamente
{
    Apontador celula,buffer;
    if(l->primeiro)
    {

    celula = l->primeiro;

    while(celula->proximo != NULL)
    {
        buffer = celula;
        celula = celula->proximo;
        free(buffer); // limpa memoria alocada pela celula

    }

    free(celula);// limpa memoria alocada pela celula
    l->primeiro = NULL;
    l->fim = NULL;
    }
    if(celula_cabeca>0)
    {
    FLVazia(l);// reinicia a lista
    }

}
