namespace del {

class quadrilatero_vizinhos {
private:
  /* data */

public:
  quadrilatero_vizinhos (array A[3]; array B[3]; array C[3]; array D[3]);
  virtual ~quadrilatero_vizinhos ();
};

class obter_catalogo_de_vizinhancas_vizinhos {
private:
  /* data */

public:
<<<<<<< HEAD
  obter_catalogo_de_vizinhancas_vizinhos (array P[3]; std::vector<float> ptos_vizinhos;);
=======
  obter_catalogo_de_vizinhancas_vizinhos (array P, std::vector<float> ptos_vizinhos );
>>>>>>> feature/obter_catalogo_de_vizinhancas-de-vizinhos
  virtual ~obter_catalogo_de_vizinhancas_vizinhos ();
};



class triangulo_Delaunay {
private:
  /* data */

public:
  triangulo_Delaunay (arguments);
  virtual ~triangulo_Delaunay ();
};

}
