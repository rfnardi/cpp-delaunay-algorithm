#ifndef DEL_NEIGHBORHOOD_H
#define DEL_NEIGHBORHOOD_H

#include <vector>
#include "./Point.hpp"

namespace del {

    class Vizinhanca {
        private:
            std::vector<Point> universalSet;
            float raio;
            Point referencial;
            Point* vizinhos;
            bool debug = true;
            unsigned int maxNeighboorHoodSize;

        public:
            /**
             * Inicializa o catálogo a partir de um conjunto de pontos no espaço e um valor para o número máximo de vizinhos em cada vizinhança.
             *
             * @param universalSet O conjunto de todos os pontos do sólido.
			 *
			 * @param maxNeighboorHoodSize quantidade de pontos em cada vizinhança
            */
            Vizinhanca ( std::vector<Point> universalSet, unsigned int maxNeighboorHoodSize );

            ~Vizinhanca ();

            /**
             * Apresenta as coordenadas de um ponto de forma humanamente legível no console.
             *
             * @param ponto Conjunto de coordendas
            */
            std::string debugar_ponto ( Point ponto );

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
            void definir_referencial ( Point ponto );

            /**
             * Retorna a vizinhança do ponto de referência.
             *
             * @return vizinhança do ponto de referência.
            */
            // std::vector<Point> obter_vizinhos ();
            Point* obter_vizinhos ();

            /**
             * Calcula a vizinhança de todos os pontos do conjunto.
             * Retora uma lista de vizinhanças sendo o ponto referencial sempre o primeiro vetor da lista.
             *
             * @return obter_catalogo_de_vizinhancas de vizinhos.
            */
            // std::vector<std::vector<Point>> obter_catalogo_de_vizinhancas ();
            std::vector<Point*> obter_catalogo_de_vizinhancas ();

            /**
             * Obtém uma listas de pontos na interseção das vizinhanças.
             * A lista é ordenada considerando ponto de referencia o primeiro ponto da vizinhança do primeiro parametro.
             *
             * @return lista de pontos pertencentes a interseção das vizinhanças.
            */
            // std::vector<Point> obter_intersecao_entre_vizinhancas ( std::vector<Point> nhb1, std::vector<Point> nhb2 );
            Point* obter_intersecao_entre_vizinhancas ( Point* nhb1, Point* nhb2 );

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
            float obter_distancia_de ( Point ponto );

            /**
             * Verifica se o ponto é vizinho do ponto de referência.
             *
             * @param ponto Coordenadas do ponto.
             * @return verdadeiro caso serja vizinho, false caso conrtário.
            */
            bool e_vizinho_de ( Point ponto );

            /**
             * Adiciona ponto para a lista de vizinhos do ponto de referência.
             *
             * @param ponto Coordenadas do ponto.
            */
            void adicionar_vizinho ( Point ponto );

            /**
             * Compara distancia referencial de dois pontos
             *
             * @param p1 ponto.
             * @param p2 ponto.
             * @return se o primeiro argumento está mais próximo do referencial.
            */
            bool comparar_distancia_referencial ( Point p1, Point p2 );

            /**
             * Ordena os pontos da vizinhança em ordem crescente de distância ao ponto referencial.
             *
             * @param viz vizinhança.
             * @return Vizinhança ordenada.
            */
            Point* ordenar_vizinhanca ( Point* viz );
    };

};
#endif
