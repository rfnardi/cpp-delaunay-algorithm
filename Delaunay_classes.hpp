namespace del {

class quadrilatero_vizinhos {
private:
  /* data */

public:
  quadrilatero_vizinhos (array A[3]; array B[3]; array C[3]; array D[3]);
  virtual ~quadrilatero_vizinhos ();
};

class catalogo_vizinhos {
private:
  /* data */

public:
  catalogo_vizinhos (array P, std::vector<float> ptos_vizinhos );
  virtual ~catalogo_vizinhos ();
};



class triangulo_Delaunay {
private:
  /* data */

public:
  triangulo_Delaunay (arguments);
  virtual ~triangulo_Delaunay ();
};

}
