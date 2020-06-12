#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../libs/catch.hpp"
#include "../src/Point.cpp"
#include "../src/Set.hpp"

#define MAX_LOOP_NUMBER 100

del::coordinate randomCoordinate ()
{
    return rand() % 10;
}

del::Point randomPoint()
{
    del::coordinate
        x = randomCoordinate(),
        y = randomCoordinate(),
        z = randomCoordinate();
    del::Point p ( x, y, z );
    return p;
}

TEST_CASE( "Validando operador igualdade.", "[point]" )
{
    for ( int i = 0; i < MAX_LOOP_NUMBER; i++ )
    {
        del::Point p1 = randomPoint();
        del::Point p2 = p1;
        bool comparison = ( p1 == p2 );
        CHECK( true == comparison );
    }
}

TEST_CASE( "Instância sem valores para construtor deve ser (0,0,0).", "[point]" )
{
    del::Point p1;
    del::Point p2 ( 0, 0, 0 );
    bool comparison = ( p1 == p2 );
    CHECK( true == comparison );
}

TEST_CASE( "Distâncias iguais para mesmos pontos entre os métodos estáticos e não estáticos.", "[point]" )
{
    for ( int i = 0; i < MAX_LOOP_NUMBER; i++ )
    {
        del::Point p1 = randomPoint();
        del::Point p2 = randomPoint();
        del::distance dist1 = p1.distancia( p2 );
        del::distance dist2 = del::Point::distancia( p1, p2 );
        CHECK( dist1 == dist2 );
    }
}

TEST_CASE( "Cálculo de distâncias deve ser simétrico.", "[point]" )
{
    for ( int i = 0; i < MAX_LOOP_NUMBER; i++ )
    {
        del::Point p1 = randomPoint();
        del::Point p2 = randomPoint();
        CHECK( p1.distancia( p2 ) == p2.distancia( p1 ) );
    }
}



TEST_CASE( "Validando reordenação de Set em relação a um ponto P", "[point,set]" )
{
    del::Point points1[ MAX_LOOP_NUMBER ];
    del::Point points2[ MAX_LOOP_NUMBER ];
    for ( int i = 0; i < MAX_LOOP_NUMBER; i++ )
    {
        points2[ i ] = del::Point ( i, 0, 0 );
        if ( i != MAX_LOOP_NUMBER - 1 )
        {
            points1[ i ] = del::Point ( i+1, 0, 0 );
        }
        else
        {
            points1[ i ] = del::Point ( 0, 0, 0 );
        }
        
        
    }
    del::Set<del::Point> set ( points1, MAX_LOOP_NUMBER );
    set.orderByDistance( del::Point ( 0, 0, 0 ) );
    for ( int i = 0; i < MAX_LOOP_NUMBER; i++ )
    {
        bool comparison = points2[ i ] == points1 [ i ];
        CHECK( true == comparison );
    }
}