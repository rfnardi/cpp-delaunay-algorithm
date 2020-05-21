#ifndef DEL_Point_C
#define DEL_Point_C

#include "./Point.hpp"
#include <math.h>
#include <string>

void del::Point::setCoordinates ( int dim, float coords[] )
{
	for( int i = 0; i < dim; i++ ) {
		this->p[ i ] = coords[ i ];
	}
}

void del::Point::operator = ( del::Point P )
{
	this->p[ 0 ] = P.p[ 0 ];
	this->p[ 1 ] = P.p[ 1 ];
	this->p[ 2 ] = P.p[ 2 ];
}

del::Point del::Point::operator + ( del::Point P )
{
	del::Point Point;
	Point.p[ 0 ] = this->p[ 0 ] + P.p[ 0 ];
	Point.p[ 1 ] = this->p[ 1 ] + P.p[ 1 ];
	Point.p[ 2 ] = this->p[ 2 ] + P.p[ 2 ];

	return Point;
}

del::Point del::Point::operator - ( del::Point P )
{
	del::Point Point;
	Point.p[0] = this->p[0] - P.p[0];
	Point.p[1] = this->p[1] - P.p[1];
	Point.p[2] = this->p[2] - P.p[2];

	return Point;
}

bool del::Point::operator == (del::Point P)
{
	return ( this->p[0] == P.p[0] && this->p[1] == P.p[1] && this->p[2] == P.p[2] );
}

std::string del::Point::to_string( void )
{
	std::string str = "(";
	// loop in old way. change this!
    for ( int i = 0; i < 3; i++ ) {
        str += std::to_string( this->p[ i ] );
        if ( i < 3 - 1 ) {
            str += ",";
        } else {
            str += ")";
        }
    }
    return str;
}

int del::Point::begin ( void )
{
	return 0;
}

int del::Point::end ( void )
{
	return 2;
}

float del::Point::distancia ( del::Point P )
{
	return sqrt( pow( this->p[ 0 ] - P.p[ 0 ], 2 ) + pow( this->p[ 1 ] - P.p[ 1 ], 2 ) + pow( this->p[ 2 ] - P.p[ 2 ], 2 ) );
}

#endif
