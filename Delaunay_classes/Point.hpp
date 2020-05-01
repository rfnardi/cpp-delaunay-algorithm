namespace del {

class Point
{
	public:
		float p[ 3 ];

		/**
		 * Operador de atribuição de Point.
		 * 
		 * @param Point
		*/
		Point operator = ( Point P ) ;
		
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
		 * Calcula a distância entre Points.
		 * 
		 * @param Point
		 * @return float
		*/
		float distancia ( Point P );

}; //fim da classe point

}