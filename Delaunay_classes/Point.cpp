#ifndef DEL_Point_C
#define DEL_Point_C

#include "./Point.hpp"
#include <math.h>
#include <string>

del::Point::Point ( float coords[ 3 ] )
{
	this->x = coords[ 0 ];
	this->y = coords[ 1 ];
	this->z = coords[ 2 ];
}

del::Point::~Point(){};

void del::Point::operator = ( del::Point P )
{
	this->x = P.x;
	this->y = P.y;
	this->z = P.z;
}

del::Point del::Point::operator + ( del::Point P )
{
	float coords[ 3 ];
	coords[ 0 ] = this->x + P.x;
	coords[ 1 ] = this->y + P.y;
	coords[ 2 ] = this->z + P.z;

	return Point( coords );
}

del::Point del::Point::operator - ( del::Point P )
{
	float coords[ 3 ];
	coords[ 0 ] = this->x - P.x;
	coords[ 1 ] = this->y - P.y;
	coords[ 2 ] = this->z - P.z;

	return Point( coords );
}

bool del::Point::operator == (del::Point P)
{
	return ( this->x == P.x && this->y == P.y && this->z == P.z );
}

std::string del::Point::to_string( void )
{
	std::string str = "(";
	str += std::to_string( this->x );
	str += ",";
	str += std::to_string( this->y );
	str += ",";
	str += std::to_string( this->z );
	str += ")";
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
	return sqrt( pow( this->x - P.x, 2 ) + pow( this->y - P.y, 2 ) + pow( this->z - P.z, 2 ) );
}

#endif
