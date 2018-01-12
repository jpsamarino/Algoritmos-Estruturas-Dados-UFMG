#include"memoria.h"


void prepara_memoria(Memoria_principal* mp, int tamanho_p, int tamanho_t)//função destinada a preparar a "memoria" para receber as paginas de uma nova instancia
{
    FLVazia(&(mp->pagina));
    mp->tamanho_total = tamanho_t;
    mp->tamanho_pagina = tamanho_p;
    mp->qt_paginas_atual = 0;
}
void limpa_memoria(Memoria_principal* mp)
{
    limpa_l(&(mp->pagina));
    mp->tamanho_total = 0;
    mp->tamanho_pagina = 0;
    mp->qt_paginas_atual = 0;

}
int insere_lru(Memoria_principal* mp, int indicador) // retorna -1 quando der page fault ou N representado o numero de passos necessarios para colocar o indicador no inicio
{
    Apontador buffer_celula;
    int buffer_referencia_temporal,indicador_valido; //indicador que se refere ao primeiro byte da pagina
    indicador_valido = (indicador/mp->tamanho_pagina)*mp->tamanho_pagina; // calcula indicador valido
    buffer_referencia_temporal = Busca_l(indicador_valido,&(mp->pagina),&buffer_celula);

    if(buffer_referencia_temporal == -1 )// se não existe a pagina na memoria
    {
        if((mp->qt_paginas_atual < (mp->tamanho_total/mp->tamanho_pagina) ))// se a memoria ainda tiver espaço vazio
        {
            mp->qt_paginas_atual+=1;
            //Insere_l(indicador_valido,mp->pagina.primeiro,&(mp->pagina));

        }
        else  // memoria cheia , necessario tirar a ultima pagina
        {
            Remove_l(mp->pagina.fim,&(mp->pagina));
            //Insere_l(indicador_valido,mp->pagina.primeiro,&(mp->pagina));
        }
    }
    else //pagina ja na memoria , necessario deslocar.
    {
        Remove_l(buffer_celula,&(mp->pagina));
    }

    Insere_l(indicador_valido,mp->pagina.primeiro,&(mp->pagina),0);//coloca o valor no incio

    return buffer_referencia_temporal;
}
int insere_fifo(Memoria_principal* mp, int indicador)
{
    Apontador buffer_celula;
    int buffer,indicador_valido; //indicador que se refere ao primeiro byte da pagina
    indicador_valido = (indicador/mp->tamanho_pagina)*mp->tamanho_pagina; // calcula indicador valido
    buffer = Busca_l(indicador_valido,&(mp->pagina),&buffer_celula);

    if(buffer == -1 )// se não existe a pagina na memoria
    {
        if((mp->qt_paginas_atual < (mp->tamanho_total/mp->tamanho_pagina) ))// se a memoria ainda tiver espaço vazio
        {
            mp->qt_paginas_atual+=1;
            //Insere_l(indicador_valido,mp->pagina.primeiro,&(mp->pagina));

        }
        else  // memoria cheia , necessario tirar a ultima pagina
        {
            Remove_l(mp->pagina.fim,&(mp->pagina));

        }
        Insere_l(indicador_valido,mp->pagina.primeiro,&(mp->pagina),0);//so insere se a pagina não estiver  na memoria.
    }



    return buffer;// retorna -1 se houver uma falta
}
int insere_lfu(Memoria_principal* mp, int indicador)
{
    Apontador buffer_celula;
    int buffer_referencia,buffer_con_lfu,indicador_valido; //indicador que se refere ao primeiro byte da pagina
    buffer_con_lfu = 1;
    indicador_valido = (indicador/mp->tamanho_pagina)*mp->tamanho_pagina; // calcula indicador valido
    buffer_referencia = Busca_l(indicador_valido,&(mp->pagina),&buffer_celula);

    if(buffer_referencia == -1 )// se não existe a pagina na memoria
    {
        if((mp->qt_paginas_atual < (mp->tamanho_total/mp->tamanho_pagina) ))// se a memoria ainda tiver espaço vazio
        {
            mp->qt_paginas_atual+=1;


        }
        else  // memoria cheia , necessario tirar a celula que contem o menor contador lfu
        {
            busca_l_lfu(&(mp->pagina),&buffer_celula);
            Remove_l(buffer_celula,&(mp->pagina));

        }
    }

    else //pagina ja na memoria , necessario deslocar e incrementar o contador.
    {
        buffer_con_lfu = (buffer_celula->lfu)+1;
        // printf("chave:%d-cont:%d",buffer_celula->chave,buffer_con_lfu);
        Remove_l(buffer_celula,&(mp->pagina));
    }

    Insere_l(indicador_valido,mp->pagina.primeiro,&(mp->pagina),buffer_con_lfu);//coloca o valor no incio

    return buffer_referencia;

}
int insere_nova(Memoria_principal* mp, int indicador)
{
    Apontador buffer_celula;
    int buffer_referencia,indicador_valido; //indicador que se refere ao primeiro byte da pagina
    indicador_valido = (indicador/mp->tamanho_pagina)*mp->tamanho_pagina; // calcula indicador valido
    buffer_referencia = Busca_l(indicador_valido,&(mp->pagina),&buffer_celula);

    if(buffer_referencia == -1 )// se não existe a pagina na memoria
    {
        if((mp->qt_paginas_atual < (mp->tamanho_total/mp->tamanho_pagina) ))// se a memoria ainda tiver espaço vazio
        {
            mp->qt_paginas_atual+=1;
            //Insere_l(indicador_valido,mp->pagina.primeiro,&(mp->pagina));

        }
        else  // a nova politiva sempre remove o segundo item da fila , que e organizada conforme o mlu
        {
            Remove_l(mp->pagina.primeiro->proximo,&(mp->pagina));

        }
    }
    else //pagina ja na memoria , necessario deslocar.
    {
        Remove_l(buffer_celula,&(mp->pagina));
    }

    Insere_l(indicador_valido,mp->pagina.primeiro,&(mp->pagina),0);//coloca o valor no incio

    return buffer_referencia;

}
int referencia_espacial(int tamanho_p,int inicio , int fim)
{
    int buffer1,buffer2,resposta;

    buffer1 = inicio/tamanho_p; // calcula em qual pagina esta o numero informado
    buffer2 = fim/tamanho_p; // calcula em qual pagina esta o numero informado
    resposta = buffer2 -buffer1; // calcula a distancia entre as paginas
    return resposta;
}
