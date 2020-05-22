#ifndef DEL_POINT_H
#define DEL_POINT_H
#include <string>

namespace del
{

class Point
{
	public:
		Point();
		~Point();

		/**
		 * Set origin of coordinates as default Point.
		 * This strtategy avoids the program of exiting with EXIT_FAILURE status in some situations.
		 * A list of defined Point doesn't sure you all these have defined coordinates (float p[3] bellow).
		 * Require computation on Point's coordinates may cause system failure.
		 * Solutions:
		 * 1. Set default coordinates (implemented)
		 * 2. Set constructor and obligate coordinates insertion at the object implementation (more logic, agree?).
		*/
		int dim = 3;
		float p[ 3 ] = { 0, 0, 0 };

		/**
		 * Inicializa Point passando uma lista de coordenadas.
		 * Replace this by constructor.
		 *
		 * @return int
		*/
		void setCoordinates ( int dim, float coords[] );

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

		/**
		 * Iterador de coordenadas de Point
		*/
		// Make use old style of iterator (using int)
		using iterator = std::vector<float>::iterator;

		/**
		 * Operador de incremento de iterador de coordenadas de Point.
		 *
		 * @param iterator
		 * @return int
		*/
		// iterator operator ++ ( void );

		/**
		 * Operador de decremento de iterador de coordenadas de Point.
		 *
		 * @param iterator
		 * @return int
		*/
		// iterator operator -- ( void );

		/**
		 * Valor da primeira coordanada de Point
		 *
		 * @return int
		*/
		int begin ( void );

		/**
		 * Valor da última coordanada de Point
		 *
		 * @return int
		*/
		int end ( void );

		/**
		 * Representa Point em forma de string para debug.
		 *
		 * @return string
		*/
		std::string to_string ( void );

		/**
		 * Retorna o número de coordenadas em Point.
		 *
		 * @return int
		*/
		int size ( void );

		/**
		 * Calcula a distância entre Points.
		 * Implement a MetricSpace class and move all distance computation to that
		 *
		 * @param Point
		 * @return float
		*/
		float distancia ( Point P );

}; //fim da classe Point

}
#endif
