namespace del {

  class triangulo_Delaunay {
  private:
    /* data */

  public:
    triangulo_Delaunay (arguments);

    //pega componentes do primeiro vetor do catálogo de ptos_vizinhos: ponto A
    //Pega ponto mais próximo da lista de vizinhos: ponto B
    //define aresta AB
    //procura ponto que seja vizinho comum de A e B: ponto C
    //define triangulo ABC: candidato à triangulação de Delaunay
    //calcula centro da espera que circunscreve A, B e C. <------------------------ já escrito. Método de Newton
        //procura pontos nas vizinhas de A, B e C que estejam dentro da Esfera
          //SE (busca não retornar nenhum ponto) ENTÃO (triangulo é admitido na triangulação de Delaunay)
          //CASO CONTRÁRIO, ponto encontrado D é usado para montar novo triangulo (ABD, BCD ou ABD) candidato à triangulação de Delaunay
          //caso o triangulo seja admitido na triangulação, ENTÃO determina orientação correta dos vértices

    virtual ~triangulo_Delaunay ();
  };

} /* del */
