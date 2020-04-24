#include "Vizinhanca.hpp"
#include <stdlib.h>
#include <iostream>

del::Vizinhanca::Vizinhanca ( std::vector<std::vector<float>> conjuntoUniverso ) {
    this->conjuntoUniverso = conjuntoUniverso;
};

std::string del::Vizinhanca::debugar_ponto( std::vector<float> ponto ) {
    std::string str = "(";
    for ( int i = 0; i < ponto.size(); i++ ) {
        str += std::to_string( ponto[ i ] );
        if ( i < ponto.size() - 1 ) {
            str += ",";
        } else {
            str += ")";
        }
    }
    return str;
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
    if ( this->debug ) {
        std::cout << "Ponto " << this->debugar_ponto( this->referencial ) << " definido como referencial." << std::endl;
        std::cout << "Vizinhos ainda não conhecidos!" << std::endl;
    }
};

std::vector<std::vector<float>> del::Vizinhanca::obter_vizinhos () {
    std::vector<std::vector<float>> pontos = this->conjuntoUniverso;
    if ( this->debug ) {
        std::cout << "Iniciando cálculo de vizinhança do ponto " << this->debugar_ponto( this->referencial ) << std::endl;
    }
    for ( int i = 0; i < pontos.size(); i++ ) {
        if ( this->e_vizinho_de( pontos[ i ] ) ) {
            this->adicionar_vizinho( pontos[ i ] );
        }
    }
    if ( this->debug ) {
        std::cout << "A vizinhança obtida contém " << this->vizinhos.size() << " pontos" << std::endl;
    }
    return this->vizinhos;
};

std::vector<std::vector<std::vector<float>>> del::Vizinhanca::obter_catalogo_de_vizinhancas () {
    std::vector<std::vector<std::vector<float>>> catalago;
    std::vector<std::vector<float>> vizinhanca;
    std::vector<std::vector<float>> pontos = this->conjuntoUniverso;
    if ( this->debug ) {
        std::cout << "Iniciando processo de obtenção do catálogo de vizinhanças." << std::endl;
    }
    for ( int i = 0; i < pontos.size(); i++ ) {
        this->definir_referencial( pontos[ i ] );
        vizinhanca =  this->obter_vizinhos();
        vizinhanca.push_back( pontos[ i ] );
        catalago.push_back( this->ordenar_vizinhanca( vizinhanca ) );
        vizinhanca.clear();
    }
    if ( this->debug ) {
        std::cout << "O catálogo obtido contém " << catalago.size() << "  vizinhanças." << std::endl;
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
    float distance = sqrt( sum );
    if ( this->debug ) {
        std::cout << "Distância entre " << this->debugar_ponto( this->referencial ) << " e " << this->debugar_ponto( ponto ) << " vale " << distance << std::endl;
    }
    return distance;
};

bool del::Vizinhanca::e_vizinho_de ( std::vector<float> ponto ) {
    return ( this->obter_distancia_de( ponto ) <= this->raio ) ? true : false;
};

void del::Vizinhanca::adicionar_vizinho ( std::vector<float> ponto ) {
    std::vector<std::vector<float>> listaRef = this->vizinhos;
    listaRef.push_back( ponto );
    this->vizinhos = listaRef;
    if ( this->debug ) {
        std::cout << "Ponto " << this->debugar_ponto( ponto ) << " foi adicionado a vizinhança." << std::endl;
    }
};

bool del::Vizinhanca::comparar_distancia_referencial ( std::vector<float> p1, std::vector<float> p2 ) {
    return ( this->obter_distancia_de( p1 ) < this->obter_distancia_de( p2 ) );
};

std::vector<std::vector<float>> del::Vizinhanca::ordenar_vizinhanca ( std::vector<std::vector<float>> viz ) {
    std::sort( viz.begin(), viz.end(), std::bind( &del::Vizinhanca::comparar_distancia_referencial, this, std::placeholders::_1,  std::placeholders::_2 ) );
    if ( this->debug ) {
        std::cout << "Vizinhança em ordem crescente de distância ao ponto " << this->debugar_ponto( this->referencial ) << "." << std::endl;
    }
    return viz;
};