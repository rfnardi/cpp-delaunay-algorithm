#include <vector>

namespace del {

    class Vizinhanca {
        private:
            std::vector<std::vector<float>> conjuntoUniverso;
            float raio;
            std::vector<float> referencial;
            std::vector<std::vector<float>> vizinhos;
            bool debug = true;

        public:
            /**
             * Inicializa o catálogo a partir de um conjunto de pontos no espaço.
             * 
             * @param conjuntoUniverso O conjunto de todos os pontos do sólido.
            */
            Vizinhanca ( std::vector<std::vector<float>> conjuntoUniverso );

            /**
             * Apresenta as coordenadas de um ponto de forma humanamente legível no console.
             * 
             * @param ponto Conjunto de coordendas
            */
            std::string debugar_ponto ( std::vector<float> ponto );

            /**
             * Define o raio de vizinhança.
             * 
             * @param raio O raio da vizinhança.
            */
            void definir_raio ( float raio );

            /**
             * Define um ponto de referência.
             * 
             * @param ponto O ponto de referência.
            */
            void definir_referencial ( std::vector<float> ponto );

            /**
             * Retorna a vizinhança do ponto de referência.
             * 
             * @return vizinhança do ponto de referência.
            */
            std::vector<std::vector<float>> obter_vizinhos ();

            /**
             * Calcula a vizinhança de todos os pontos do conjunto.
             * Retora uma lista de vizinhanças sendo o ponto referencial sempre o primeiro vetor da lista.
             * 
             * @return catalogo de vizinhos.
            */
            std::vector<std::vector<std::vector<float>>> obter_catalogo_de_vizinhancas ();

            /**
             * Ativa mensagens no console
             * 
            */
            void ativar_debug ();

            /**
             * Desativa mensagens no console
             * 
            */
            void desativar_debug ();

        private:
            /**
             * Calcula a distância entre um ponto e o ponto referencial.
             * 
             * @param ponto Coordenadas de um ponto.
             * @return Distância entre os pontos a e b.
            */
            float obter_distancia_de ( std::vector<float> ponto );

            /**
             * Verifica se o ponto é vizinho do ponto de referência.
             * 
             * @param ponto Coordenadas do ponto.
             * @return verdadeiro caso serja vizinho, false caso conrtário.
            */
            bool e_vizinho_de ( std::vector<float> ponto );

            /**
             * Adiciona ponto para a lista de vizinhos do ponto de referência.
             * 
             * @param ponto Coordenadas do ponto.
            */
            void adicionar_vizinho ( std::vector<float> ponto );

            /**
             * Compara distancia referencial de dois pontos
             * 
             * @param p1 ponto.
             * @param p2 ponto.
             * @return se o primeiro argumento está mais próximo do referencial.
            */
            bool comparar_distancia_referencial ( std::vector<float> p1, std::vector<float> p2 );

            /**
             * Ordena os pontos da vizinhança em ordem crescente de distância ao ponto referencial.
             * 
             * @param viz vizinhança.
             * @return Vizinhança ordenada.
            */
            std::vector<std::vector<float>> ordenar_vizinhanca ( std::vector<std::vector<float>> viz );
    };

};