#include <iostream>
#include <cmath>
#include "./Centro_Esfera_Aprox.hpp"

  del::Center_Sphere::Center_Sphere (){}; //constructor
  del::Center_Sphere::~Center_Sphere (){}; //destructor

  del::Point del::Center_Sphere::Find (del::Point A, del::Point B, del::Point C)
  {

    del::Point Centro;
    float Centro_0[3], F[6];
    float Jacobiano [6][6];
    float Raio, Raio_0, Alpha, Beta, Alpha_0, Beta_0;

    //chute de ordem zero para o centro da esfera (média das coordenadas dos vértices) :
    for (size_t i = 0; i < 3; i++) {
        Centro_0[i] = (A.p[i] + B.p[i] + C.p[i])/3;
    }

    //escolhemos o Ponto A para medir a distância até o chute Centro_0 e tomá-la como chute para o Raio:
    Raio_0 = sqrt( pow((A.p[0]-Centro_0[0]),2) + pow((A.p[1]-Centro_0[1]),2) + pow((A.p[2]-Centro_0[2]),2) );


    //montando Jacobiano:
    Jacobiano[0][0] = 2*(Centro_0[0]-A.p[0]);
    Jacobiano[0][1] = 2*(Centro_0[1]-A.p[1]);
    Jacobiano[0][2] = 2*(Centro_0[2]-A.p[2]);
    Jacobiano[0][3] = -2*(Raio_0);
    Jacobiano[0][4] = 0;
    Jacobiano[0][5] = 0;

    Jacobiano[1][0] = 2*(Centro_0[0]-B.p[0]);
    Jacobiano[1][1] = 2*(Centro_0[1]-B.p[1]);
    Jacobiano[1][2] = 2*(Centro_0[2]-B.p[2]);
    Jacobiano[1][3] = -2*(Raio_0);
    Jacobiano[1][4] = 0;
    Jacobiano[1][5] = 0;

    Jacobiano[2][0] = 2*(Centro_0[0]-C.p[0]);
    Jacobiano[2][1] = 2*(Centro_0[1]-C.p[1]);
    Jacobiano[2][2] = 2*(Centro_0[2]-C.p[2]);
    Jacobiano[2][3] = -2*(Raio_0);
    Jacobiano[2][4] = 0;
    Jacobiano[2][5] = 0;

    Jacobiano[3][0] = 1;
    Jacobiano[3][1] = 0;
    Jacobiano[3][2] = 0;
    Jacobiano[3][3] = 0;
    Jacobiano[3][4] = A.p[0]-C.p[0];
    Jacobiano[3][5] = A.p[0]-B.p[0];

    Jacobiano[4][0] = 0;
    Jacobiano[4][1] = 1;
    Jacobiano[4][2] = 0;
    Jacobiano[4][3] = 0;
    Jacobiano[4][4] = A.p[1]-C.p[1];
    Jacobiano[4][5] = A.p[1]-B.p[1];

    Jacobiano[5][0] = 0;
    Jacobiano[5][1] = 0;
    Jacobiano[5][2] = 1;
    Jacobiano[5][3] = 0;
    Jacobiano[5][4] = A.p[2]-C.p[2];
    Jacobiano[5][5] = A.p[2]-B.p[2];

    //tornando a matriz triangular:
    for (size_t t = 5; t > 0; t--)
    {
      for (size_t i = 0; i < t; i++)
      {
        for (size_t j = 0; j < t+1; j++)
        {
          F[i] = F[i]*Jacobiano[i+1][i+1] - F[i+1]*Jacobiano[i][i+1];
          Jacobiano[i][j] = Jacobiano[i][j]*Jacobiano[i+1][i+1] - Jacobiano[i+1][j]*Jacobiano[i][i+1];
        }
      }
    }

    Centro.p[0] = F[0]/Jacobiano[0][0] + Centro_0[0];

    Centro.p[1] = (F[1] - Jacobiano[1][0]*(Centro.p[0]-Centro_0[0]))/Jacobiano[1][1] + Centro_0[1];

    Centro.p[2] = (F[2] - Jacobiano[2][0]*(Centro.p[0]-Centro_0[0]) - Jacobiano[2][1]*(Centro.p[1]-Centro_0[1]))/Jacobiano[2][2] + Centro_0[2];

    return Centro;

  }//fim do método Find
