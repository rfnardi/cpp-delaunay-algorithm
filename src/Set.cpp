#ifndef DEL_Set_C
#define DEL_Set_C

#include "./Set.hpp"
#include <math.h>

/****************************************************************************/
/*																			*/
/*								  METHODS									*/
/*																			*/
/****************************************************************************/
del::Set::Set ( Point* points, int size )
{
	this->points = points;
	this->size = size;
}

std::string del::Set::to_string( void )
{
	std::string str = "[\n";
	for ( int i = 0; i < this->size; i++ )
	{
		str += this->points[ i ].to_string() + "\n";
	}
	str += "]";
	
	return str;
}

void del::Set::orderByDistance ( del::Point p )
{
	std::cout << p.to_string() << std::endl;
	for ( size_t i = 0; i < this->size; i++ )
	{
		for ( size_t j = i; j > 0; j-- )
		{
			std::cout << "i = " << i << " e j = " << j << std::endl;
			std::cout << this->points[ j ].to_string() << std::endl;
			del::distance Dj = this->points[ j ].distancia( p );
			del::distance Dj_1 = this->points[ j - 1 ].distancia( p );
			std::cout << Dj << " - " << Dj_1 << std::endl;
			if ( this->points[ j ].distancia( p ) < this->points[ j - 1 ].distancia( p ) )
			{
				del::Point tmp = this->points[ j - 1 ];
				this->points[ j - 1 ] = this->points[ j ];
				this->points[ j ] = tmp;
			}
		}
		
	}
}

#endif
