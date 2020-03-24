#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(){

        char filename[27]; // cria variável char para armazenar string com o nome do arquivo de log

        printf("Digite o nome do arquivo a ser triangulado.\n");
        scanf("%s'EOF'\n", filename);
        printf("Nome do arquivo inserido: %s \n", filename);

        FILE *arq;
        arq = fopen(filename, "rt"); //abertura de arquivo de text para leitura

        float x[100], y[100], z[100], s, bigX, bigY, bigZ;  //arrays para armazenamento do bloco de dados


        size_t n=0; //n é definido como long unsigned integer

        //CONTAGEM DE PONTOS DO ARQUIVO:
         do {
          fscanf(arq, "%E%E%E \n", &bigX, &bigY, &bigZ);
          printf("Linha: %ld \n", n);
          n=n+1;
        } while (bigX != EOF | bigY != EOF | bigZ != EOF ); // not working


        printf("Total de pontos: %ld. \n", n);

        int i=0;
        while (i<=100) {
          fscanf(arq, "%E%E%E \n", &x[i], &y[i], &z[i]);
          i++;
        }


        i=0;

        //determinando borda do grafo:
            //determinando pontos mais distantes e mais próximos do bloco de dados:
                float d=0;
                float d_max, d_min;
                int j, I_max, J_max, I_min, J_min;
                for (i = 0; i < 100; i++) {
                    for (j = 0; j < 100 && i!=j; j++) {
                      d= sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)+pow(z[i]-z[j],2));
                      if (d>d_max) {
                        d_max=d;
                        I_max=i;
                        J_max=j;
                      }
                      if (d<d_min) {
                        d_min=d;
                        I_min=i;
                        J_min=j;
                      }
                    }
                }

                printf("Os pontos mais distantes um do outro são: (%f, %f, %f) e (%f, %f, %f). \n Com uma distância de %f \n", x[I_max], y[I_max], z[I_max], x[J_max], y[J_max], z[J_max], d_max);

                printf("Os pontos mais próximos um do outro são: (%f, %f, %f) e (%f, %f, %f). \n Com uma distância de %f \n", x[I_min], y[I_min], z[I_min], x[J_min], y[J_min], z[J_min], d_min);

          //estudando distribuição de pontos via distribuição de distâncias entre pontos:




   /*


  */



        //ler a primeira faixa de dados do arquivo: 0<=z<=s ; s é o passo vertical de leitura, que deve ser pouco maior que o passo vertical de escrita
            //contar o número N de pontos dentro da faixa e criar uma matriz 3xN onde os dados do arquivo são copiados

        //medir as distâncias d(P_i,P_j) entre todos os pontos da faixa e criar associação entre pontos próximos (d<=1.3*S) dentro da faixa: criação de arestas

        //considere todos os ciclos de de 3 arestas tais que o tamanho de uma das arestas não seja maior do que 1.3 vezes o tamanho de qualquer outra aresta do ciclo

        //grave os ciclos no arquivo gerado

        //crie conjunto de pontos da borda superior

        //leia a segunda faixa de dados e adicione os pontos da borda superior ao conjunto

        //repita até computar todas as faixas de dados

  }
