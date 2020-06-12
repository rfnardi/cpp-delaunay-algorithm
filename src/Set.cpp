#ifndef DEL_SET_C
#define DEL_SET_C

#include <math.h>
#include "./Set.hpp"

/****************************************************************************/
/*																			*/
/*								  METHODS									*/
/*																			*/
/****************************************************************************/
template <typename T>
del::Set<T>::Set ( T* points, int size )
{
	this->points = points;
	this->size = size;
}

template <typename T>
std::string del::Set<T>::to_string( void )
{
	std::string str = "[\n";
	for ( int i = 0; i < this->size; i++ )
	{
		str += this->points[ i ].to_string() + "\n";
	}
	str += "]";
	
	return str;
}


template <typename T>
void del::Set<T>::exchangeListPositions ( T* pos1, T* pos2 )
{
	T tmp = *( pos1 );
	*( pos1 ) = *( pos2 );
	*( pos2 ) = tmp;
}

template <typename T>
void del::Set<T>::orderByDistance ( T p )
{
	// std::cout << "Distâncias referentes ao ponto " << p.to_string() << std::endl;
	for ( size_t i = 0; i < this->size; i++ )
	{
		for ( size_t j = i; j > 0; j-- )
		{
			T Pj = this->points[ j ], Pj_1 = this->points[ j - 1 ];
			
			// std::cout << "i = " << i << " e j = " << j << std::endl;
			// std::cout << "Pj = " << Pj.to_string() << std::endl;
			del::distance Dj = Pj.distancia( p );
			// std::cout << "Pj-1 = " << Pj_1.to_string() << std::endl;
			del::distance Dj_1 = Pj_1.distancia( p );
			
			// std::cout << "Dj = " << Dj << " e Dj-1 = " << Dj_1 << std::endl ;
			// std::cout << "Dj " << ( ( Dj < Dj_1 ) ? "é" : "não é" ) << " menor que Dj-1" << std::endl;
			
			if ( Dj < Dj_1 )
			{
				// std::cout << "Trocando Pj " << Pj.to_string() << " e Pj-1 " << Pj_1.to_string() << " de posição." << std::endl;
				this->exchangeListPositions( ( this->points + j ), ( this->points + j - 1 ) );
			}

			// std::cout << std::endl;
		}
		
	}
}

template <typename T>
del::Set<T> del::Set<T>::subSetFromTop ( T* points, int size )
{
	for ( size_t i = 0; i < size; i++ )
	{
		*( points ) = *( this->points + i );
	}
	return del::Set<T> ( points, size );
}

#endif
