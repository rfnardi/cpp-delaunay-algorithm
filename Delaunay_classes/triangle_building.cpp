namespace del {

  class triangulo_Delaunay {
  private:
    /* data */

  public:
    triangulo_Delaunay (arguments);

    //pega componentes do primeiro vetor do catálogo de ptos_vizinhos - ponto A:
    float A[3];
    //Pega ponto mais próximo da lista de vizinhos - ponto B:
    float B[3];
    //define aresta AB:
    float AB[3][2]={
      {A[0], A[1], A[2]},
      {B[0], B[1], B[2]}
    };
    //procura ponto que seja vizinho comum de A e B - ponto C:

    //define triangulo ABC: candidato à triangulação de Delaunay
    float ABC[3][3]={
      {A[0], A[1], A[2]},
      {B[0], B[1], B[2]},
      {C[0], C[1], C[2]}
    };
    //calcula centro da esfera que circunscreve A, B e C. <------------------------ já escrito. Método de Newton
    float Centro_Circunf_ABC[3];
    for (size_t i = 0; i < 3; i++) {
      Centro_Circunf_ABC[i]= Find_Centro_esfera.centro[i];
    }
    float Raio = Find_Centro_esfera.Raio;
    //procura pontos nas vizinhas de A, B e C que estejam dentro da Esfera:

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
