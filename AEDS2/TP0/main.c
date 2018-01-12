#include <stdio.h>
#include <stdlib.h>
#include "Geo.h"

int main()
{

    int q_pt,q_l,q_p,q_pt_p,q_pt_l,i,j;
    double x,y;//variaveis buffers para pontos.
    ponto *buffer_pt;//buffer para pontos capturados na main.
    //printf("%d",((1^0)&(1^0)));

    //*******************************Captura pontos no plano********************************************
    scanf("%d",&q_pt);
    ponto pt_plano[q_pt];
    for(i=0; i<q_pt; i++)
    {
        scanf("%lf",&x);
        scanf("%lf",&y);
        criaPonto(&pt_plano[i],x,y);
        printf("pt - X%lf Y%lf\n",pt_plano[i].x,pt_plano[i].y);
    }
    //***************************************************************************************************

    //*******************************Captura linhas no plano*********************************************

    scanf("%d",&q_l);
    linha l_plano[q_l];
    for(i=0; i<q_l; i++)
    {
        scanf("%d",&q_pt_l);
        buffer_pt = (ponto *)malloc(q_pt_l*sizeof(ponto));

        for(j=0; j<q_pt_l; j++)
        {
            scanf("%lf",&x);
            scanf("%lf",&y);
            criaPonto(&buffer_pt[j],x,y);
            printf("--pt - X%lf Y%lf\n",buffer_pt[j].x,buffer_pt[j].y);
        }

        criaLinha(&l_plano[i],q_pt_l,buffer_pt);

        free(buffer_pt);//limpa a memoria do buffer para realocar novamente

        for(j=0; j<l_plano[i].q_retas; j++)
        {
            printf("l%d %lf-%lf",i,l_plano[i].reta_l[j].inicio.x,l_plano[i].reta_l[j].inicio.y);
            printf("--%lf-%lf\n",l_plano[i].reta_l[j].fim.x,l_plano[i].reta_l[j].fim.y);
        }

    }
    //***************************************************************************************************

    //*******************************Captura poligono no plano********************************************

    scanf("%d",&q_p);
    poligono p_plano[q_p];
    for(i=0; i<q_p; i++)
    {
        scanf("%d",&q_pt_p);
        buffer_pt = (ponto *)malloc(q_pt_p*sizeof(ponto));

        for(j=0; j<q_pt_p; j++)
        {
            scanf("%lf",&x);
            scanf("%lf",&y);
            criaPonto(&buffer_pt[j],x,y);
            printf("--pt - X%lf Y%lf\n",buffer_pt[j].x,buffer_pt[j].y);
        }

        criaPoligono(&p_plano[i],q_pt_p,buffer_pt);

        free(buffer_pt);//limpa a memoria do buffer para realocar novamente

        for(j=0; j<p_plano[i].q_retas; j++)
        {
            printf("p%d %lf-%lf",i,p_plano[i].reta_p[j].inicio.x,p_plano[i].reta_p[j].inicio.y);
            printf("--%lf-%lf\n",p_plano[i].reta_p[j].fim.x,p_plano[i].reta_p[j].fim.y);
        }

    }
    //***************************************************************************************************

printf("a linha 1 e %d\n",linhaSimples(l_plano[0]));
printf("o p 1 e %d",poligonoSimples(p_plano[0]));
    return 0;
}
