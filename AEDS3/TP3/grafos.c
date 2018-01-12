#include "grafos.h"

void Mont_grafo(Lista *l,Grafo *f,double *raio,int qt_itens)
{
    int i,j;
    double dist;
    Apontador temp1,temp2;
    temp1 = l->primeiro; // variaveis temporarias

    f->indicador = (Lista *)malloc(sizeof(Lista)*qt_itens);
    f->cores = (int *)malloc(sizeof(int)*qt_itens);
    f->cores_f = (int *)malloc(sizeof(int)*qt_itens);
    f->qt_v= qt_itens;
    f->qt_cor = qt_itens+1; // armazena a qauantidade de vertices e limita a quantidade de cores

    for(i=0; i<qt_itens; i++) //loop que define a estutura (uma lista para cada vertice)
    {
        FLVazia(&f->indicador[temp1->chave-1]); // prepara uma nova lista para anexar na estrutura

        temp2 = l->primeiro; // apontador temporario para operacoes

        for(j=0; j<qt_itens; j++)
        {

            if(temp1!=temp2) //verifica se e possivel conectar algum vertice com o atual
            {
                dist = sqrt((temp1->x-temp2->x)*(temp1->x-temp2->x)+(temp1->y-temp2->y)*(temp1->y-temp2->y));

                if(dist>*raio) //  se possivel conecta
                {
                    Insere_l(temp2->chave,f->indicador[temp1->chave-1].primeiro,&f->indicador[temp1->chave-1],temp2->x,temp2->y);

                }
            }
            temp2 = temp2->proximo;
        }

        temp1 = temp1->proximo;
    }

}
void limpa_grafo(Grafo *f)
{
int i;
free(&f->cores);
free(&f->cores_f);
for(i=0; i<f->qt_v; i++) //loop que define a estutura (uma lista para cada vertice)
{
limpa_l(&(f->indicador[i]),0);
}
free(&f->indicador);
}
void colore_grafo (Grafo *f, int* buffer)
{
    int i,qt_cor,indice_cor;
    Apontador temp;
    qt_cor = 0;

    for(i=0; i<f->qt_v; i++) // limpa vetor de cores para uma nova operacao
    {
        f->cores[i]=-1;
    }

    for(i=0; i<f->qt_v; i++)// percorre o grafo apartir da sequencia (buffer) enviada para o procedimento
    {

        temp = f->indicador[buffer[i]].primeiro;
        indice_cor=0;

        while(temp!= NULL && temp->chave>0) //percorre todas as arestas do vertice atual
        {

            if(f->cores[temp->chave-1]==indice_cor) //verifica a menor cor possivel
            {
                temp = f->indicador[buffer[i]].primeiro;
                indice_cor+=1;
            }
            else
            {
                temp = temp->proximo;
            }
        }

        f->cores[buffer[i]] = indice_cor;//coloca a menor cor possivel no momento

        if(qt_cor<indice_cor+1)
        {
            qt_cor = indice_cor+1;
        }

        if(f->qt_cor<=indice_cor+1)// caso ja exista uma coloração melhor entao para.
        {
            return;
        }

    }
    f->qt_cor=qt_cor;

    for(i=0; i<f->qt_v; i++) // define as cores finais
    {
        f->cores_f[i] = f->cores[i];

    }

}
void permuta_forca_bruta(Grafo *f, int* buffer, int k) // algoritmo fatorial
{
    int i,tmp;

    if (k == f->qt_v)
    {
        colore_grafo(f,buffer); // chama a colore para cada instancia
    }

    else  //  recursão para permutaçoes
    {
        for (i = k; i < f->qt_v; i++)
        {
            tmp = buffer[k];
            buffer[k] = buffer[i]; // realiza as trocas a cada interacao
            buffer[i] = tmp;
            permuta_forca_bruta(f,buffer, k + 1);// faz a chamada recursiva
            tmp = buffer[k];
            buffer[k] = buffer[i];
            buffer[i] = tmp;
        }
    }
}
void forca_bruta(Grafo *f)
{
    int i,*buffer;
    buffer = (int*)malloc(sizeof(int)*f->qt_v); // cria um vetor de buffer para a parte recursiva

    for(i=0; i<f->qt_v; i++)
    {
        buffer[i] = i;
    }

    permuta_forca_bruta(f,buffer,0); // parte recursiva do codigo

}
void *colore_grafo_p(void *paramentros) // algoritmo paralelo
{
    Paralelo *p = (Paralelo *) paramentros;
    int i,qt_cor,indice_cor;

    Apontador temp;
    qt_cor = 0;

    for(i=0; i<p->g.qt_v; i++)
    {
        p->g.cores[i]=-1;
    }

    for(i=0; i<p->g.qt_v; i++)
    {

        temp = p->g.indicador[p->buffer[i]].primeiro;
        indice_cor=0;

        while(temp!= NULL && temp->chave>0)
        {

            if(p->g.cores[temp->chave-1]==indice_cor)
            {
                temp = p->g.indicador[p->buffer[i]].primeiro;
                indice_cor+=1;
            }
            else
            {
                temp = temp->proximo;
            }
        }

        p->g.cores[p->buffer[i]] = indice_cor;

        if(qt_cor<indice_cor+1)
        {
            qt_cor = indice_cor+1;
        }

        if(p->g.qt_cor<=indice_cor+1)// caso ja exista uma coloração melhor entao para.
        {
            pthread_exit((void *)NULL);
        }

    }
    p->g.qt_cor=qt_cor;

    for(i=0; i<p->g.qt_v; i++) // define as cores finais
    {
        p->g.cores_f[i] = p->g.cores[i];
    }

    pthread_exit((void *)NULL);
}
void permuta_forca_bruta_p(Paralelo *p,int* buffer ,int k ,int *buffer_t, pthread_t *t_id) // algoritmo fatorial paralelo
{
    int i,j,tmp;

    if (k == p[0].g.qt_v)
    {

        for (i = 0; i < p[0].g.qt_v; i++) // copia a sequencia a ser processada na thread
        {
            p[*buffer_t].buffer[i] = buffer[i];

        }

        pthread_create(&(t_id[*buffer_t]), NULL, colore_grafo_p, (void *)&p[*buffer_t]); // chama a função em paralelo


        if(*buffer_t<limit_p-1)//verifica se exedeu o numero de threads
        {
            *buffer_t+=1;
        }

        else //se exedeu espera elas terminarem
        {
            *buffer_t = 0;
            for(j=0; j<limit_p; j++)
            {
                pthread_join(t_id[j], NULL);
            }
        }
        // chama a colore para cada instancia
    }

    else  //  recursão para permutaçoes
    {
        for (i = k; i < p[0].g.qt_v; i++)
        {
            tmp = buffer[k];
            buffer[k] = buffer[i];
            buffer[i] = tmp;
            permuta_forca_bruta_p(p,buffer, k + 1,buffer_t,t_id);
            tmp = buffer[k];
            buffer[k] = buffer[i];
            buffer[i] = tmp;
        }
    }
}
void forca_bruta_p(Grafo *f)
{
    int i,x,*buffer;
    Paralelo p[limit_p];
    pthread_t id[limit_p];
    x = 0;

    for(i=0; i<limit_p; i++) // faz uma copia dos dados para cada thread para evitar conflitos
    {

        p[i].g = *f;
        p[i].buffer = (int*)malloc(sizeof(int)*f->qt_v); //buffer que guarda a sequencia da permultacao a ser processada

    }

    buffer = (int*)malloc(sizeof(int)*f->qt_v);

    for(i=0; i<f->qt_v; i++)
    {
        buffer[i] = i;
    }

    permuta_forca_bruta_p(p,buffer,0,&x,id); // parte recursiva do codigo

    for(i=0; i<limit_p; i++) // verifica a melhor solocao e transforma em resposta final
    {
        if(f->qt_cor>p[i].g.qt_cor)
        {
            f->qt_cor = p[i].g.qt_cor;
        }

    }

}
void heuristica(Grafo *f)
{
    int i,j,cont,*buffer,*sequencia; //buffer para armazenar a quantidade de arestas de cada vertice;
    buffer = (int*)malloc(sizeof(int)*f->qt_v);
    sequencia = (int*)malloc(sizeof(int)*f->qt_v);
    Apontador temp;

    for(i=0; i<f->qt_v; i++)// percorre o grafo apartir da sequencia (buffer) enviada para o procedimento
    {
        temp = f->indicador[i].primeiro;
        cont = 0;
        while(temp!= NULL && temp->chave>0) //percorre todas as arestas do vertice atual
        {
            cont++;
            temp = temp->proximo;
        }
        buffer[i] = cont;
    }

    for(i=0; i<f->qt_v; i++) // ordena o vetor em relação a qt de vertices
    {
        cont = 0;
        for(j=0; j<f->qt_v; j++)
        {
            if(cont<buffer[j])
            {
                sequencia[i] = j;
                cont = buffer[j];
            }
        }
        buffer[sequencia[i]] = -1;
    }

    colore_grafo (f,sequencia); // envia a sequencia para colorir seguindo a regra proposta

}
void il(Lista *l)
{
    Apontador temp;
    temp = l->primeiro;
    while(temp!= NULL && temp->chave>0) //percorre todas as arestas do vertice atual
    {

        printf( "%d ",temp->chave);
        temp = temp->proximo;

    }

}
void ip(Grafo *f)
{
    int i;
    Apontador temp;

    for(i=0; i<f->qt_v; i++)// percorre o grafo apartir da sequencia (buffer) enviada para o procedimento
    {

        temp = f->indicador[i].primeiro;

        printf("\n\n*%d*\n\n",i+1);
        while(temp!= NULL && temp->chave>0) //percorre todas as arestas do vertice atual
        {

            printf( "%d ",temp->chave);
            temp = temp->proximo;

        }



    }


}
