namespace del {

  class triangulo_Delaunay {       //classe que determina quais são os triangulos de Delaunay
  private:
    /* data */

  public:
    triangulo_Delaunay ();

    //pega componentes do primeiro vetor do catálogo de ptos_vizinhos - ponto A:
    float A[3];
    //Pega ponto mais próximo da lista de vizinhos - ponto B: <--------- falta determinar como ele vai econtrar este ponto
    float B[3];
    //define aresta AB:
    float AB[3][2]={
      {A[0], A[1], A[2]},
      {B[0], B[1], B[2]}
    };
    //procura ponto que seja vizinho comum de A e B - ponto C: <-------------------------- to be done!!

    //define triangulo ABC: candidato à triangulação de Delaunay
    float ABC[3][3]={
      {A[0], A[1], A[2]},
      {B[0], B[1], B[2]},
      {C[0], C[1], C[2]}
    };

    //calcula centro da esfera que circunscreve A, B e C. <------------------------ já escrito. Método de Newton
    del::Find_Centro_esfera find_center_sphere_obj;      // cria objeto da classe Find_Centro_esfera,  a qual calcula o centro da esfera que circunscreve os pontos A,B e C
        for (int j = 0; j < 3; j++) {
          find_center_sphere_obj.A[j]= ABC[0][j];
          find_center_sphere_obj.B[j]= ABC[1][j];       //faz passagem por valor dos pontos A, B e C para o objeto find_center_sphere_obj
          find_center_sphere_obj.C[j]= ABC[2][j];
        }


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
