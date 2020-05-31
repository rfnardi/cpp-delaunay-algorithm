#ifndef DEL_POINT_H
#define DEL_POINT_H
#include <string>

namespace del
{

class Point
{
	public:
		/****************************************************************************/
		/*																			*/
		/*								PROPERTIES									*/
		/*																			*/
		/****************************************************************************/
		float x = 0;
		float y = 0;
		float z = 0;

		
		/****************************************************************************/
		/*																			*/
		/*								  METHODS									*/
		/*																			*/
		/****************************************************************************/
		/**
		 * Inicializa Point passando uma lista de coordenadas.
		 * Replace this by constructor.
		 *
		 * @return int
		*/
		Point( float x = 0, float y = 0, float z = 0 );

		~Point();

		/**
		 * Representa Point em forma de string para debug.
		 *
		 * @return string
		*/
		std::string to_string ( void );

		/**
		 * Calcula a distância entre P e o ponto de referência.
		 *
		 * @param Point
		 * @return float
		*/
		float distancia ( Point P );

		/**
		 * Calcula a distância entre dois Point quaisquer.
		 *
		 * @param Point
		 * @param Point
		 * @return float
		*/
		float distancia ( const Point P1, const Point P2 );


		/****************************************************************************/
		/*																			*/
		/*									OPERATORS								*/
		/*																			*/
		/****************************************************************************/
		/**
		 * Operador de atribuição de Point.
		 *
		 * @param Point
		*/
		void operator = ( Point P ) ;

		/**
		 * Operador de soma entre Points.
		 *
		 * @param Point
		 * @return Point
		*/
		Point operator + ( Point P );

		/**
		 * Operador de subtração entre Points.
		 *
		 * @param Point
		 * @return Point
		*/
		Point operator - ( Point P );

		/**
		 * Operador de igualdade entre Points.
		 *
		 * @param Point
		 * @return boolean
		*/
		bool operator == ( Point P );

}; //fim da classe Point

}
#endif
