#include "Vizinhanca.hpp"
#include <cmath>

del::Vizinhanca::Vizinhanca ( std::vector<std::vector<float>> conjuntoUniverso ) {
    this->conjuntoUniverso = conjuntoUniverso;
};

void del::Vizinhanca::definir_raio ( float raio ) {
    this->raio = raio;
};

void del::Vizinhanca::definir_referencial ( std::vector<float> ponto ) {
    this->referencial = ponto;
    this->vizinhos.clear();
};

std::vector<std::vector<float>> del::Vizinhanca::obter_vizinhos () {
    std::vector<std::vector<float>> pontos = this->conjuntoUniverso;
    for ( int i = 0; i < pontos.size(); i++ ) {
        if ( this->e_vizinho_de( pontos[ i ] ) ) {
            this->adicionar_vizinho( pontos[ i ] );
        }
    }
    return this->vizinhos;
};

std::vector<std::vector<std::vector<float>>> del::Vizinhanca::obter_catalogo_de_vizinhos () {
    std::vector<std::vector<std::vector<float>>> catalago;
    std::vector<std::vector<float>> pontos = this->conjuntoUniverso;
    for ( int i = 0; i < pontos.size(); i++ ) {
        this->definir_referencial( pontos[ i ] );
        catalago.push_back( this->obter_vizinhos() );
    }
    return catalago;
};

float del::Vizinhanca::obter_distancia_de ( std::vector<float> ponto ) {
    std::vector<float> ref = this->referencial;
    std::vector<float>::iterator j = ref.begin();
    float diff;
    float square;
    float sum = 0;
    for ( std::vector<float>::iterator i = ponto.begin(); i != ponto.end(); i++, j++ ) {
        diff = *i - *j;
        sum += pow( diff, 2 );
    }
    return sqrt( sum );
};

bool del::Vizinhanca::e_vizinho_de ( std::vector<float> ponto ) {
    return ( this->obter_distancia_de( ponto ) <= this->raio ) ? true : false;
};

void del::Vizinhanca::adicionar_vizinho ( std::vector<float> ponto ) {
    std::vector<std::vector<float>> listaRef = this->vizinhos;
    listaRef.push_back( ponto );
    this->vizinhos = listaRef;
};