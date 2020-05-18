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


}; /* fim do namespace del */
