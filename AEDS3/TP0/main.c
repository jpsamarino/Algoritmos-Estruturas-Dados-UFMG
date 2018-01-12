#include "matriz.h"

void CapturaMatrizAquivo(FILE* in,MatrizComplexa *matriz_generica , int qt_coluna , int qt_linha)
{
    int i,j,buffer_a,buffer_b; //variaveis para executar operaçoes internas da função
    char buffer_texto1[MAX], buffer_texto2[MAX]; //buffers para processar o texto de entrada

    for(i=0; i<qt_linha; i++)//loop responsavel por percorrer as linhas da matrix do arquivo
    {
        for(j=0; j<qt_coluna; j++)
        {
            fscanf(in,"%s",buffer_texto1);
            strcpy(buffer_texto2,buffer_texto1);//faz uma copia da palavra lida
            strtok(buffer_texto1,"-");//separa o texto para traz do marcador -

            buffer_a = strlen(buffer_texto1);//quarda os tamanhos das strings
            buffer_b = strlen(buffer_texto2);

            if(buffer_a==buffer_b) // se o tamaho for igual então não possui marcador - , que implica so haver marcador +
            {
                matriz_generica->numero[i][j].real =  atof(strtok(buffer_texto1,"+"));
                matriz_generica->numero[i][j].imaginario = atof(strtok(NULL,"i"));

            }
            else //se não existe pelo menos um marcador -
            {
                if((buffer_b-buffer_a)==1)//entao so a parte real e negativa
                {
                    matriz_generica->numero[i][j].real = atof(strtok(buffer_texto1,"+"))*(-1);
                    matriz_generica->numero[i][j].imaginario = atof(strtok(NULL,"i"));

                }

                else if (buffer_texto2[0]=='-') // os dois numeros são negativos
                {
                    matriz_generica->numero[i][j].real = atof(buffer_texto1);
                    matriz_generica->numero[i][j].imaginario = atof(strtok(NULL,"i"))*(-1);
                }

                else // a parte real e positiva e a imaginaria negativa
                {
                    matriz_generica->numero[i][j].real = atof(buffer_texto1);
                    matriz_generica->numero[i][j].imaginario = atof(strtok(NULL,"i"))*(-1);
                }
            }

        }

    }

}
void ImprimeResposta(FILE* out,MatrizComplexa *matriz_resposta,int qt_coluna_resposta,int qt_linha_resposta)
{
    int linha ,coluna;// variaveis usadas internamente

    fprintf(out,"\n");

    for ( linha = 0; linha < qt_linha_resposta; linha++)//percorre a variavel matriz
    {
        for ( coluna = 0; coluna < qt_coluna_resposta; coluna++)
        {

            fprintf(out,"%g+%gi ",matriz_resposta->numero[linha][coluna].real,matriz_resposta->numero[linha][coluna].imaginario);

        }
        fprintf(out,"\n");
    }
}
int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "r"); //ponteiros aquivos de entrada e saida
    FILE *out = fopen(argv[2], "w");

    int qt_instancias,qt_linha_a,qt_linha_b,qt_coluna_a,qt_coluna_b; // variaveis usadas na funcão principal
    MatrizComplexa mat_buffer_a , mat_buffer_b , mat_resultado;
    fscanf(in,"%d",&qt_instancias); //captura a qt de instancias

    while(qt_instancias) //loop para executar todas as operaçoes
    {
        fscanf(in,"%d",&qt_linha_a); //captura a dimensão das matriz A
        fscanf(in,"%d",&qt_coluna_a);
        Aloca(&mat_buffer_a,qt_coluna_a,qt_linha_a);
        CapturaMatrizAquivo(in,&mat_buffer_a,qt_coluna_a,qt_linha_a); //captura a matriz A por completo
        fscanf(in,"%d",&qt_linha_b);//capitura a dimenção das matriz B
        fscanf(in,"%d",&qt_coluna_b);

        Aloca(&mat_buffer_b,qt_coluna_b,qt_linha_b);
        CapturaMatrizAquivo(in,&mat_buffer_b,qt_coluna_b,qt_linha_b);//captura a matriz B por completo

        if(qt_coluna_a==qt_linha_b) // validação multiplicacao matrizes ,so entra se for possivel multiplicar
        {
            Aloca(&mat_resultado,qt_coluna_b,qt_linha_a);
            MultiplicaMatriz(&mat_buffer_a,&mat_buffer_b,&mat_resultado,qt_coluna_b,qt_linha_a,qt_coluna_a);
            ImprimeResposta(out,&mat_resultado,qt_coluna_b,qt_linha_a);
        }
        else
        {
            fprintf(out,"\n****arquivo de entrada no formato errado****\n");
        }
        free(&mat_buffer_a.numero); // Limpa alocação antiga para poder realizar uma nova operação
        free(&mat_buffer_b.numero);
        free(&mat_resultado.numero);

        qt_instancias--;
    }
    fclose(in);
    fclose(out);

    return 0;
}
