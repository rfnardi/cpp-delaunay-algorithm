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
          Triangle_Building ();
          ~Triangle_Building ();

          std::vector<std::vector<del::Point>> Catalogo_Viz;

          void Recebe_Catalogo (std::vector<std::vector<del::Point>> neighboorhoodsBook);

          del::Triangle Point_based_Triangle_Building (del::Point );

          del::Triangle Edge_based_Triangle_Building (del::Edge , Triangle );


        }; //fim da classe "triangle building"


  }; /* fim do namespace del */
#endif
