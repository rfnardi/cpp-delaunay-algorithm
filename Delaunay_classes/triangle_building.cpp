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
    
    point operator ++ (point P)
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

    ~point();
  };
  
  point::point(/* args */)
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

    size_t k, VIZ_A, VIZ_B;

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
                  if (P1 == P2)
                  {
                    //define triangulo ABC: candidato à triangulação de Delaunay
                    float ABC[3][3]={
                      {AB[0][0], AB[0][1], AB[0][2]},
                      {AB[1][0], AB[1][1], AB[1][2]},
                      {P1.p[0], P1.p[1], P1.p[2]}
                    };
                    
                    for (int j = 0; j < 3; j++) {
                      find_center_sphere_obj.A[j]= ABC[0][j];
                      find_center_sphere_obj.B[j]= ABC[1][j];       //faz passagem por valor dos pontos A, B e C para o objeto find_center_sphere_obj
                      find_center_sphere_obj.C[j]= ABC[2][j];
                    }
                    
                  }
                  
                }
              }
            }
          }
          
          

          



        }
    
    

    //calcula centro da esfera que circunscreve A, B e C. <------------------------ já escrito. Método de Newton
    del::Find_Centro_esfera find_center_sphere_obj;      // cria objeto da classe Find_Centro_esfera,  a qual calcula o centro da esfera que circunscreve os pontos A,B e C
        


    float Centro_Circunf_ABC[3];
    for (int i = 0; i < 3; i++) 
    {
      Centro_Circunf_ABC[i]= find_center_sphere_obj.centro[i];
    }
    float Raio = find_center_sphere_obj.Raio;
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
