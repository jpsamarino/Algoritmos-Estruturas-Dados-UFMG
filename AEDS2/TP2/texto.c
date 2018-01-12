#include "texto.h"
int Maior(TipoItem a,TipoItem b)
{
    int a_t,b_t,i,j;

    a_t = strlen(a.Palavra);
    b_t = strlen(b.Palavra);

    if(a_t>=b_t)
    {
        i=b_t;
    }
    else
    {
        i=a_t;
    }
    for(j=0; j<i; j++)
    {
        if(a.Palavra[j]>b.Palavra[j])
        {
            return 1;   // a é maior q b , se a e o anterior vai para esquerda
        }
        else if(a.Palavra[j]<b.Palavra[j])
        {
            return 2;   // b é maior q a ,se a e o anterior vai para direita
        }
    }
    if(a_t>b_t)
    {
        return 1;   // a é maior q b
    }
    else if(a_t<b_t)
    {
        return 2;   // b é maior q a
    }
    return 0;
}
void Insere(TipoItem *x, Apontador *no)
{
    if ((*no) == NULL)
    {
        printf("1\n");
        (*no) = (Apontador)malloc(sizeof(No));
        (*no)->Reg.Palavra = (TipoChave)malloc(sizeof(char)*(strlen(x->Palavra)+1));
        strcpy((*no)->Reg.Palavra,x->Palavra);
        (*no)->Reg.qt = 1;
        (*no)->Esq = NULL;
        (*no)->Dir = NULL;
        return;
    }

    if (Maior((*no)->Reg,*x)==1)
    {
        printf("esquerda de %s\n",(*no)->Reg.Palavra);
        Insere(x,&(*no)->Esq);
        return;
    }
    else if (Maior((*no)->Reg,*x)==2)
    {
        printf("direita de %s\n",(*no)->Reg.Palavra);
        Insere(x,&(*no)->Dir);
        return;
    }

    else
    {
        (*no)->Reg.qt+=1;
        return;
    }
}
void Imprime(Apontador no)
{
    if(no!=NULL)
    {
        Imprime(no->Esq);
        printf("%s %d\n",no->Reg.Palavra,no->Reg.qt);
        Imprime(no->Dir);
    }
}
int Busca(TipoChave c, Apontador no)
{
    TipoItem buffer;
    buffer.Palavra = c;

    if(no==NULL){printf("false\n"); return 0;}
    if (Maior(no->Reg,buffer)==1)
    {
        printf("%s %d\n",no->Reg.Palavra,no->Reg.qt);
        Busca(c,no->Esq);
        return 1;
    }
    else if (Maior(no->Reg,buffer)==2)
    {
        printf("%s %d\n",no->Reg.Palavra,no->Reg.qt);
        Busca(c,no->Dir);
        return 1;
    }

    else
    {   printf("%s %d\n",no->Reg.Palavra,no->Reg.qt);
        printf("true\n");
        return 1;
    }


return 0;
}
