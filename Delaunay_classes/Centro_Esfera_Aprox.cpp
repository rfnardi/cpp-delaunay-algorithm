#include <iostream>
#include <cmath>


namespace del {


  class Find_Centro_esfera {
  private:
    /* data */

  public:
    Find_Centro_esfera (arguments); //constructor

    float Centro_0[3], A[3], B[3], C[3], Centro[3], delta_z;
    float Jacobiano [3][3];

    //chute de ordem zero para o centro da esfera (média das coordenadas dos vértices) :
    for (size_t i = 0; i < 3; i++) {
        Centro_0[i] = (A[i] + B[i] + C[i])/3
    }


    Jacobiano = {
      {2*(Centro_0[0]-A[0]), 2*(Centro_0[1]-A[1]), 2*(Centro_0[2]-A[2])},
      {2*(Centro_0[0]-B[0]), 2*(Centro_0[1]-B[1]), 2*(Centro_0[2]-B[2])},
      {2*(Centro_0[0]-C[0]), 2*(Centro_0[1]-C[1]), 2*(Centro_0[2]-C[2])}
    };

    float Esfera(float P1[3], float P2[3]){

      float d = pow((P1[0]-P2[0]),2)+pow((P1[1]-P2[1]),2)+pow((P1[2]-P2[2]),2) - pow(1.5*delta_z, 2);

      return d;
    }
    //variáveis de simplificação das contas:
    float alpha = (Jacobiano[0][0] - (Jacobiano[0][2]*Jacobiano[1][0])/Jacobiano[1][2] );
    float beta = (Jacobiano[0][1] - (Jacobiano[0][2]*Jacobiano[1][1])/Jacobiano[1][2] );
    float gamma = (Jacobiano[1][0] - (Jacobiano[1][2]*Jacobiano[2][0])/Jacobiano[2][2] );
    float delta = (Jacobiano[1][1] - (Jacobiano[1][2]*Jacobiano[2][1])/Jacobiano[2][2] );


    //determinando ponto central da espera que engloba os 3 vértices A, B e C do triângulo:
    Centro[0] = ((Jacobiano[0][2]/Jacobiano[1][2])*Esfera(Centro_0[], B[]) - Esfera(Centro_0[], A[]))*(beta/gamma)/(alpha - gamma*beta/delta) + Centro_0[0];

    Centro[1] = (((Jacobiano[1][2]/Jacobiano[2][2])*Esfera(Centro_0[], C[]) - Esfera(Centro_0[], B[]))/delta - (Centro[0] - Centro_0[0])*gamma;

    Centro[2] = (Esfera(Centro_0[], C[]) - Jacobiano[2][0]*(Centro[0] - Centro_0[0]) - Jacobiano[2][1]*(Centro[1] - Centro_0[1]))/Jacobiano[2][2];

    float Raio = Esfera(Centro[], A[]);
  };


} /* del */
