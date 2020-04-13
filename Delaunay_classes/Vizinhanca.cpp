#include "Vizinhanca.hpp"
#include <stdlib.h>
#include <iostream>

del::Vizinhanca::Vizinhanca ( std::vector<std::vector<float>> conjuntoUniverso ) {
    this->conjuntoUniverso = conjuntoUniverso;
};

void del::Vizinhanca::definir_raio ( float raio ) {
    this->raio = raio;
    if ( this->debug ) {
        std::cout << "Raio de vizinhança definido para " + std::to_string( this->raio ) << std::endl;
    }
};

void del::Vizinhanca::definir_referencial ( std::vector<float> ponto ) {
    this->referencial = ponto;
    this->vizinhos.clear();
};

std::vector<std::vector<float>> del::Vizinhanca::obter_vizinhos () {
    std::vector<std::vector<float>> pontos = this->conjuntoUniverso;
    if ( this->debug ) {
        std::cout << "Iniciando cálculo de vizinhança de ponto ["  << "criar metodo para debug do ponto" << "]" << std::endl;
    }
    for ( int i = 0; i < pontos.size(); i++ ) {
        if ( this->e_vizinho_de( pontos[ i ] ) ) {
            this->adicionar_vizinho( pontos[ i ] );
        }
    }
    return this->vizinhos;
};

std::vector<std::vector<std::vector<float>>> del::Vizinhanca::obter_catalogo_de_vizinhancas () {
    std::vector<std::vector<std::vector<float>>> catalago;
    std::vector<std::vector<float>> vizinhanca;
    std::vector<std::vector<float>> pontos = this->conjuntoUniverso;
    for ( int i = 0; i < pontos.size(); i++ ) {
        this->definir_referencial( pontos[ i ] );
        vizinhanca =  this->obter_vizinhos();
        vizinhanca.push_back( pontos[ i ] );
        catalago.push_back( this->ordenar_vizinhanca( vizinhanca ) );
        vizinhanca.clear();
    }
    return catalago;
};

void del::Vizinhanca::ativar_debug () {
    this->debug = true;
};

void del::Vizinhanca::desativar_debug () {
    this->debug = false;
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

bool del::Vizinhanca::comparar_distancia_referencial ( std::vector<float> p1, std::vector<float> p2 ) {
    return ( this->obter_distancia_de( p1 ) < this->obter_distancia_de( p2 ) );
};

std::vector<std::vector<float>> del::Vizinhanca::ordenar_vizinhanca ( std::vector<std::vector<float>> viz ) {
    std::sort( viz.begin(), viz.end(), std::bind( &del::Vizinhanca::comparar_distancia_referencial, this, std::placeholders::_1,  std::placeholders::_2 ) );
    return viz;
};