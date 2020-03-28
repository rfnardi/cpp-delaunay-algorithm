#include "catalogo_vizinhos.hpp"

del::catalogo_vizinhos::catalogo_vizinhos ( std::vector<std::vector<float>> conjunto_universo ) {
    this.catalogo_vizinhos = conjunto_universo;
};

void del::catalogo_vizinhos::define_raio_vizinhanca ( float raio ) {
    this.raio = raio;
};

void del::catalogo_vizinhos::define_referencial ( float ponto[ 3 ] ) {
    this.ponto_referencial = ponto;
};

float del::catalogo_vizinhos::ver_referencial () {
    return this.ponto_referencial;
};

float del::catalogo_vizinhos::distancia_referencial ( float ponto[ 3 ] ) {
    // calculo de distancia entre pontos a e b
    // ax = a[0], ay = a[1] e az = a[2]
};

bool del::catalogo_vizinhos::e_vizinho ( float ponto[ 3 ] ) {
    return ( this.distancia_referencial( ponto ) <= this.raio ) ? true : false;
};