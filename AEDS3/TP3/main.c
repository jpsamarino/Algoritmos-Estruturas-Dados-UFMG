#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

int nova_instancia(FILE *arq)
{
    char b;
    b = getc(arq);

    if(feof(arq)) // chegou no final do arquivo
    {
        return 1;
    }

    if(b!='\n')
    {
        fseek(arq,-sizeof(char),1);
    }
    else
    {
        b = getc(arq);
        if(b!='\n')

        {
            fseek(arq,-1,1);
        }

        else
        {
            return 1;
        }
    }
    return 0;
}

void imprime_dados(FILE *out,Grafo *g,int n_agt)
{
    int i,j;
    if(g->qt_cor>n_agt)
    {
    fprintf(out,"no solution\n");
    }
    else
    {
        for(i=0; i<g->qt_cor; i++)
        {
            for(j=0; j<g->qt_v; j++)
            {
                if(g->cores_f[j]==i)
                {
                    fprintf(out,"%d ",j+1);
                }
            }
            fprintf(out,"\n");
        }
        fprintf(out,"\n");
    }

}
int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "r"); //ponteiros aquivos de entrada e saida
    FILE *out = fopen(argv[2], "w");
    Lista l_buffer;
    Grafo g_buffer;
    int i,num_agentes,identificador;
    double raio_buffer,x,y;

    FLVazia(&l_buffer);

    while(!feof(in)) // repete ate o final do arquivo
    {
        i=0;
        fscanf(in,"%d",&num_agentes);
        fscanf(in,"%lf",&raio_buffer);

        while(!nova_instancia(in))
        {
            if(fscanf(in,"%d %lf %lf",&identificador,&x,&y) != EOF) // se hover valores, inserir na estrutura
            {
                Insere_l(identificador,l_buffer.primeiro,&l_buffer,x,y);
                i++;
            }

        }

        Mont_grafo(&l_buffer,&g_buffer,&raio_buffer,i);

       // heuristica(&g_buffer);

        //forca_bruta_p(&g_buffer);


        forca_bruta(&g_buffer);

        //imprime_dados(out,&g_buffer,num_agentes);
        limpa_l(&l_buffer,1);
        limpa_grafo(&g_buffer);
        i=0;


   }

    limpa_l(&l_buffer,0);
    limpa_grafo(&g_buffer);
    free(&l_buffer);
    free(&g_buffer);
    fclose(in);
    fclose(out);

    /*
    Lista buffer;
    Grafo f;
    Apontador buffer_celula;
    FLVazia(&buffer);
    float raio = 5;
    Insere_l(1,buffer.primeiro,&buffer,-3,3);
    Insere_l(2,buffer.primeiro,&buffer,0,3);
    Insere_l(3,buffer.primeiro,&buffer,3,3);
    Insere_l(4,buffer.primeiro,&buffer,-3,0);
    Insere_l(5,buffer.primeiro,&buffer,0,-5);
    //il(&buffer);
    //buffer_celula = Busca_l(5,&buffer);
    Mont_grafo(&buffer,&f,&raio,5);
    //printf("\npp%dpp",f.indicador[4].primeiro->chave);
    //permuta_forca_bruta(&f,&j,0);
    forca_bruta(&f);
    heuristica(&f);
    forca_bruta_p(&f);
    //colore_grafo(&f,&j);
    printf("%d %d %d %d %d \n",f.cores_f[0],f.cores_f[1],f.cores_f[2],f.cores_f[3],f.cores_f[4]);
    printf(" 888 %d 888",f.qt_cor);
    ip(&f);
    //Remove_l(mp->pagina.fim,&(mp->pagina));
    //Busca_l(indicador_valido,&(mp->pagina),&buffer_celula);
    //Insere_l(indicador_valido,mp->pagina.primeiro,&(mp->pagina),0);*/
    return 0;
}
