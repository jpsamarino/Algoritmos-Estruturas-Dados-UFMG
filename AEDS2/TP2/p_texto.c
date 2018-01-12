#include <stdio.h>
#include <stdio.h>
#include <string.h>
#define MAX 60
//Os comandos dentro do arquivo principal são referentes somente ao tratamento da entrada para ser envido ao TAD.

int especial(char b)
{
    if(b<'1' || b>'z' || (b>'9' && b<'A') || (b>'Z' && b<'a'))
    {
        return 1;
    }

    return 0;

}

char acento(char b)
{
    int i;
    char acentos[58]= {'À','Á','Â','Ã','Ä','Å','Ç','È','É','Ê','Ë','Ì','Í','Î','Ï','Ñ','Ò','Ó','Ô','Õ','Ö','Ù','Ú','Û','Ü','Ý','à','á','â','ã','ä','å','ç','è','é','ê','ë','ì','í','î','ï','ñ','ò','ó','ô','õ','ö','ù','ú','û','ü','ý','Š','Ž','š','ž','Ÿ'};
    char corrigi[58]= {'a','a','a','a','a','a','c','e','e','e','e','i','i','i','i','n','o','o','o','o','o','u','u','u','u','y','a','a','a','a','a','a','c','e','e','e','e','i','i','i','i','n','o','o','o','o','o','u','u','u','u','y','s','z','s','z','y'};

    for(i=0; i<57; i++)
    {
        if(acentos[i] == b)
        {
            return corrigi[i];
        }
    }

    return 0;
}

void comando(char b , int *retorno)
{
    if(b == '#')
    {
        *retorno = 1;   // busca
    }
    else if(b == '@')
    {
        *retorno = 2;   // remove
    }
    else if(b == '&')
    {
        *retorno = 3;   // imprime
    }

}

int main()
{
    int j = 0 ,l = 1,comand = 0;
    char buffer,buffer2[MAX];

    while(!feof(stdin))
    {


        buffer = getc(stdin); // faz a leitura dos carcteres do arquivo.


//***********************************************************************
        if(especial(buffer) || (j==0 && buffer>='1' && buffer<='9')) // veririca se o carcter é especial.
        {
            buffer2[j] = acento(buffer); // retira os acentos.

            if(buffer2[j]!=0) // add no cntador de letras da palavra.
            {
                j++;
            }


            else // trata delimitadores de palavras.
            {


                if((j!=0)|| feof(stdin))
                {
                    buffer2[j] = 0; // finaliza a string;

                    strlwr(buffer2); // transforma a palavra em minusculo.


                        // chama a TAD
                        if(!comand) {}// insere

                        if(comand == 1) {}//busca

                        if(comand == 2) {}//remove

                        if(comand == 3) {}//imprime

                        printf("\n-%s- comando %d l %d",buffer2,comand,l);



                    j=0; // reinicia contador palavra
                    comand = 0; // reinicia comando


                }

                if(!feof(stdin))
                {
                    if(buffer == 13 || buffer == 10) // verifica se existiu uma quebra de linha (win e linux).
                    {
                        l+=1;
                    }

                    comando(buffer ,&comand); // verifica comando

                }

            }


        }
//**************************************************************************
        else // adiciona a letra do arquivo a palavra.
        {
            buffer2[j]=buffer;
            j++;
        }

    }
    return 0;
}
