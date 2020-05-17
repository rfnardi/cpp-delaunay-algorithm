namespace del
{


      class Triangle_Building       //classe que determina quais são os triangulos de Delaunay
      {

      public:
        Triangle_Building ();
        ~Triangle_Building ();

        Triangle Point_based_Triangle_Building (del::Point );

        Triangle Edge_based_Triangle_Building (del::Edge , Triangle );


      }; //fim da classe "triangle building"



              //caso o triangulo seja admitido na triangulação, ENTÃO determina orientação correta dos vértices
        //faz segunda busca por triangulo de Delaunay nas vizinhanças de A e B.
          //Se encontrar segundo triangulo de Delaunay, então aresta AB é colocada no conjunto de arestas internas.
          //Se não encontrar segundo triângulo de Delaunay, então aresta é colocada no conjunto de arestas de borda.

        virtual ~Triangle_Building ();

}; /* fim do namespace del */
