//***********************João Pedro Samarino******Mat: 2013048933**************************************************
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
int main()
{
    Lista teste;
    CriaLista(&teste);
    Insere(3,0,&teste);
    Insere(6,3,&teste);
    Insere(7,0,&teste);
    Insere(9,1,&teste);
    Insere(12,0,&teste);
    Insere(17,1,&teste);
    Insere(19,0,&teste);
    Insere(21,0,&teste);
    Insere(25,2,&teste);
    Insere(26,0,&teste);
    imprime(2,&teste);
    Apontador j[5];
    Busca(17,&teste,j,1);

    return 0;
}
