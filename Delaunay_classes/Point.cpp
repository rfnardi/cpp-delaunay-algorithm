#include "./Point.hpp"

del::Point operator = ( del::Point P ) 
{
	this->p[ 0 ] = P.p[ 0 ];
	this->p[ 1 ] = P.p[ 1 ];
	this->p[ 2 ] = P.p[ 2 ];
}

del::Point operator + ( del::Point P )
{
	del::Point point;
	point.p[ 0 ] = this->p[ 0 ] + P.p[ 0 ];
	point.p[ 1 ] = this->p[ 1 ] + P.p[ 1 ];
	point.p[ 2 ] = this->p[ 2 ] + P.p[ 2 ];
	
	return point;
}

del::Point operator - ( del::Point P )
{
	del::Point point;
	point.p[0] = this->p[0] - P.p[0];
	point.p[1] = this->p[1] - P.p[1];
	point.p[2] = this->p[2] - P.p[2];
	
	return point;
}

bool operator == (del::Point P)
{
	return ( this->p[0] == P.p[0] && this->p[1] == P.p[1] && this->p[2] == P.p[2] );
}

float distancia ( del::Point Y )
{
	float d = sqrt(pow(p[0]-Y.p[0], 2 ) + pow(p[1]-Y.p[1], 2 ) + pow(p[2]-Y.p[2], 2 ));
	return d;
}