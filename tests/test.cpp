#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../libs/catch.hpp"
#include "../src/Point.cpp"
#include "../src/Set.hpp"

#define SET_SIZE 6
#define SUBSET_SIZE 3

del::coordinate randomCoordinate ()
{
    return rand() % 10;
}

del::Point randomPoint ()
{
    del::coordinate
        x = randomCoordinate(),
        y = randomCoordinate(),
        z = randomCoordinate();
    del::Point p ( x, y, z );
    return p;
}

void fillWithRandomPoints ( del::Point* pointer, size_t size )
{
    for ( size_t i = 0; i < size; i++ )
    {
        pointer[ i ] = randomPoint();
    }
}



TEST_CASE( "Validando operador igualdade.", "[point]" )
{
    for ( int i = 0; i < SET_SIZE; i++ )
    {
        del::Point p1 = randomPoint();
        del::Point p2 = p1;
        bool comparison = ( p1 == p2 );
        REQUIRE( true == comparison );
    }
}

TEST_CASE( "Instância sem valores para construtor deve ser (0,0,0).", "[point]" )
{
    del::Point p1;
    del::Point p2 ( 0, 0, 0 );
    bool comparison = ( p1 == p2 );
    REQUIRE( true == comparison );
}

TEST_CASE( "Instância sem valores para construtor em array deve preencher nulos.", "[point]" )
{
    del::Point p1[ SET_SIZE ];
		for ( int i = 0; i < SET_SIZE; i++ )
	 	{
			bool isP1Null = ( p1[ i ] == del::Point() );
			REQUIRE( true == isP1Null );
		}
}

TEST_CASE( "Distâncias iguais para mesmos pontos entre os métodos estáticos e não estáticos.", "[point]" )
{
    for ( int i = 0; i < SET_SIZE; i++ )
    {
        del::Point p1 = randomPoint();
        del::Point p2 = randomPoint();
        del::distance dist1 = p1.distancia( p2 );
        del::distance dist2 = del::Point::distancia( p1, p2 );
        REQUIRE( dist1 == dist2 );
    }
}

TEST_CASE( "Cálculo de distâncias deve ser simétrico.", "[point]" )
{
    for ( int i = 0; i < SET_SIZE; i++ )
    {
        del::Point p1 = randomPoint();
        del::Point p2 = randomPoint();
        REQUIRE( p1.distancia( p2 ) == p2.distancia( p1 ) );
    }
}



TEST_CASE( "Construtor Set deve encher de nulos caso não receba ponteiro.", "[set]" )
{
	del::Set<del::Point> set ( SET_SIZE );
	del::Point p;
	for ( int i = 0; i < SET_SIZE; i++ )
	{
		bool isNullPoint = ( p == set.points[ i ] );
		REQUIRE( isNullPoint == true );
	}
}


TEST_CASE( "Construtor Set deve fazer uma cópia dos valores inseridos para o ponteiro interno.", "[set]" )
{
    del::Point points[ SET_SIZE ];
    fillWithRandomPoints( points, SET_SIZE );
    del::Set<del::Point> set ( SET_SIZE, points );
    for ( int i = 0; i < SET_SIZE; i ++ )
    {
				del::Point* pMem = &points[ i ];
				del::Point* sMem = &set.points[ i ];
				CHECK_FALSE( sMem == pMem );
    }
}

TEST_CASE( "Após instanciar Set, este  não depende do ponteiro inserido inicialmente, podendo recebe-lo em outra stack 'filha'.", "[set]" )
{
    del::Set<del::Point> set ( SET_SIZE );
		del::Point p = randomPoint();
		{
			del::Point pointer[ SET_SIZE ];
			for ( int i = 0; i < SET_SIZE; i++ )
			{
				pointer[ i ] = p;
			}
			set.copyList( pointer, SET_SIZE );
		}
		for ( int i = 0; i < SET_SIZE; i++ )
		{
			bool comparison = ( set.points[ i ] == p );
			CHECK( comparison == true );
		}
}

/*
TEST_CASE( "Validando reordenação de Set em relação a um ponto (0,0,0)", "[point,set]" )
{
    // inspired on HTML tags: ul = unordered list, ol = ordered list
    del::Point ul[ SET_SIZE ];
    del::Point ol[ SET_SIZE ];
    for ( int i = 0; i < SET_SIZE; i++ )
    {
        ol[ i ] = del::Point ( i, 0, 0 );
        if ( i != SET_SIZE - 1 )
        {
            ul[ i ] = del::Point ( i+1, 0, 0 );
        }
        else
        {
            ul[ i ] = del::Point ( 0, 0, 0 );
        }
        
        
    }
    del::Set<del::Point> set ( SET_SIZE, ul );
    std::cout << set.to_string() << std::endl;
    set.orderByDistance( del::Point ( 0, 0, 0 ) );
    for ( int i = 0; i < SET_SIZE; i++ )
    {
        bool comparison = ( ol[ i ] == set.points[ i ] );
        std::cout << ol[ i ].to_string() << " ~ " << set.points[ i ].to_string() <<std::endl;
        CHECK( true == comparison );
    }
    std::cout << set.to_string() << std::endl;
}

TEST_CASE( "Após reordenação por distância, Set torna-se uma sequência não-descrescente.", "[point,set]" )
{
    del::Point P = randomPoint();
    del::Point points[ SET_SIZE ];
    fillWithRandomPoints( points, SET_SIZE );
    del::Set<del::Point> set ( SET_SIZE, points );
    set.orderByDistance( P );
    for ( size_t i = 1; i < SET_SIZE; i++ )
    {
        bool comparison = set.points[ i - 1 ].distancia( P ) <= set.points[ i ].distancia( P );
        REQUIRE( true == comparison );
    }
    std::cout << set.to_string() << std::endl;
}

TEST_CASE( "Subset creation.", "[set]" )
{
    del::Point points[ SUBSET_SIZE ];
    del::Set<del::Point> subset ( SUBSET_SIZE, points );
    del::Point morePoints[ SET_SIZE ];
    fillWithRandomPoints( morePoints, SET_SIZE );
    for ( size_t i = 0; i < SUBSET_SIZE; i++ )
    {
        points[ i ] = morePoints[ i ];
    }
    del::Set<del::Point> set ( SET_SIZE, morePoints );
    set.subSetFromTop( subset );
}

*/
