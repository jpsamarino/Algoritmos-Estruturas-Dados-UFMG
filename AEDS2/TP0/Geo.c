#include <stdio.h>
#include <stdlib.h>
#include "Geo.h"

void criaPonto(ponto *p, double x, double y)
{
    p->x = x;
    p->y = y;
}
int pontoCoincide(ponto P, ponto Q)
{
    if(P.x==Q.x&&P.y==Q.y)
    {
        return 1;
    }
    return 0;
}
void criaLinha(linha *l, int numVertices, ponto *vertices)
{
    int i,j;
    l->reta_l = (semireta *)malloc((numVertices-1)*sizeof(semireta));
    l->q_retas = (numVertices-1);

    for(j=i=0; i<(numVertices-1); i++)
    {


        if(pontoCoincide(vertices[i],vertices[i+1]))//se os dois pontos seguidos forem iguais desconsidera a reta .
        {
            i++;
            l->q_retas-=1;
        }

        l->reta_l[j].inicio.x = vertices[i].x;//utilizada para a logica se separação por maior y , criando uma semi reta.
        l->reta_l[j].inicio.y = vertices[i].y;

        if(l->reta_l[j].inicio.y>vertices[i+1].y)//logica separação do maior y
        {
            l->reta_l[j].fim.y = l->reta_l[i].inicio.y;
            l->reta_l[j].fim.x = l->reta_l[i].inicio.x;
            l->reta_l[j].inicio.x = vertices[i+1].x;
            l->reta_l[j].inicio.y = vertices[i+1].y;
        }

        else
        {
            l->reta_l[j].fim.x = vertices[i+1].x;
            l->reta_l[j].fim.y = vertices[i+1].y;
        }

        j++;
    }


}
void criaPoligono(poligono *p, int numVertices, ponto *vertices)
{

    int i,j;
    p->reta_p = (semireta *)malloc(numVertices*sizeof(semireta));
    p->q_retas = numVertices;
//*********************************ordena os pontos em semi retas.*****************************************************
    for(j=i=0; i<(numVertices-1); i++)
    {


        if(pontoCoincide(vertices[i],vertices[i+1]))//se os dois pontos seguidos forem iguais desconsidera a reta .
        {
            i++;
            p->q_retas-=1;
        }

        p->reta_p[j].inicio.x = vertices[i].x;//utilizada para a logica se separação por maior y , criando uma semi reta.
        p->reta_p[j].inicio.y = vertices[i].y;

        if(p->reta_p[j].inicio.y>vertices[i+1].y)//logica separação do maior y
        {
            p->reta_p[j].fim.y = p->reta_p[i].inicio.y;
            p->reta_p[j].fim.x = p->reta_p[i].inicio.x;
            p->reta_p[j].inicio.x = vertices[i+1].x;
            p->reta_p[j].inicio.y = vertices[i+1].y;
        }

        else
        {
            p->reta_p[j].fim.x = vertices[i+1].x;
            p->reta_p[j].fim.y = vertices[i+1].y;
        }

        j++;
    }
//*********************************************************************************************************************

//*********************************fecha o poligono em relacao as retas.***********************************************

    if(!pontoCoincide(vertices[i],vertices[0]))
    {
        if(vertices[i].y>vertices[0].y )
        {
            p->reta_p[j].fim.y = vertices[i].y;
            p->reta_p[j].fim.x = vertices[i].x;
            p->reta_p[j].inicio.x = vertices[0].x;
            p->reta_p[j].inicio.y = vertices[0].y;
        }
        else
        {
            p->reta_p[j].fim.y = vertices[0].y;
            p->reta_p[j].fim.x = vertices[0].x;
            p->reta_p[j].inicio.x = vertices[i].x;
            p->reta_p[j].inicio.y = vertices[i].y;


        }

    }
    else
    {
        p->q_retas--;
    }
//*********************************************************************************************************************
}
int posicaorelativa(ponto a , ponto b , ponto c)
{
    double result;
    result = ((b.x-a.x)*(c.y-a.y))-((c.x-a.x)*(b.y-a.y)); // forma eficiente de calculo de determinante 3x3 para o computador, evitando multiplicoes.
    if(result>0)
    {
        return 0;
    }
    if(result<0)
    {
        return 1;
    }
    return 2;

}
int intersecaoespecial(semireta a , semireta b)
{
    int p_relativa[4];
    p_relativa[0]=posicaorelativa(a.inicio,a.fim,b.inicio);
    p_relativa[1]=posicaorelativa(a.inicio,a.fim,b.fim);
    p_relativa[2]=posicaorelativa(b.inicio,b.fim,a.inicio);
    p_relativa[3]=posicaorelativa(b.inicio,b.fim,a.fim);

    if(p_relativa[0]==2&&p_relativa[1]==2&&p_relativa[2]==2&&p_relativa[3]==2) //volta no tempo. cassos especiais
    {

        if(a.inicio.x<b.inicio.x&&a.fim.x>b.inicio.x&&a.inicio.y<b.inicio.y&&a.fim.y>b.inicio.y)
        {
            return 1;
        }
        if(a.inicio.x<b.fim.x&&a.fim.x>b.fim.x&&a.inicio.y<b.fim.y&&a.fim.y>b.fim.y)
        {
            return 1;
        }
        if(b.inicio.x<a.inicio.x&&b.fim.x>a.inicio.x&&b.inicio.y<a.inicio.y&&b.fim.y>a.inicio.y)
        {
            return 1;
        }
        if(b.inicio.x<a.fim.x&&b.fim.x>a.fim.x&&b.inicio.y<a.fim.y&&b.fim.y>a.fim.y)
        {
            return 1;
        }
        if(b.inicio.y==a.inicio.y&&b.fim.y==a.fim.y) //caso mais especial, semi retas sobreposta totalmnete é seguidas.
        {
            if(b.inicio.x==a.inicio.x&&b.fim.x==a.fim.x)
            {
                return 1;
            }
            if(b.inicio.x==a.fim.x&&b.fim.x==a.inicio.x)
            {
                return 1;
            }
        }
        else
        {
            printf(" deu certo");
            return 0;
        }
    }

    return 0;

}
int intersecaoretas(semireta a , semireta b)
{
    int p_relativa[4];
    p_relativa[0]=posicaorelativa(a.inicio,a.fim,b.inicio);
    p_relativa[1]=posicaorelativa(a.inicio,a.fim,b.fim);
    p_relativa[2]=posicaorelativa(b.inicio,b.fim,a.inicio);
    p_relativa[3]=posicaorelativa(b.inicio,b.fim,a.fim);

    if(p_relativa[0]==2&&p_relativa[1]==2&&p_relativa[2]==2&&p_relativa[3]==2) //volta no tempo. cassos especiais
    {

        if(a.inicio.x<=b.inicio.x&&a.fim.x>=b.inicio.x&&a.inicio.y<=b.inicio.y&&a.fim.y>=b.inicio.y)
        {
            return 1;
        }
        if(a.inicio.x<=b.fim.x&&a.fim.x>=b.fim.x&&a.inicio.y<=b.fim.y&&a.fim.y>=b.fim.y)
        {
            return 1;
        }
        if(b.inicio.x<=a.inicio.x&&b.fim.x>=a.inicio.x&&b.inicio.y<=a.inicio.y&&b.fim.y>=a.inicio.y)
        {
            return 1;
        }
        if(b.inicio.x<=a.fim.x&&b.fim.x>=a.fim.x&&b.inicio.y<=a.fim.y&&b.fim.y>=a.fim.y)
        {
            return 1;
        }
        else
        {
            printf("ts3");
            return 0;
        }
    }
    if(p_relativa[0]!=p_relativa[1]&&p_relativa[2]!=p_relativa[3])
    {
        return 1;//retas se cruzao
    }
    return 0;


}
int linhaSimples(linha L)
{
    int i,j;
    for(i=0; i<L.q_retas; i++)
    {
        printf("--%d--\n",L.q_retas);
        for(j=i+2; j<L.q_retas; j++)
        {
            printf("%d %d \n",i,j);
            if(intersecaoretas(L.reta_l[i],L.reta_l[j]))
            {
                printf(" entrou aqui %d %d \n",i,j);
                return 0;
            }
        }
    }
    for(i=0; i<L.q_retas-1; i++)//verifica linhas seguidas para ver se estão sobe escritas
    {
        printf("\neeee%deeee",i);
        if(intersecaoespecial(L.reta_l[i],L.reta_l[i+1]))
        {
            return 0;
        }
    }
    return 1;
}
int poligonoSimples(poligono Pol)
{

    int i,j;

    for(i=0; i<Pol.q_retas; i++)
    {
        for(j=i+2; j<Pol.q_retas-1; j++)
        {
            if(intersecaoretas(Pol.reta_p[i],Pol.reta_p[j]))
            {
                printf("%d %d",i,j);
                return 0;
            }
        }

        if(i==0) Pol.q_retas++;
    }

    return 1;
}
