namespace del {

  class point
  {
  private:
    /* data */
  public:
    point(/* args */);

    float p[3];
    float x;
    float y;
    float z;
    
    point operator + (point P)
    {
      point new_point;
      new_point.p[0] = p[0] + P.p[0];
      new_point.p[1] = p[1] + P.p[1];
      new_point.p[2] = p[2] + P.p[2];
      
      return new_point;
    }

    bool operator == (point P)
    {
      if (p[0] == P.p[0] && p[1] == P.p[1] && p[2] == P.p[2])
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    float distancia (point X, point Y)
    {
      float d=sqrt(pow(X.p[0]-Y.p[0], 2 ) + pow(X.p[1]-Y.p[1], 2 ) + pow(X.p[2]-Y.p[2], 2 ))
      return d;
    }

    ~point();
  };
  
  point::point()
  {
  }
  
  point::~point()
  {
  }
  



  class triangulo_Delaunay {       //classe que determina quais são os triangulos de Delaunay
  private:
    /* data */

  public:
    triangulo_Delaunay ();

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
        N_B = k;
      }
      
    }
    
    del::Find_Centro_esfera find_center_sphere_obj; //cria objeto da classe que calcula centro da esfera que circunscreve 3 pontos
    del::point Centro_Circunf_ABC; //variável para armazenar o centro da esfera que circunscreve os pontos A, B e C.
    float Raio; //variável para armazenar o raio da esfera calculada pelo método da classe Find_Centro_esfera

    //define aresta AB:
    float AB[2][3];
        while (/* Delaunay triangle not found */)      
        {
          
         for (size_t i = 0; i < 2; i++)
          {
            for (size_t j = 0; j < 3; j++)
            {
              AB[i][j]=catalogo[N_A][i][j];
            }
            
          }
          //procura ponto que seja vizinho comum de A e B - ponto C: <-------------------------- to be done!!
          del::point P1;
          del::point P2;
          for (size_t linha_A = 0; linha_A < catalogo[VIZ_A].size(); linha_A++)
          {
            for (size_t col_A = 0; col_A < 3; col_A++)
            {
              P1.p[col_A] = catalogo[VIZ_A][linha_A][col_A];
              for (size_t linha_B = 0; linha_B < catalogo[VIZ_B].size(); linha_B++)
              {
                for (size_t col_B = 0; col_B < 3; col_B++)
                {
                  P2.p[j] = catalogo[VIZ_B][linha_B][col_B];
                  if ( (P1 == P2) && (P1 != A) && (P1 != B) ) //P1 == P2 é o PONTO C !!!
                  {
                    //define triangulo ABC: candidato à triangulação de Delaunay
                    float ABC[3][3]={
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
                            N_C = k;
                          }                    
                      }
                        //procurando pontos da vizinhança de A dentro da esfera:
                        for (size_t i = 2; i < catalogo[VIZ_A].size(); i++) 
                        {
                          P.p[0]=catalogo[VIZ_A][i][0];
                          P.p[1]=catalogo[VIZ_A][i][1];
                          P.p[2]=catalogo[VIZ_A][i][2];
                          d= distancia(P , Centro_Circunf_ABC);
                          if ((d<Raio) && (P! == A)&& (P! == B)&& (P! == C))
                          {
                            break;
                          }
                          
                        }
                        //procurando pontos da vizinhança de B dentro da esfera:
                        for (size_t i = 1; i < catalogo[VIZ_B].size(); i++)
                        {
                          P.p[0]=catalogo[VIZ_B][i][0];
                          P.p[1]=catalogo[VIZ_B][i][1];
                          P.p[2]=catalogo[VIZ_B][i][2];
                          d= distancia(P , Centro_Circunf_ABC);
                          if ((d<Raio) && (P! == A)&& (P! == B)&& (P! == C))
                          {
                            break;
                          }
                        }
                        //procurando pontos da vizinhança de C dentro da esfera:
                        for (size_t i = 1; i < catalogo[VIZ_C].size(); i++)
                        {
                          P.p[0]=catalogo[VIZ_C][i][0];
                          P.p[1]=catalogo[VIZ_C][i][1];
                          P.p[2]=catalogo[VIZ_C][i][2];
                          d= distancia(P , Centro_Circunf_ABC);
                          if ((d<Raio) && (P! == A)&& (P! == B)&& (P! == C))
                          {
                            break;
                          }
                        }
                  }
                  
                }
              }
            }
          }
          
          

          



        }
    
    
    //procura pontos nas vizinhanças de A, B e C que estejam dentro da Esfera:
    for (int i = 0; i < count; i++)
    {
      float d = sqrt(pow(Centro_Circunf_ABC[0]-x[j],2)+pow(Centro_Circunf_ABC[1]-y[j],2)+pow(Centro_Circunf_ABC[2]-z[j],2));
      if (d<Raio)
      {
        //substitui ponto C pelo ponto encontrado
        break; //sai do loop
      }
      
      
    }
    

          //SE (busca não retornar nenhum ponto) ENTÃO (triangulo é admitido na triangulação de Delaunay)
          if (/* condition */) {
            /* code */
          }
          //CASO CONTRÁRIO, ponto encontrado D é usado para montar novo triangulo (ABD, BCD ou ABD) candidato à triangulação de Delaunay
          else{};
          //caso o triangulo seja admitido na triangulação, ENTÃO determina orientação correta dos vértices
    //faz segunda busca por triangulo de Delaunay nas vizinhanças de A e B.
      //Se encontrar segundo triangulo de Delaunay, então aresta AB é colocada no conjunto de arestas internas.
      //Se não encontrar segundo triângulo de Delaunay, então aresta é colocada no conjunto de arestas de borda.

    virtual ~triangulo_Delaunay ();
  };

} /* del */
