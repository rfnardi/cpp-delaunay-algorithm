#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>


int main(){

        std::string filename; // cria objeto da classe string para armazenar string com o nome do arquivo de dados

        std::cout << "Digite o nome do arquivo a ser triangulado." << '\n';
        std::cin >> filename;
        std::cout << "Nome do arquivo inserido:" << filename << ''\n';


        FILE *arq;
        arq = fopen(filename, "rt"); //abertura de arquivo de text para leitura

        std::cout << "Insira o valor do parâmetro de resolução de leitura." << '\n';
        std::cin >> delta_z;

        //CONTAGEM DE PONTOS DO BLOCO DE DADOS:
        int n=1;
        do{
          fscanf(arq, "%E%E%E \n", &bigX, &bigY, &bigZ);
          std::cout << "\r" <<"Número de pontos localizados no bloco de dados:" << n;
          n=n+1;

        } while(bigZ >= 0 && bigZ < delta_z);

        std::cout << "Total de pontos do bloco de dados:" << n << '\n';

        //passando dados do arquivo para arrays:
        float x[n], y[n], z[n];                                //is it possible???
        int i=0;
        while (i<=n) {
          fscanf(arq, "%E%E%E \n", &x[i], &y[i], &z[i]);
          i++;
        }


        //encontrando ponto mais próximo ao primeiro ponto da lista copiada:
        float d, d_min, I_min;
        d_min = 100;
        for (i = 0; i < n; i++) {
          d = sqrt(pow(x[0]-x[i],2)+pow(y[0]-y[i],2)+pow(z[0]-z[i],2));
          if (d<d_min) {
            d_min=d;
            I_min=i;
          }

        //montando primeira aresta:
        std::cout << "Primeira aresta encontrada:" << "(" x[0] << "," << y[0] << "," << z[0] << ")" << "----"
                                                   << "(" x[I_min] << "," << y[I_min] << "," << z[I_min] << ")"  '\n';

        //montando triangulação (Critério de Delaunay):

              //medir as distâncias d(P_i,P_j) entre todos os ptos
              /*criar catálogo de vizinhos (dizer para cada ponto, quem são seus vizinhos
                  (ptos cuja distância é menor do que 1.5*delta_z)) */
              //encontrar ciclo de 4 vizinhos
                  //qual é o Critério para determinar se 4 pontos formam um ciclo de vizinhos?
                        //----> não há nenhum ponto interno ao ciclo
              //aplicar Critério de Delaunay
              //determinar convex hull (borda)



        //leia a segunda faixa de dados e adicione os pontos da borda superior ao conjunto

        //repita até computar todas as faixas de dados

  }
