#include <stdio.h>
#include <stdlib.h>
#include "caminhos.h"


int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "r"); //ponteiros aquivos de entrada e saida
    FILE *out = fopen(argv[2], "w");
    cidade cidade_buffer;// variaveis usadas na funcão principal
    int qt_instancias,qt_bloqueios,qt_testes;
    int qt_caminhos,i,l_buffer,c_buffer; // variaveis de buffers

    fscanf(in,"%d",&qt_instancias); //captura a qt de instancias

    while(qt_instancias) //loop para executar todas as operaçoes
    {
        fscanf(in,"%d",&cidade_buffer.qt_linhas); //captura a dimensão da cidade
        fscanf(in,"%d",&cidade_buffer.qt_colunas);
        Aloca(&cidade_buffer);
        fscanf(in,"%d",&qt_bloqueios);

        for(i=0; i<qt_bloqueios; i++)
        {
            fscanf(in,"%d",&l_buffer); //captura local do bloqueio
            fscanf(in,"%d",&c_buffer);
            marca_bloqueio(&cidade_buffer,l_buffer-1,c_buffer-1);
        }

        faz_matriz_custo(&cidade_buffer,0,0,0);
        fscanf(in,"%d",&qt_testes);

        for(i=0; i<qt_testes; i++)
        {
            fscanf(in,"%d",&l_buffer); //captura local do bloqueio
            fscanf(in,"%d",&c_buffer);
            qt_caminhos = 0;
            acha_qt_caminhos(&cidade_buffer,l_buffer-1,c_buffer-1,&qt_caminhos);
            fprintf(out,"%d\n",qt_caminhos);
        }

        fprintf(out,"\n");

        limpa_estrutura(&cidade_buffer); // Limpa alocação antiga para poder realizar uma nova operação

        qt_instancias--;
    }
    fclose(in);
    fclose(out);

    return 0;
}
