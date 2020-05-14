#ifndef DEL_SPHERE_H
#define DEL_SPHERE_H
#include <iostream>
#include <cmath>
#include"./Point.hpp"


namespace del {


  class Find_Centro_Esfera 
  {
  
    public:
      Find_Centro_Esfera (); //constructor

      float A[3], B[3], C[3], delta_z, raio; //declaration
      float Jacobiano [3][3];

      Point Centro_0, Centro;
      
      //variáveis de simplificação das contas:
      float alpha, beta, gamma, delta;
      
      //o que este método está fazendo mesmo????
      float Distancia(Point , Point);

      //Método que retorna o ponto central da esfera que circunscreve os 3 vértices do triangulo
      Point retorna_centro(Point, Point, Point);

  };


}; /* del */
#endif
