#ifndef DEL_NEIGHBORHOOD_C
#define DEL_NEIGHBORHOOD_C

#include "Vizinhanca.hpp"
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <functional>


del::Vizinhanca::Vizinhanca ( std::vector<del::Point> universalSet, unsigned int maxNeighboorHoodSize )
{
    this->universalSet = universalSet;
    this->maxNeighboorHoodSize = maxNeighboorHoodSize;
};

del::Vizinhanca::~Vizinhanca ()
{
    delete this->vizinhos;
};

std::string del::Vizinhanca::debugar_ponto( del::Point ponto )
{
    return ponto.to_string();
};

void del::Vizinhanca::definir_raio ( float raio )
{
    this->raio = raio;
    if ( this->debug )
    {
        std::cout << "Raio de vizinhança definido para " + std::to_string( this->raio ) << std::endl;
    }
};

void del::Vizinhanca::definir_referencial ( del::Point ponto )
{
    this->referencial = ponto;
    delete this->vizinhos;
    if ( this->debug )
    {
        std::cout << "Ponto " << this->debugar_ponto( this->referencial ) << " definido como referencial." << std::endl;
        std::cout << "Vizinhos ainda não conhecidos!" << std::endl;
    }
};

del::Point* del::Vizinhanca::obter_vizinhos ()
{
    std::vector<del::Point> pontos = this->universalSet;
    if ( this->debug )
    {
        std::cout << "Iniciando cálculo de vizinhança do ponto " << this->debugar_ponto( this->referencial ) << std::endl;
    }
    for ( int i = 0; i < pontos.size(); i++ )
    {
        if ( this->e_vizinho_de( pontos[ i ] ) )
        {
            this->adicionar_vizinho( pontos[ i ] );
        }
    }
    if ( this->debug )
    {
        std::cout << "A vizinhança obtida contém " << this->vizinhos << " pontos" << std::endl;
    }
    return this->vizinhos;
};

std::vector<del::Point*> del::Vizinhanca::obter_catalogo_de_vizinhancas ()
{
    std::vector<del::Point*> catalago;
    del::Point* vizinhanca;
    std::vector<del::Point> pontos = this->universalSet;
    if ( this->debug )
    {
        std::cout << "Iniciando processo de obtenção do catálogo de vizinhanças." << std::endl;
    }
    for ( int i = 0; i < pontos.size(); i++ )
    {
        this->definir_referencial( pontos[ i ] );
        vizinhanca =  this->obter_vizinhos();
        std::cout << vizinhanca << std::endl;
        std::cout << i << std::endl;
        // vizinhanca.push_back( pontos[ i ] );
        // catalago.push_back( this->ordenar_vizinhanca( vizinhanca ) );
        // vizinhanca.clear();
    }
    if ( this->debug )
    {
        std::cout << "O catálogo obtido contém " << catalago.size() << "  vizinhanças." << std::endl;
    }
    return catalago;
};

del::Point* del::Vizinhanca::obter_intersecao_entre_vizinhancas ( del::Point* nhb1, del::Point* nhb2 )
{
    del::Point p1, p2;
    del::Point* intersection;
    // ref viz 1
    // ref viz 2
    // for (  ; ; i++ )
    // {}
    // for ( std::vector<del::Point>::iterator i = nhb1.begin(); i != nhb1.end(); i++ )
    // {
    //     for ( std::vector<del::Point>::iterator j = nhb2.begin(); j != nhb2.end(); j++ )
    //     {
    //         p1 = (*i);
    //         p2 = (*j);
    //         if ( p1 == p2 )
    //         {
    //             intersection.push_back( p1 );
    //         }
    //     }
    // }
    return intersection;
};

void del::Vizinhanca::ativar_debug ()
{
    this->debug = true;
};

void del::Vizinhanca::desativar_debug ()
{
    this->debug = false;
};

float del::Vizinhanca::obter_distancia_de ( del::Point ponto )
{
    del::Point ref = this->referencial;
    float distance = ref.distancia( ponto );
    if ( this->debug )
    {
        std::cout << "Distância entre " << this->debugar_ponto( this->referencial ) << " e " << this->debugar_ponto( ponto ) << " vale " << distance << std::endl;
    }
    return distance;
};

bool del::Vizinhanca::e_vizinho_de ( del::Point ponto )
{
    return ( this->obter_distancia_de( ponto ) <= this->raio ) ? true : false;
};

void del::Vizinhanca::adicionar_vizinho ( del::Point ponto )
{
    del::Point* listaRef = this->vizinhos;
    // listaRef.push_back( ponto );
    // this->vizinhos = listaRef;
    // if ( this->debug )
    // {
    //     std::cout << "Ponto " << this->debugar_ponto( ponto ) << " foi adicionado a vizinhança." << std::endl;
    // }
};

bool del::Vizinhanca::comparar_distancia_referencial ( del::Point p1, del::Point p2 )
{
    return ( this->obter_distancia_de( p1 ) < this->obter_distancia_de( p2 ) );
};

del::Point* del::Vizinhanca::ordenar_vizinhanca ( del::Point* viz )
{
    // std::sort( viz.begin(), viz.end(), std::bind( &del::Vizinhanca::comparar_distancia_referencial, this, std::placeholders::_1,  std::placeholders::_2 ) );
    if ( this->debug )
    {
        std::cout << "Vizinhança em ordem crescente de distância ao ponto " << this->debugar_ponto( this->referencial ) << "." << std::endl;
    }
    return viz;
};

#endif
