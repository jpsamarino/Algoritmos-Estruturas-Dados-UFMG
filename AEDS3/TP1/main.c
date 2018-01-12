#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"

int main(int argc, char *argv[])
{

    FILE *in = fopen(argv[1], "r"); //ponteiros aquivos de entrada e saida
    FILE *out = fopen(argv[2], "w");
    Memoria_principal mp_fifo,mp_lru,mp_lfu,mp_nova; //declarando memorias a serem usadas
    int qt_instancias,t,i,buffer,faltas[4],*ref_espacial,buffer_espacial,*ref_temporal; // variaveis usadas na funcão principal


    fscanf(in,"%d",&qt_instancias); //captura a qt de instancias

    while(qt_instancias) //loop para executar todas as operaçoes
    {
        fscanf(in,"%d",&mp_fifo.tamanho_total); //captura a dimensão das matriz A
        fscanf(in,"%d",&mp_fifo.tamanho_pagina);

        mp_lru.tamanho_pagina=mp_fifo.tamanho_pagina; //definindo o tamanho das memorias e das paginas
        mp_lru.tamanho_total=mp_fifo.tamanho_total;
        mp_lfu.tamanho_pagina=mp_fifo.tamanho_pagina;
        mp_lfu.tamanho_total=mp_fifo.tamanho_total;
        mp_nova.tamanho_pagina=mp_fifo.tamanho_pagina;
        mp_nova.tamanho_total=mp_fifo.tamanho_pagina;

        faltas[0] = 0; // zerando os contadores de falta
        faltas[1] = 0;
        faltas[2] = 0;
        faltas[3] = 0;

        prepara_memoria(&mp_lru, mp_fifo.tamanho_pagina,mp_fifo.tamanho_total);//preparando memoria para ser usada
        prepara_memoria(&mp_lfu, mp_fifo.tamanho_pagina,mp_fifo.tamanho_total);
        prepara_memoria(&mp_nova, mp_fifo.tamanho_pagina,mp_fifo.tamanho_total);
        prepara_memoria(&mp_fifo, mp_fifo.tamanho_pagina,mp_fifo.tamanho_total);

        fscanf(in,"%d",&i); // captura quantidade de leituras a serem realizadas

        ref_temporal = (int *)malloc(sizeof(int)*i); // locando vetores que iram guardar as referencias temporais e locais
        ref_espacial = (int *)malloc(sizeof(int)*(i-1));

        for(t=0; t<i; t++) // loop de captura e processamento
        {

            fscanf(in,"%d",&buffer);
            ref_temporal[t] = insere_lru(&mp_lru,buffer);

            if(insere_fifo(&mp_fifo,buffer)==-1)
            {
                faltas[0]+=1;
            }
            if(insere_lfu(&mp_lfu,buffer)==-1)
            {
                faltas[1]+=1;
            }
            if(insere_nova(&mp_nova,buffer)==-1)
            {
                faltas[2]+=1;
            }
            if(ref_temporal[t]==-1)
            {
                faltas[3]+=1;
            }

            if(t!=0)
            {
                ref_espacial[(t-1)] = referencia_espacial(mp_fifo.tamanho_pagina,buffer_espacial,buffer);
            }

            buffer_espacial = buffer; // atribuicao para calcular a referencia espacial no mesmo loop

        }


        fprintf(out,"%d %d %d %d \n",faltas[0],faltas[1],faltas[2],faltas[3]);

        for(t=0; t<(i-1); t++) // imprime a referencia espacial
        {
            fprintf(out,"%d ",ref_espacial[t]);
        }

        fprintf(out,"\n");

        for(t=0; t<i; t++) // imprime a referencia temporal
        {
            fprintf(out,"%d ",ref_temporal[t]);
        }

        fprintf(out,"\n");

        limpa_memoria(&mp_lru);//limpa a memoria para uma proxima instancia
        limpa_memoria(&mp_lfu);
        limpa_memoria(&mp_nova);
        limpa_memoria(&mp_fifo);
        free(ref_espacial); //limpa buffers de referencia
        free(ref_temporal);

        qt_instancias--;

    }

    fclose(in); // fecha arquivos
    fclose(out);
    return 0;
}
