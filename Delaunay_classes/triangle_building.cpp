#ifndef TRIANGLE_BUILD
#define TRIANGLE_BUILD

#include "./Triangle.hpp"
#include "./Point.hpp"
#include "./triangle_building.hpp"
#include "./convex_hull.hpp"
#include "./Vizinhanca.hpp"

  void del::Triangle_Building::Recebe_Catalogo(std::vector<std::vector<del::Point>> neighboorhoodsBook)
  {
    this->Catalogo_Viz = neighboorhoodsBook;
  }

  del::Triangle del::Triangle_Building::Point_based_Triangle_Building (del::Point A)
  {

    long unsigned int VIZ_A, VIZ_B, VIZ_C;

    //encontra vizinhança do ponto A:
    for (size_t k = 0; k < Catalogo_Viz.size(); k++)
    {
      del::Point P;
      P = Catalogo_Viz[k][0];

      if (A == P)
      {
        VIZ_A = k;
      }

    }

    //ponto B se localiza na segunda linha da vizinhança de A:
    del::Point B;
    B = Catalogo_Viz[VIZ_A][1];


    //encontra vizinhança do ponto B:
    for (size_t k = 0; k < Catalogo_Viz.size(); k++)
    {
      del::Point P;
      P = Catalogo_Viz[k][0];

      if (B == P)
      {
        VIZ_B = k;
      }

    }

    del::Center_Sphere center_sphere_obj; //cria objeto da classe que calcula centro da esfera que circunscreve 3 pontos
    del::Point Centro_Circunf_ABC; //variável para armazenar o centro da esfera que circunscreve os pontos A, B e C.
    float Raio; //variável para armazenar o raio da esfera calculada pelo método da classe Center_Sphere
    bool encontrou, criterio_Delaunay;
    float d;
    float ABC[3][3]; //armazena os 3 pontos A, B e C : candidatos a triangulo de Delaunay
    del::Triangle triangle_found;


    // (do ... while loop) procura ponto C nas vizinhanças de A e B, monta triangulo, encontra esfera que circunscreve A, B e C e aplica método de Delaunay:
    do
    {


      //procura ponto que seja vizinho COMUM de A e B - ponto C:
      del::Point P1;
      del::Point P2;
      del::Point C;

      /*parte da segunda linha da tabela de vizinhos de A pq a primeira linha é o próprio A*/
      for (size_t linha_A = 1; linha_A < Catalogo_Viz[VIZ_A].size(); linha_A++)
      {
        for (size_t col_A = 0; col_A < 3; col_A++)
        {
          P1.p[col_A] = Catalogo_Viz[VIZ_A][linha_A][col_A];
          for (size_t linha_B = 1; linha_B < Catalogo_Viz[VIZ_B].size(); linha_B++)
          {
            for (size_t col_B = 0; col_B < 3; col_B++)
            {
              P2.p[col_B] = Catalogo_Viz[VIZ_B][linha_B][col_B];
              if ( (P1 == P2) && !(P1 == B) && !(P1 == A) ) //P1 == P2 é o PONTO C !!!
              {
                C = P1;

                Centro_Circunf_ABC = center_sphere_obj.Find(A, B, C);

                Raio = sqrt( pow((A.p[0]-Centro_Circunf_ABC.p[0]),2) + pow((A.p[1]-Centro_Circunf_ABC.p[1]),2) + pow((A.p[2]-Centro_Circunf_ABC.p[2]),2) );

                del::Point P;
                // encontra vizinhança do ponto C:
                for (size_t k = 0; k < Catalogo_Viz.size(); k++)
                {

                  P = Catalogo_Viz[k][0];

                  if (C == P)
                    {
                      VIZ_C = k;
                    }
                }

                encontrou = false;
                //procurando pontos da vizinhança de A dentro da esfera:
                for (size_t i = 2; i < Catalogo_Viz[VIZ_A].size(); i++)
                {
                  P = Catalogo_Viz[VIZ_A][i];

                  d = P.distancia(Centro_Circunf_ABC);
                  if ((d<Raio) && !(P == A) && !(P == B) && !(P == C))
                  {
                    encontrou = true;
                    break;
                  }
                }

                //se não encontrou pto dentro da esfera na vizinhança de A, procura na vizinhança de B :
                if (!encontrou)
                {
                  for (size_t i = 1; i < Catalogo_Viz[VIZ_B].size(); i++)
                  {
                    P = Catalogo_Viz[VIZ_B][i];

                    d = P.distancia(Centro_Circunf_ABC);
                    if ((d<Raio) && !(P == A) && !(P == B) && !(P == C))
                    {
                      encontrou = true;
                      break;
                    }
                  }
                }

                //se não encontrou pto dentro da esfera na vizinhança de B, procura na vizinhança de C:
                if (!encontrou)
                {
                  for (size_t i = 1; i < Catalogo_Viz[VIZ_C].size(); i++)
                  {
                    P = Catalogo_Viz[VIZ_C][i] ;

                    d = P.distancia(Centro_Circunf_ABC);
                    if ((d<Raio) && !(P == A) && !(P == B) && !(P == C))
                    {
                      encontrou = true;
                      break;
                    }
                  }
                }

                //triangulo ABC é admitido na triangulação
                if (!encontrou)
                {
                  criterio_Delaunay = true;
                  triangle_found.A=A;
                  triangle_found.B=B;
                  triangle_found.C=C;
                }

              }//fim do if que certifica que o ponto encontrado é comum às vizinhanças de A e B
            }

          }//fim do loop for nas linhas da vizinhança de B
        }


      }//fim do loop for nas linhas da vizinhança de A

    }while(!criterio_Delaunay); //fim do "do ... while" loop

    return triangle_found;

  } //Fim do método "Point_based_Triangle_Building"


  del::Triangle edge_based_Triangle_Building (del::Edge edge, del::Triangle Base_triangle)
  {

    long unsigned int VIZ_A, VIZ_B, VIZ_C;

    del::Point A = edge.first_Point;
    del::Point B = edge.second_Point;

    del::Point P;
    //encontra vizinhança do ponto A:
    for (size_t k = 0; k < Catalogo_Viz.size(); k++)
    {
      P = Catalogo_Viz[k][0];
      if (A == P)
      {
        VIZ_A = k;
      }
    }

    //encontra vizinhança do ponto B:
    for (size_t k = 0; k < Catalogo_Viz.size(); k++)
    {
      P = Catalogo_Viz[k][0];
      if (B == P)
      {
        VIZ_B = k;
      }
    }

    del::Triangle New_triangle;
    del::Center_Sphere center_sphere_obj; //cria objeto da classe que calcula centro da esfera que circunscreve 3 pontos
    del::Point Centro_Circunf_ABC; //variável para armazenar o centro da esfera que circunscreve os pontos A, B e C.
    float Raio; //variável para armazenar o raio da esfera calculada pelo método da classe Center_Sphere
    bool encontrou_ponto_dentro_da_esfera, encontrou_ponto_C, encontrou_triangulo_valido, criterio_Delaunay_satisfeito;
    float d;
    float ABC[3][3]; //armazena os 3 pontos A, B e C : candidatos a triangulo de Delaunay

    do
    {
      //procura ponto que seja vizinho comum de A e B - ponto C:
      del::Point P1;
      del::Point P2;
      del::Point C;
      for (size_t linha_A = 0; linha_A < Catalogo_Viz[VIZ_A].size(); linha_A++)//BUSCA DO PONTO C
      {
        for (size_t col_A = 0; col_A < 3; col_A++)//BUSCA DO PONTO C
        {
          P1.p[col_A] = Catalogo_Viz[VIZ_A][linha_A][col_A];
          for (size_t linha_B = 0; linha_B < Catalogo_Viz[VIZ_B].size(); linha_B++)//BUSCA DO PONTO C
          {
            for (size_t col_B = 0; col_B < 3; col_B++)//BUSCA DO PONTO C
            {
              P2.p[col_B] = Catalogo_Viz[VIZ_B][linha_B][col_B];
              encontrou_ponto_C = false;
              if ( (P1 == P2) && !(P1 == B) && !(P1 == A) ) //P1 == P2 é o PONTO C !!!
              {
                C = P1;
                encontrou_ponto_C = true;
                Centro_Circunf_ABC = center_sphere_obj.Find(A, B, C);

                Raio = sqrt( pow((A.p[0]-Centro_Circunf_ABC.p[0]),2) + pow((A.p[1]-Centro_Circunf_ABC.p[1]),2) + pow((A.p[2]-Centro_Circunf_ABC.p[2]),2) );

                for (size_t k = 0; k < Catalogo_Viz.size(); k++) // encontra vizinhança do ponto C
                {
                  P = Catalogo_Viz[k][0];
                  if (P1 == P)
                    {
                      VIZ_C = k;
                    }
                }

                encontrou_ponto_dentro_da_esfera = false;
                //procurando pontos da vizinhança de A dentro da esfera:
                for (size_t i = 2; i < Catalogo_Viz[VIZ_A].size(); i++)
                {
                  P = Catalogo_Viz[VIZ_A][i];
                  d = P.distancia(Centro_Circunf_ABC);
                  if ((d<Raio) && !(P == A) && !(P == B) && !(P == C))
                  {
                    encontrou_ponto_dentro_da_esfera = true; //caso isso for verdadeiro, o programa deve continuar a busca por outro ponto C
                    break;
                  }
                }

                //se não encontrou pto dentro da esfera na vizinhança de A, procura na vizinhança de B :
                if (!encontrou_ponto_dentro_da_esfera)
                {
                  for (size_t i = 1; i < Catalogo_Viz[VIZ_B].size(); i++)
                  {
                    P = Catalogo_Viz[VIZ_B][i];
                    d = P.distancia(Centro_Circunf_ABC);
                    if ((d<Raio) && !(P == A) && !(P == B) && !(P == C))
                    {
                      encontrou_ponto_dentro_da_esfera = true; //caso isso for verdadeiro, o programa deve continuar a busca por outro ponto C
                      break;
                    }
                  }
                }

                if (!encontrou_ponto_dentro_da_esfera)
                {
                  //procurando pontos da vizinhança de C dentro da esfera:
                  for (size_t i = 1; i < Catalogo_Viz[VIZ_C].size(); i++)
                  {
                    P = Catalogo_Viz[VIZ_C][i];
                    d = P.distancia(Centro_Circunf_ABC);
                    if ((d<Raio) && !(P == A) && !(P == B) && !(P == C))
                    {
                      encontrou_ponto_dentro_da_esfera = true; //caso isso for verdadeiro, o programa deve continuar a busca por outro ponto C
                      break;
                    }
                  }
                }

               //SE NENHUM PONTO FOR ENCONTRADO NO INTERIOR DA ESFERA QUE CIRCUNSCREVE O TRIANGULO ABC,
               //CONSTRUA New_triangle E COMPARE COM O 'not_this_triangle' fornecido no argumento deste método
               if (!encontrou_ponto_dentro_da_esfera)
                {
                 criterio_Delaunay_satisfeito = true;
                 New_triangle.A=A;
                 New_triangle.B=B;
                 New_triangle.C=C;
                }
                //caso sejam diferentes, New_triangle é cuspido como resultado e a busca é terminada (sai do 'do ... while' loop)
                if (New_triangle == Base_triangle)
                {
                  encontrou_triangulo_valido = true;
                  New_triangle.same_curl(Base_triangle);
                }
              }//fim do if que certifica que o ponto encontrado é comum às vizinhanças de A e B
            }

          }//fim do loop for de busca do ponto C nas linhas da vizinhança de B
        }

      }//fim do loop for de busca do ponto C nas linhas da vizinhança de A

      //contemplando caso em que nenhum ponto C satisfaz a condição de Delaunay:
      //(se varreu as vizinhanças de A e B e não encontrou qqr C então construa o 'triangulo" trivial) --- neste caso o edge deve ser reconhecido como um membro definitivo do Convex_Hull
      if (!encontrou_ponto_C | !encontrou_triangulo_valido)
      {
        edge.really_a_Convex_Hull_member = true;
        del::Point Origem;
        Origem.p[0]=0.0;
        Origem.p[1]=0.0;
        Origem.p[2]=0.0;
        New_triangle.A = Origem;
        New_triangle.B = Origem;
        New_triangle.C = Origem;

        encontrou_triangulo_valido = true; //sai do loop 'do...while' e método retorna o triangulo trivial
      }

    }while( !encontrou_triangulo_valido);


    return New_triangle;

  } //Fim do método "edge_based_Triangle_Building"
#endif
