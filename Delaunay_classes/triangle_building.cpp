
  del::Triangle del::Point_based_Triangle_Building (del::Point A)
  {

    long unsigned int VIZ_A, VIZ_B, VIZ_C;

    //encontra vizinhança do ponto A:
    for (size_t k = 0; k < catalogo.size(); k++)
    {
      del::Point P;
      P.p[0]=catalogo[k][0][0];
      P.p[1]=catalogo[k][0][1];
      P.p[2]=catalogo[k][0][2];
      if (A == P)
      {
        VIZ_A = k;
      }

    }

    //ponto B se localiza na segunda linha da vizinhança de A:
    del::Point B;
    B.p[0]=catalogo[VIZ_A][1][0];
    B.p[1]=catalogo[VIZ_A][1][1];
    B.p[2]=catalogo[VIZ_A][1][2];

    //encontra vizinhança do ponto B:
    for (size_t k = 0; k < catalogo.size(); k++)
    {
      del::Point P;
      P.p[0]=catalogo[k][0][0];
      P.p[1]=catalogo[k][0][1];
      P.p[2]=catalogo[k][0][2];
      if (B == P)
      {
        VIZ_B = k;
      }

    }

    del::Center_Sphere center_sphere_obj; //cria objeto da classe que calcula centro da esfera que circunscreve 3 pontos
    del::Point Centro_Circunf_ABC; //variável para armazenar o centro da esfera que circunscreve os pontos A, B e C.
    float Raio; //variável para armazenar o raio da esfera calculada pelo método da classe Center_Sphere
    bool encontrou;
    float d;
    float ABC[3][3]; //armazena os 3 pontos A, B e C : candidatos a triangulo de Delaunay


    // (do ... while loop) procura ponto C nas vizinhanças de A e B, monta triangulo, encontra esfera que circunscreve A, B e C e aplica método de Delaunay:
    do
    {


      //procura ponto que seja vizinho COMUM de A e B - ponto C:
      del::Point P1;
      del::Point P2;
      del::Point C;

      /*parte da segunda linha da tabela de vizinhos de A pq a primeira linha é o próprio A*/
      for (size_t linha_A = 1; linha_A < catalogo[VIZ_A].size(); linha_A++)
      {
        for (size_t col_A = 0; col_A < 3; col_A++)
        {
          P1.p[col_A] = catalogo[VIZ_A][linha_A][col_A];
        }
        for (size_t linha_B = 1; linha_B < catalogo[VIZ_B].size(); linha_B++)
        {
          for (size_t col_B = 0; col_B < 3; col_B++)
          {
            P2.p[col_B] = catalogo[VIZ_B][linha_B][col_B];
          }
          if ( (P1 == P2) && (P1 != B) && (P1 != A) ) //P1 == P2 é o PONTO C !!!
          {
            C = P1;

            Centro_Circunf_ABC = center_sphere_obj.Find(A, B, C);

            Raio = sqrt( pow((A.p[0]-Centro_Circunf_ABC.p[0]),2) + pow((A.p[1]-Centro_Circunf_ABC.p[1]),2) + pow((A.p[2]-Centro_Circunf_ABC.p[2]),2) );

            // encontra vizinhança do ponto C:
            for (size_t k = 0; k < catalogo.size(); k++)
            {
              del::Point P;
              P.p[0]=catalogo[k][0][0];
              P.p[1]=catalogo[k][0][1];
              P.p[2]=catalogo[k][0][2];
              if (C == P)
                {
                  VIZ_C = k;
                }
            }

            //procurando pontos da vizinhança de A dentro da esfera:
            for (size_t i = 2; i < catalogo[VIZ_A].size(); i++)
            {
              P.p[0]=catalogo[VIZ_A][i][0];
              P.p[1]=catalogo[VIZ_A][i][1];
              P.p[2]=catalogo[VIZ_A][i][2];
              d= P.distancia(Centro_Circunf_ABC);
              if ((d<Raio) && (P! == A)&& (P! == B)&& (P! == C))
              {
                encontrou = true;
                break;
              }

            }
            if (encontrou)
            {
              break;
            }

                                        //procurando pontos da vizinhança de B dentro da esfera:
                                        for (size_t i = 1; i < catalogo[VIZ_B].size(); i++)
                                        {
                                          P.p[0]=catalogo[VIZ_B][i][0];
                                          P.p[1]=catalogo[VIZ_B][i][1];
                                          P.p[2]=catalogo[VIZ_B][i][2];
                                          d= P.distancia(Centro_Circunf_ABC);
                                          if ((d<Raio) && (P! == A)&& (P! == B)&& (P! == C))
                                          {
                                            encontrou = true;
                                            break;
                                          }
                                        }
                                        if (encontrou)
                                        {
                                          break;
                                        }
                                        //procurando pontos da vizinhança de C dentro da esfera:
                                        for (size_t i = 1; i < catalogo[VIZ_C].size(); i++)
                                        {
                                          P.p[0]=catalogo[VIZ_C][i][0];
                                          P.p[1]=catalogo[VIZ_C][i][1];
                                          P.p[2]=catalogo[VIZ_C][i][2];
                                          d= P.distancia(Centro_Circunf_ABC);
                                          if ((d<Raio) && (P! == A)&& (P! == B)&& (P! == C))
                                          {
                                            encontrou = true;
                                            break;
                                          }
                                          else
                                          {
                                            encontrou = false;
                                          }

                                        }
                                        if (encontrou)
                                        {
                                          break;
                                        }
                                  }

                                }
                              }
                            }
                          }







                        }while(!encontrou);

                        //triangulo ABC é admitido na triangulação
                        del::Triangle T;
                        T.A = A;
                        T.B = B;
                        T.C = C;

                        return T;








        } //Fim do método "Point_based_Triangle_Building"


        Triangle edge_based_Triangle_Building (del::edge Edge, Triangle Not_this_triangle)
        {


                    long unsigned int k, VIZ_A, VIZ_B, VIZ_C;

                    del::Point A = Edge.first_Point;
                    del::Point B = Edge.second_Point;

                    //encontra vizinhança do ponto A:
                    for (size_t k = 0; k < catalogo.size(); k++)
                    {
                      del::Point P;
                      P.p[0]=catalogo[k][0][0];
                      P.p[1]=catalogo[k][0][1];
                      P.p[2]=catalogo[k][0][2];
                      if (A == P)
                      {
                        VIZ_A = k;
                      }

                    }


                    //encontra vizinhança do ponto B:
                    for (size_t k = 0; k < catalogo.size(); k++)
                    {
                      del::Point P;
                      P.p[0]=catalogo[k][0][0];
                      P.p[1]=catalogo[k][0][1];
                      P.p[2]=catalogo[k][0][2];
                      if (B == P)
                      {
                        VIZ_B = k;
                      }

                    }

                    del::Triangle New_triangle;
                    del::Center_Sphere center_sphere_obj; //cria objeto da classe que calcula centro da esfera que circunscreve 3 pontos
                    del::Point Centro_Circunf_ABC; //variável para armazenar o centro da esfera que circunscreve os pontos A, B e C.
                    float Raio; //variável para armazenar o raio da esfera calculada pelo método da classe Center_Sphere
                    bool encontrou_ponto_dentro_da_esfera, kein_Dreieck_gefunden, encontrou_triangulo_valido;
                    float d;
                    float ABC[3][3]; //armazena os 3 pontos A, B e C : candidatos a triangulo de Delaunay

                        do
                        {


                          //procura ponto que seja vizinho comum de A e B - ponto C:
                          del::Point P1;
                          del::Point P2;
                          del::Point C;
                          for (size_t linha_A = 0; linha_A < catalogo[VIZ_A].size(); linha_A++)//BUSCA DO PONTO C
                          {
                            for (size_t col_A = 0; col_A < 3; col_A++)//BUSCA DO PONTO C
                            {
                              P1.p[col_A] = catalogo[VIZ_A][linha_A][col_A];
                              for (size_t linha_B = 0; linha_B < catalogo[VIZ_B].size(); linha_B++)//BUSCA DO PONTO C
                              {
                                for (size_t col_B = 0; col_B < 3; col_B++)//BUSCA DO PONTO C
                                {
                                  P2.p[col_B] = catalogo[VIZ_B][linha_B][col_B];
                                  if ( (P1 == P2) && (P1 != A) && (P1 != B) ) //P1 == P2 é o PONTO C !!!
                                  {
                                    C = P1;
                                    //monta triangulo ABC: candidato à triangulação de Delaunay
                                    ABC[][]={
                                      {A.p[0], A.p[1], A.p[2]},
                                      {B.p[0], B.p[1], B.p[2]},
                                      {P1.p[0], P1.p[1], P1.p[2]}
                                    };

                                    for (int j = 0; j < 3; j++) {
                                      center_sphere_obj.A[j]= ABC[0][j];    //faz passagem por valor dos pontos A, B e C
                                      center_sphere_obj.B[j]= ABC[1][j];       // para o objeto center_sphere_obj
                                      center_sphere_obj.C[j]= ABC[2][j];
                                    }
                                    for (int i = 0; i < 3; i++) //encontra centro da esfera
                                      {
                                        Centro_Circunf_ABC.p[i]= center_sphere_obj.centro[i];
                                      }
                                    Raio = center_sphere_obj.Raio; //guarda raio da esfera

                                        for (size_t k = 0; k < catalogo.size(); k++) // encontra vizinhança do ponto C
                                        {
                                          del::Point P;
                                          P.p[0]=catalogo[k][0][0];
                                          P.p[1]=catalogo[k][0][1];
                                          P.p[2]=catalogo[k][0][2];
                                          if (P1 == P)
                                            {
                                              VIZ_C = k;
                                            }
                                        }
                                        //procurando pontos da vizinhança de A dentro da esfera:
                                        for (size_t i = 2; i < catalogo[VIZ_A].size(); i++)
                                        {
                                          P.p[0]=catalogo[VIZ_A][i][0];
                                          P.p[1]=catalogo[VIZ_A][i][1];
                                          P.p[2]=catalogo[VIZ_A][i][2];
                                          d= P.distancia(Centro_Circunf_ABC);
                                          if ((d<Raio) && (P! == A)&& (P! == B)&& (P! == C))
                                          {
                                            encontrou_ponto_dentro_da_esfera = true; //caso isso for verdadeiro, o programa deve continuar a busca por outro ponto C
                                            break;
                                          }

                                        }
                                        if (encontrou_ponto_dentro_da_esfera)
                                        {
                                          break;
                                        }

                                        //procurando pontos da vizinhança de B dentro da esfera:
                                        for (size_t i = 1; i < catalogo[VIZ_B].size(); i++)
                                        {
                                          P.p[0]=catalogo[VIZ_B][i][0];
                                          P.p[1]=catalogo[VIZ_B][i][1];
                                          P.p[2]=catalogo[VIZ_B][i][2];
                                          d= P.distancia(Centro_Circunf_ABC);
                                          if ((d<Raio) && (P! == A)&& (P! == B)&& (P! == C))
                                          {
                                            encontrou_ponto_dentro_da_esfera = true; //caso isso for verdadeiro, o programa deve continuar a busca por outro ponto C
                                            break;
                                          }
                                        }
                                        if (encontrou_ponto_dentro_da_esfera)
                                        {
                                          break;
                                        }
                                        //procurando pontos da vizinhança de C dentro da esfera:
                                        for (size_t i = 1; i < catalogo[VIZ_C].size(); i++)
                                        {
                                          P.p[0]=catalogo[VIZ_C][i][0];
                                          P.p[1]=catalogo[VIZ_C][i][1];
                                          P.p[2]=catalogo[VIZ_C][i][2];
                                          d= P.distancia(Centro_Circunf_ABC);
                                          if ((d<Raio) && (P! == A)&& (P! == B)&& (P! == C))
                                          {
                                            encontrou_ponto_dentro_da_esfera = true; //caso isso for verdadeiro, o programa deve continuar a busca por outro ponto C
                                            break;
                                          }
                                          else
                                          {
                                             //SE NENHUM PONTO FOR ENCONTRADO NO INTERIOR DA ESFERA QUE CIRCUNSCREVE O TRIANGULO ABC,
                                             //CONSTRUA New_triangle E COMPARE COM O 'not_this_triangle' fornecido no argumento deste método

                                            New_triangle.A = A;
                                            New_triangle.B = B;
                                            New_triangle.C = C;

                                            if (New_triangle == Not_this_triangle)
                                            {
                                              break;
                                            }
                                            else //caso sejam diferentes, New_triangle é cuspido como resultado e a busca é terminada (sai do 'do ... while' loop)
                                            {
                                              encontrou_triangulo_valido = true;
                                            }


                                          }

                                        }


                                        if (encontrou_ponto_dentro_da_esfera)
                                        {
                                          break; //continua busca por ponto C
                                        }
                                  }

                                }
                              }
                            }




                          }//fim do loop de varredura na vizinhança de A ... FIM DA BUSCA PELO PONTO C



                          //contemplando caso em que nenhum ponto C satisfaz a condição de Delaunay:
                          //(se varreu as vizinhanças de A e B e não encontrou qqr C então construa o 'triangulo" trivial) --- neste caso o edge deve ser reconhecido como um membro definitivo do convex_hull
                          if ((linha_A == catalogo[VIZ_A].size()-1) && (linha_B == catalogo[VIZ_B].size()-1) && (!encontrou_ponto_dentro_da_esfera))
                          {

                            del::Point Origem;
                            Origem.p[0]=0.0;
                            Origem.p[1]=0.0;
                            Origem.p[2]=0.0;
                            New_triangle.A = Origem;
                            New_triangle.B = Origem;
                            New_triangle.C = Origem;

                            encontrou_triangulo_valido = true; //sai do loop 'do...while' e método retorna o triangulo trivial
                          }



                        }while(!encontrou_triangulo_valido);


        return New_triangle;

        } //Fim do método "edge_based_Triangle_Building"


    }; //fim da classe "triangle building"



              //caso o triangulo seja admitido na triangulação, ENTÃO determina orientação correta dos vértices
        //faz segunda busca por triangulo de Delaunay nas vizinhanças de A e B.
          //Se encontrar segundo triangulo de Delaunay, então aresta AB é colocada no conjunto de arestas internas.
          //Se não encontrar segundo triângulo de Delaunay, então aresta é colocada no conjunto de arestas de borda.

        virtual ~Triangle_Building ();

}; /* fim do namespace del */
