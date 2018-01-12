typedef struct
{
    double x;
    double y;

}ponto;
typedef struct
{
    ponto inicio,fim;
}semireta;
typedef struct
{
    semireta* reta_l;
    int q_retas;

}linha;
typedef struct
{
    semireta* reta_p;
    int q_retas;

}poligono;
void criaPonto(ponto *p, double x, double y); // retorna TRUE se os pontos forem identicos
int pontoCoincide(ponto P, ponto Q);
void imprimePonto(ponto P);
void criaLinha(linha *l, int numVertices, ponto *vertices); // verifica se a linha poligonal tem interseção com o polígono
int linhaInterceptaPoligono(linha L, poligono P); // verifica se a linha é simples (sem auto-interseções)
int linhaSimples(linha L);
void criaPoligono(poligono *p, int numVertices, ponto *vertices); // verifica se o ponto está no interior do polígono
int pontoEmPoligono(ponto P, poligono Pol); // verifica se o polígono é simples (sem auto-interseções)
int poligonoSimples(poligono Pol);
int intersecaoretas(semireta a , semireta b);
int posicaorelativa(ponto a , ponto b , ponto c);
