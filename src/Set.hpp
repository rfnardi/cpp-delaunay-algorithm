#ifndef DEL_SET_H
#define DEL_SET_H
#include "./Point.hpp"
namespace del
{
// making the code more semantical
typedef float distance;

class Set
{

	public:
		/****************************************************************************/
		/*																			*/
		/*								PROPERTIES									*/
		/*																			*/
		/****************************************************************************/
		Point* points;
		int size;

		
		/****************************************************************************/
		/*																			*/
		/*								  METHODS									*/
		/*																			*/
		/****************************************************************************/
		/**
		 * Inicializa Set passando uma lista de pontos.
		 *
		 * @param points
		 * @param size
		*/
		Set( Point* points, int size );

		/**
		 * Representa Set em forma de string para debug.
		 *
		 * @return string
		*/
		std::string to_string ( void );

		/**
		 * Calcula a distâncias entre P e os pontos da lista.
		 *
		 * @param Point
		 * @return distance pointer
		*/
		void orderByDistance ( Point p );

}; //fim da classe Set

}
#endif
