#ifndef DEL_SPHERE
#define DEL_SPHERE
#include <iostream>
#include <cmath>
#include "./Centro_Esfera_Aprox.hpp"
#include "./Point.hpp"


float del::Find_Centro_Esfera::Distancia(del::Point P1, del::Point P2)
{
  float d = pow((P1.p[0]-P2.p[0]),2) + pow((P1.p[1]-P2.p[1]),2) + pow((P1.p[2]-P2.p[2]),2);

  return d;
};

del::Point del::Find_Centro_Esfera::retorna_centro(del::Point A, del::Point B, del::Point C)
{
  //chute de ordem zero para o centro da esfera (média das coordenadas dos vértices) :
    for (size_t i = 0; i < 3; i++) 
    {
        Centro_0.p[i] = (A.p[i] + B.p[i] + C.p[i])/3;
    }

  del::Find_Centro_Esfera::Jacobiano = 
    {
      {2*(Centro_0.p[0]-A.p[0]), 2*(Centro_0.p[1]-A.p[1]), 2*(Centro_0.p[2]-A.p[2])},
      {2*(Centro_0.p[0]-B.p[0]), 2*(Centro_0.p[1]-B.p[1]), 2*(Centro_0.p[2]-B.p[2])},
      {2*(Centro_0.p[0]-C.p[0]), 2*(Centro_0.p[1]-C.p[1]), 2*(Centro_0.p[2]-C.p[2])}
    }

  //variáveis de simplificação das contas:
  del::Find_Centro_Esfera::alpha = (Jacobiano[0][0] - (Jacobiano[0][2]*Jacobiano[1][0])/Jacobiano[1][2] );
  del::Find_Centro_Esfera::beta = (Jacobiano[0][1] - (Jacobiano[0][2]*Jacobiano[1][1])/Jacobiano[1][2] );
  del::Find_Centro_Esfera::gamma = (Jacobiano[1][0] - (Jacobiano[1][2]*Jacobiano[2][0])/Jacobiano[2][2] );
  del::Find_Centro_Esfera::delta = (Jacobiano[1][1] - (Jacobiano[1][2]*Jacobiano[2][1])/Jacobiano[2][2] );

  //determinando ponto central da espera que engloba os 3 vértices A, B e C do triângulo:
  Centro.p[0] = ((Jacobiano[0][2]/Jacobiano[1][2])*Distancia(Centro_0, B) - Distancia(Centro_0, A))*(beta/gamma)/(alpha - gamma*beta/delta) + Centro_0.p[0];

  Centro.p[1] = (((Jacobiano[1][2]/Jacobiano[2][2])*Distancia(Centro_0, C) - Distancia(Centro_0, B))/delta - (Centro.p[0] - Centro_0.p[0])*gamma;

  Centro.p[2] = (Distancia(Centro_0, C) - Jacobiano[2][0]*(Centro.p[0] - Centro_0.p[0]) - Jacobiano[2][1]*(Centro.p[1] - Centro_0.p[1]))/Jacobiano[2][2];

  float Raio = Distancia(Centro, A);

  return Centro;
    
  
};
#endif