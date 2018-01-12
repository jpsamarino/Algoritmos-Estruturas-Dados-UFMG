#include <stdio.h>
#include <stdlib.h>

int nova_instancia(FILE *arq)
{
    char b;
    b = getc(arq);
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

int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "r"); //ponteiros aquivos de entrada e saida
    double f;

    while(!feof(in)) // repete ate o final do arquivo
    {
        if(nova_instancia(in))
        {
            printf("\n ok ok \n");
        }
        if(fscanf(in,"%lf",&f) != EOF)
        {
            printf ("%lf ",f);
        }

    }

    fclose(in);

    return 0;
}
