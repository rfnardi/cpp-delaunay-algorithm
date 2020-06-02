#ifndef TRIANGLE_BUILD_H
#define TRIANGLE_BUILD_H
#include <vector>
#include "./Triangle.hpp"
#include "./Point.hpp"
#include "./convex_hull.hpp"

  namespace del
  {


        class Triangle_Building       //classe que determina quais são os triangulos de Delaunay
        {

        public:
          std::vector<std::vector<del::Point>> Catalogo_Viz;

          Triangle_Building (); // necessário apenas se formos definir uma operação para o construtor
          ~Triangle_Building (); // necessário apenas se formos definir uma operação para o destrutor

          /**
           * Recebe um catálogo de vizinhança.
           * @param neighboorhoodsBook catálogo de vizinhanças de pontos
           */
          void Recebe_Catalogo (std::vector<std::vector<del::Point>> neighboorhoodsBook);
          
          /**
           * Recebe um ponto e retorna o índice da vizinhança desse ponto dentro do catalago.
           * @param ponto ponto de referencia
           * @return -1 caso não haja vizinhança ou índice inteiro não negativo representando a ordem na lista de vizinhanças
           */
          int Get_Neighboorhood_Index_of ( Point ponto );

          /**
           * Recebe um ponto e retorna a vizinhança desse ponto.
           * @param ponto ponto de referencia
           * @return a vizinhança do ponto ou nulo.
           */
          std::vector<Point> Get_Neighboorhood_of ( Point ponto );

          // aqui dentro não precisa de del:: porque ----->>>  namespace { ... estamos aqui dentro ... }
          // e as declarações precisam receber um nome de variável --->>> ( tipo nomeDaVar )
          Triangle Point_based_Triangle_Building ( Point ponto );

          Triangle Edge_based_Triangle_Building ( Edge aresta , Triangle triangulo );


        }; //fim da classe "triangle building"


  }; /* fim do namespace del */
#endif
