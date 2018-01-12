#include "lista.h"

void FLVazia(Lista *l)
{

    l->primeiro = (Celula *)malloc(sizeof(Celula)); // aloca a celula cabeça
    l->primeiro -> proximo = NULL; //aloca os apontadores da celula cabeça
    l->primeiro -> anterior = NULL;
    l->primeiro->chave = -1;
    l->fim = l->primeiro;


}
int Busca_l(TipoChave chave, Lista *l, Apontador *celula_v)
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

    *celula_v=celula;// torca de dados entre buffers
    if(celula->chave == chave)
    {
        return i;
    }

    return -1; // retorna -1 se o valor não existir.
}
void busca_l_lfu(Lista *l, Apontador *celula_v) // faz a busca obetendo a celula com menor valor do contador lfu
{
    Apontador celula,buffer;
    celula = l->fim;
    buffer = celula;
    while(celula->anterior != NULL)
    {
        celula = celula->anterior;
        if(buffer->lfu > celula->lfu){
            buffer = celula;
        }
    }
    *celula_v=buffer;

}
void Insere_l(TipoChave x, Apontador posicao,Lista *l,int con_lfu)
{

    Apontador temp;
    temp = (Celula *)malloc(sizeof(Celula)); // aloca espaço da celula.
    temp->proximo = posicao; // aloca apontadores.
    temp->anterior = posicao->anterior;
    posicao->anterior = temp;
    temp->chave = x;
    temp->lfu = con_lfu;
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
void imprime_l(Lista *l)
{

    Apontador celula;
    printf("\n");
    celula = l->primeiro;
    while(celula->proximo != NULL)
    {

        printf("-- %d -- ",celula->chave);
        celula = celula->proximo;

    }
    printf("-- %d -- ",celula->chave);
    printf("\n");

    printf("primeiro %d , ultimo %d \n ",l->primeiro->chave,l->fim->chave);

}
void limpa_l(Lista *l)//exclui tds itens e aloca a celula cabeça novamente
{
    Apontador celula,buffer;
    if(l->primeiro)
        celula = l->primeiro;
    while(celula->proximo != NULL)
    {
        buffer = celula;
        celula = celula->proximo;
        free(buffer); // limpa memoria alocada pela celula

    }
    free(celula);// limpa memoria alocada pela celula
    FLVazia(l); // reinicia a lista

}
