#include "catalogo_vizinhos.hpp"

del::catalogo_vizinhos::catalogo_vizinhos ( vector<float> conjunto_universo[ 3 ] ) {
    this.catalogo_vizinhos = conjunto_universo;
};

void del::catalogo_vizinhos::define_raio_vizinhanca ( float raio ) {
    this.raio = raio;
};

void del::catalogo_vizinhos::define_referencial ( float ponto[ 3 ] ) {
    this.ponto_referencial = ponto;
};

float del::catalogo_vizinhos::distancia_entre ( float a[ 3 ], float b[ 3 ] ) {
    // calculo de distancia entre pontos a e b
    // ax = a[0], ay = a[1] e az = a[2]
};

bool del::catalogo_vizinhos::e_vizinho ( float ponto[ 3 ] ) {
    return ( this.distancia_entre( this.ponto_referencial, ponto ) <= this.raio ) ? true : false;
};