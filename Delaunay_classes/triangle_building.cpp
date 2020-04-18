namespace del {

      class point
      {
      private:
        /* data */
      public:
        point(/* args */);

        float p[3];
        

        point operator = (del::point P) //asignment operator
        {
          this->p[0]=P.p[0];
          this->p[1]=P.p[1];
          this->p[2]=P.p[2];

        }
        
        point operator + (del::point P)
        {
          point new_point;
          new_point.p[0] = this->p[0] + P.p[0];
          new_point.p[1] = this->p[1] + P.p[1];
          new_point.p[2] = this->p[2] + P.p[2];
          
          return new_point;
        }

        point operator - (del::point P)
        {
          point new_point;
          new_point.p[0] = this->p[0] - P.p[0];
          new_point.p[1] = this->p[1] - P.p[1];
          new_point.p[2] = this->p[2] - P.p[2];
          
          return new_point;
        }

        bool operator == (point P)
        {
          if (this->p[0] == P.p[0] && this->p[1] == P.p[1] && this->p[2] == P.p[2])
          {
            return true;
          }
          else
          {
            return false;
          }
        }

        float distancia ( point Y) //calcula a distância do ponto instanciado até um outro ponto informado como arguemento dessa função
        {
          float d = sqrt(pow(p[0]-Y.p[0], 2 ) + pow(p[1]-Y.p[1], 2 ) + pow(p[2]-Y.p[2], 2 ));
          return d;
        }

        ~point();

      }; //fim da classe point
      
      point::point()
      {
      }
      
      point::~point()
      {
      }
      



      class triangle_building       //classe que determina quais são os triangulos de Delaunay
      {
      private:
        /* data */

      public:
        triangle_building ();

        triangle_Delaunay point_based_triangle_building (del::point A)
        {
                    long unsigned int k, VIZ_A, VIZ_B, VIZ_C;

                    del::point A;

                    //encontra vizinhança do ponto A:
                    for (size_t k = 0; k < catalogo.size(); k++)
                    {
                      del::point P;
                      P.p[0]=catalogo[k][0][0];
                      P.p[1]=catalogo[k][0][1];
                      P.p[2]=catalogo[k][0][2];
                      if (A == P)
                      {
                        VIZ_A = k;
                      }
                      
                    }
                    //ponto B se localiza na segunda linha da vizinhança de A:
                    del::point B;
                      B.p[0]=catalogo[VIZ_A][1][0];
                      B.p[1]=catalogo[VIZ_A][1][1];
                      B.p[2]=catalogo[VIZ_A][1][2];

                    //encontra vizinhança do ponto B:
                    for (size_t k = 0; k < catalogo.size(); k++)
                    {
                      del::point P;
                      P.p[0]=catalogo[k][0][0];
                      P.p[1]=catalogo[k][0][1];
                      P.p[2]=catalogo[k][0][2];
                      if (B == P)
                      {
                        VIZ_B = k;
                      }
                      
                    }
                    
                    del::Find_Centro_esfera find_center_sphere_obj; //cria objeto da classe que calcula centro da esfera que circunscreve 3 pontos
                    del::point Centro_Circunf_ABC; //variável para armazenar o centro da esfera que circunscreve os pontos A, B e C.
                    float Raio; //variável para armazenar o raio da esfera calculada pelo método da classe Find_Centro_esfera
                    bool encontrou;
                    float d;
                    float ABC[3][3]; //armazena os 3 pontos A, B e C : candidatos a triangulo de Delaunay

                    
                    float AB[2][3]; //define aresta AB
                        
                        // (do ... while loop) procura ponto C nas vizinhanças de A e B, monta triangulo, encontra esfera que circunscreve A, B e C e aplica método de Delaunay: 
                        do     
                        {
                          
                        for (size_t i = 0; i < 2; i++)
                          {
                            for (size_t j = 0; j < 3; j++)
                            {
                              AB[i][j]=catalogo[VIZ_A][i][j];
                            }
                            
                          }
                          //procura ponto que seja vizinho comum de A e B - ponto C: 
                          del::point P1;
                          del::point P2;
                          del::point C;
                          for (size_t linha_A = 0; linha_A < catalogo[VIZ_A].size(); linha_A++)
                          {
                            for (size_t col_A = 0; col_A < 3; col_A++)
                            {
                              P1.p[col_A] = catalogo[VIZ_A][linha_A][col_A];
                              for (size_t linha_B = 0; linha_B < catalogo[VIZ_B].size(); linha_B++)
                              {
                                for (size_t col_B = 0; col_B < 3; col_B++)
                                {
                                  P2.p[col_B] = catalogo[VIZ_B][linha_B][col_B];
                                  if ( (P1 == P2) && (P1 != A) && (P1 != B) ) //P1 == P2 é o PONTO C !!!
                                  {
                                    C = P1;
                                    //monta triangulo ABC: candidato à triangulação de Delaunay
                                    ABC[][]={
                                      {AB[0][0], AB[0][1], AB[0][2]},
                                      {AB[1][0], AB[1][1], AB[1][2]},
                                      {P1.p[0], P1.p[1], P1.p[2]}
                                    };
                                    
                                    for (int j = 0; j < 3; j++) {
                                      find_center_sphere_obj.A[j]= ABC[0][j];    //faz passagem por valor dos pontos A, B e C
                                      find_center_sphere_obj.B[j]= ABC[1][j];       // para o objeto find_center_sphere_obj
                                      find_center_sphere_obj.C[j]= ABC[2][j];
                                    }
                                    for (int i = 0; i < 3; i++) //encontra centro da esfera
                                      {
                                        Centro_Circunf_ABC.p[i]= find_center_sphere_obj.centro[i];
                                      }
                                    Raio = find_center_sphere_obj.Raio; //guarda raio da esfera

                                        for (size_t k = 0; k < catalogo.size(); k++) // encontra vizinhança do ponto C
                                        {
                                          del::point P;
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
                        del::triangle_Delaunay T;
                        T.A = A;
                        T.B = B;
                        T.C = C;

                        return T;
                        
                        
                        
                    




        } //Fim do método "point_based_triangle_building"

        triangle_Delaunay edge_based_triangle_building (del::edge Edge)
        {

                    long unsigned int k, VIZ_A, VIZ_B, VIZ_C;

                    del::point A = Edge.first_point;
                    del::point B = Edge.second_point

                    //encontra vizinhança do ponto A:
                    for (size_t k = 0; k < catalogo.size(); k++)
                    {
                      del::point P;
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
                      del::point P;
                      P.p[0]=catalogo[k][0][0];
                      P.p[1]=catalogo[k][0][1];
                      P.p[2]=catalogo[k][0][2];
                      if (B == P)
                      {
                        VIZ_B = k;
                      }
                      
                    }
                    
                    del::Find_Centro_esfera find_center_sphere_obj; //cria objeto da classe que calcula centro da esfera que circunscreve 3 pontos
                    del::point Centro_Circunf_ABC; //variável para armazenar o centro da esfera que circunscreve os pontos A, B e C.
                    float Raio; //variável para armazenar o raio da esfera calculada pelo método da classe Find_Centro_esfera
                    bool encontrou, kein_Dreieck_gefunden;
                    float d;
                    float ABC[3][3]; //armazena os 3 pontos A, B e C : candidatos a triangulo de Delaunay

                    
                    float AB[2][3]; //define aresta AB
                        
                        do     
                        {
                          
                        for (size_t i = 0; i < 2; i++)
                          {
                            for (size_t j = 0; j < 3; j++)
                            {
                              AB[i][j]=catalogo[N_A][i][j];
                            }
                            
                          }
                          //procura ponto que seja vizinho comum de A e B - ponto C: 
                          del::point P1;
                          del::point P2;
                          del::point C;
                          for (size_t linha_A = 0; linha_A < catalogo[VIZ_A].size(); linha_A++)
                          {
                            for (size_t col_A = 0; col_A < 3; col_A++)
                            {
                              P1.p[col_A] = catalogo[VIZ_A][linha_A][col_A];
                              for (size_t linha_B = 0; linha_B < catalogo[VIZ_B].size(); linha_B++)
                              {
                                for (size_t col_B = 0; col_B < 3; col_B++)
                                {
                                  P2.p[col_B] = catalogo[VIZ_B][linha_B][col_B];
                                  if ( (P1 == P2) && (P1 != A) && (P1 != B) ) //P1 == P2 é o PONTO C !!!
                                  {
                                    C = P1;
                                    //monta triangulo ABC: candidato à triangulação de Delaunay
                                    ABC[][]={
                                      {AB[0][0], AB[0][1], AB[0][2]},
                                      {AB[1][0], AB[1][1], AB[1][2]},
                                      {P1.p[0], P1.p[1], P1.p[2]}
                                    };
                                    
                                    for (int j = 0; j < 3; j++) {
                                      find_center_sphere_obj.A[j]= ABC[0][j];    //faz passagem por valor dos pontos A, B e C
                                      find_center_sphere_obj.B[j]= ABC[1][j];       // para o objeto find_center_sphere_obj
                                      find_center_sphere_obj.C[j]= ABC[2][j];
                                    }
                                    for (int i = 0; i < 3; i++) //encontra centro da esfera
                                      {
                                        Centro_Circunf_ABC.p[i]= find_center_sphere_obj.centro[i];
                                      }
                                    Raio = find_center_sphere_obj.Raio; //guarda raio da esfera

                                        for (size_t k = 0; k < catalogo.size(); k++) // encontra vizinhança do ponto C
                                        {
                                          del::point P;
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
                          
                          

                          //contemplando caso em que nenhum ponto C satisfaz a condição de Delaunay:
                          if ((linha_A == catalogo[VIZ_A].size()-1) && (linha_B == catalogo[VIZ_B].size()-1) && (!encontrou))
                          {
                            kein_Dreieck_gefunden = true;
                            del::triangle_Delaunay T;
                            del::point Origem;
                            Origem.p[0]=0;
                            Origem.p[1]=0;
                            Origem.p[2]=0;
                            T.A = Origem;
                            T.B = Origem;
                            T.C = Origem;
                            break;
                          }



                        }while(!encontrou);

                        //triangulo ABC é admitido na triangulação
                        if (!kein_Dreieck_gefunden)
                        {
                          triangle_Delaunay T;
                          T.A = A;
                          T.B = B;
                          T.C = C;
                        }
                        
                        
                        return T;
                        
                        
                    






        } //Fim do método "edge_based_triangle_building"

        
    }; //fim da classe "triangle building"
        

              
              //caso o triangulo seja admitido na triangulação, ENTÃO determina orientação correta dos vértices
        //faz segunda busca por triangulo de Delaunay nas vizinhanças de A e B.
          //Se encontrar segundo triangulo de Delaunay, então aresta AB é colocada no conjunto de arestas internas.
          //Se não encontrar segundo triângulo de Delaunay, então aresta é colocada no conjunto de arestas de borda.

        virtual ~triangle_building ();

}; /* fim do namespace del */
