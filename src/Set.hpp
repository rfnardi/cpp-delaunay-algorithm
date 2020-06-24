#ifndef DEL_SET_H
#define DEL_SET_H
#include "./Point.hpp"
namespace del
{
// making the code more semantical
#ifndef distance
typedef float distance;
#endif

template <typename T>
class Set
{

	public:
		/****************************************************************************/
		/*																			*/
		/*								PROPERTIES									*/
		/*																			*/
		/****************************************************************************/
		T* points;
		size_t size;

		
		/****************************************************************************/
		/*																			*/
		/*								  METHODS									*/
		/*																			*/
		/****************************************************************************/
		/**
		 * Inicializa Set passando o tamanho da lista de pontos.
		 *
		 * @param size
		*/
		Set( int size );

		/**
		 * Inicializa Set passando uma lista de pontos.
		 *
		 * @param points
		 * @param size
		*/
		Set( int size, T* points );

		/**
		 * Copia os valores de um ponteiro para o ponteiro interno.
		 *
		*/
		void copyList ( T* points, size_t size );

		/**
		 * Representa Set em forma de string para debug.
		 *
		 * @return string
		*/
		std::string to_string ( void );

		/**
		 * Troca a posição entre dois pontos da lista.
		 *
		 * @param pos1
		 * @param pos2
		*/
		void exchangeListPositions ( T* pos1, T* pos2 );

		/**
		 * Calcula a distâncias entre P e os pontos da lista.
		 *
		 * @param T
		*/
		void orderByDistance ( T p );

		/**
		 * Gera um subconjunto a partir dos primeiros elementos da lista.
		 *
		 * @param points
		 * @param int
		*/
		void subSetFromTop ( Set subset );


		/****************************************************************************/
		/*																			*/
		/*								  OPERATORS									*/
		/*																			*/
		/****************************************************************************/
		/**
		 * Operador de Interseção entre Set.
		 *
		 * @param Point
		 * @return Point
		*/
		// Set operator - ( Point P );
}; //fim da classe Set

}
#include "Set.cpp"
#endif
