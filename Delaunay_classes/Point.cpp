#include <math.h>
#include "Point.hpp"

del::Point::Point ( float P[ 3 ] )
{
    for ( int i = 0; i < 3; i++ ) {
        this->p[ i ] = P[ i ];
    }
}

del::Point del::Point::operator = ( del::Point P ) 
{
    this->p[0]=P.p[0];
    this->p[1]=P.p[1];
    this->p[2]=P.p[2];
}

del::Point del::Point::operator + ( del::Point P )
{
    float coords[ 3 ];
    for ( int i = 0; i < 3; i++ ) {
        coords[ i ] = this->p[ i ] + P.p[ i ];
    }
    del::Point new_point ( coords );
    return new_point;
}

del::Point del::Point::operator - ( del::Point P )
{
    float coords[ 3 ];
    for ( int i = 0; i < 3; i++ ) {
        coords[ i ] = this->p[ i ] - P.p[ i ];
    }
    del::Point new_point ( coords );
    return new_point;
}

bool del::Point::operator == ( del::Point P )
{
    for ( int i = 0; i < 3; i++ ) {
        if ( this->p[ i ] != P.p[ i ] ) return false;
    }
    return true;
}

float del::Point::distancia ( del::Point P )
{
    float sum = 0;
    for ( int i = 0; i < 3; i++ ) {
        sum += pow( this->p[ i ] - P.p[ i ], 2 );
    }
    return sqrt( sum );
}
