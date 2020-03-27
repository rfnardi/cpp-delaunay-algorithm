namespace del {

    class catalogo_vizinhos {
        private:
            vector<float> conjunto_universo[ 3 ];
            float ponto_referencial[ 3 ];
            float raio;

        public:
            /**
             * Inicializa o catálogo a partir de um conjunto de pontos no espaço.
             * 
             * @param conjunto_universo O conjunto de todos os pontos do sólido.
            */
            catalogo_vizinhos ( vector<float> conjunto_universo[ 3 ] );

            /**
             * Define uma distância de vizinhança.
             * 
             * @param raio O raio da vizinhança.
            */
            void define_raio_vizinhanca ( float raio );

            /**
             * Define um ponto de referência.
             * 
             * @param ponto O ponto de referência.
            */
            void define_referencial ( float ponto[ 3 ] );

            /**
             * Informa as coordenadas do ponto referencial.
             * 
             * @return Ponto definido como referencial.
            */
            float ver_referencial ();

            /**
             * Calcula a distância entre dois pontos.
             * 
             * @param a Coordenadas de um ponto.
             * @param b Coordenadas de um ponto.
             * @return Distância entre os pontos a e b.
            */
            float distancia_entre ( float a[ 3 ], float b[ 3 ] );

            /**
             * Verifica se o ponto é vizinho do ponto de referência.
             * 
             * @param ponto Coordenadas do ponto.
             * @return verdadeiro caso serja vizinho, false caso conrtário.
            */
            bool e_vizinho ( float ponto[ 3 ] );
    }

}