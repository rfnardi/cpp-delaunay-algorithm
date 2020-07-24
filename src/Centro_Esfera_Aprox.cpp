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
        Centro_0[0] = (A.x + B.x + C.x)/3;
        Centro_0[1] = (A.y + B.y + C.y)/3;
        Centro_0[2] = (A.z + B.z + C.z)/3;

    //escolhemos o Ponto A para medir a distância até o chute Centro_0 e tomá-la como chute para o Raio:
    Raio_0 = sqrt( pow((A.x-Centro_0[0]),2) + pow((A.y-Centro_0[1]),2) + pow((A.z-Centro_0[2]),2) );


    //montando Jacobiano:
    Jacobiano[0][0] = 2*(Centro_0[0]-A.x);
    Jacobiano[0][1] = 2*(Centro_0[1]-A.y);
    Jacobiano[0][2] = 2*(Centro_0[2]-A.z);
    Jacobiano[0][3] = -2*(Raio_0);
    Jacobiano[0][4] = 0;
    Jacobiano[0][5] = 0;

    Jacobiano[1][0] = 2*(Centro_0[0]-B.x);
    Jacobiano[1][1] = 2*(Centro_0[1]-B.y);
    Jacobiano[1][2] = 2*(Centro_0[2]-B.z);
    Jacobiano[1][3] = -2*(Raio_0);
    Jacobiano[1][4] = 0;
    Jacobiano[1][5] = 0;

    Jacobiano[2][0] = 2*(Centro_0[0]-C.x);
    Jacobiano[2][1] = 2*(Centro_0[1]-C.y);
    Jacobiano[2][2] = 2*(Centro_0[2]-C.z);
    Jacobiano[2][3] = -2*(Raio_0);
    Jacobiano[2][4] = 0;
    Jacobiano[2][5] = 0;

    Jacobiano[3][0] = 1;
    Jacobiano[3][1] = 0;
    Jacobiano[3][2] = 0;
    Jacobiano[3][3] = 0;
    Jacobiano[3][4] = A.x-C.x;
    Jacobiano[3][5] = A.x-B.x;

    Jacobiano[4][0] = 0;
    Jacobiano[4][1] = 1;
    Jacobiano[4][2] = 0;
    Jacobiano[4][3] = 0;
    Jacobiano[4][4] = A.y-C.y;
    Jacobiano[4][5] = A.y-B.y;

    Jacobiano[5][0] = 0;
    Jacobiano[5][1] = 0;
    Jacobiano[5][2] = 1;
    Jacobiano[5][3] = 0;
    Jacobiano[5][4] = A.z-C.z;
    Jacobiano[5][5] = A.z-B.z;

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

    Centro.x = F[0]/Jacobiano[0][0] + Centro_0[0];

    Centro.y = (F[1] - Jacobiano[1][0]*(Centro.x-Centro_0[0]))/Jacobiano[1][1] + Centro_0[1];

    Centro.z = (F[2] - Jacobiano[2][0]*(Centro.x-Centro_0[0]) - Jacobiano[2][1]*(Centro.y-Centro_0[1]))/Jacobiano[2][2] + Centro_0[2];

    return Centro;

  }//fim do método Find
