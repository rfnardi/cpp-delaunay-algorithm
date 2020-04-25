namespace del {

    class Point {
        
        public:
            float p[ 3 ];

            /**
             * Um ponto é definido a partir de 3 coordenadas.
             * 
             * @param P Coordenadas em float.
            */
            Point ( float P[ 3 ] );

            /**
             * Operador atribuição de um ponto é a atribuição de suas coordenadas.
            */
            Point operator = ( Point P );
            
            /**
             * Operador soma entre dois pontos é a soma entre suas coordenadas.
            */
            Point operator + ( Point P );

            /**
             * Operador subtração entre dois pontos é a subtração entre suas coordenadas.
            */
            Point operator - ( Point P );

            /**
             * Operador comparação de igualdade entre dois pontos é a comparação  de igualdade entre suas coordenadas.
            */
            bool operator == ( Point P );

            /**
            * calcula a distância do ponto instanciado até um outro ponto informado como arguemento dessa função
            */
            float distancia ( Point P );
        
    };
	
};