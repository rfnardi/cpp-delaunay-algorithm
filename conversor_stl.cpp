#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>

#include <vector>
#include <fstream>
#include <bits/stdc++.h>

#include "Delaunay_classes/catalogo_vizinhos.cpp";

int main(){

        std::string filename; // cria objeto da classe string para armazenar string com o nome do arquivo de dados

        std::cout << "Digite o nome do arquivo a ser triangulado." << '\n';
        std::cin >> filename;
        std::cout << "Nome do arquivo inserido:" << filename << '\n';

        /* Another way */
        std::ifstream inFile;
        // Uma linha de arquivo é identificada pelo caracter '\n' (conhecido como quebra de linha)
        // Se eu definir que a quebra de linha é agora o carater 'x', então "texto escrito axim" teria as linhas
        // te
        // to escrito a
        // im
        // portanto pensei que line é a linha do arquivo e coord é a linha da linha do arquivo
        std::string line;
        std::string coord;
        std::vector<float> ponto;
        std::vector<std::vector<float>> pontos;
        int num_linhas = 0;
        inFile.open( filename );
        if ( ! inFile ) {
          std::cout << "Arquivo não existente ou está sendo editado por outro programa." << std::endl;
          exit( 1 );
        }
        // ATENÇÃO! Em C++ "i" é um string e 'i' é um char.
        // "isto é permitido" é string válida.
        // 'isto não é permitido' não é um char!
        
        //passando dados do arquivo para arrays:
        while ( std::getline( inFile, line, '\n' ) ) {
          num_linhas += 1;
          while ( std::getline( line, coord, ' ' ) ) {
            ponto.push_back( std::stof( coord ) );
          }
          pontos.push_back( ponto );
          ponto.clear();
        }

        //
        //
        std::cout << "Insira o valor do parâmetro de resolução de leitura." << '\n';
        float delta_z;
        std::cin >> delta_z;

        //CONTAGEM DE PONTOS DO BLOCO DE DADOS:
        std::cout << "Total de pontos (num_linhas) do bloco de dados:" << num_linhas << std::endl;

        // catalogo de pontos inicia aqui
        del::catalogo_vizinhos catalogo( pontos );
        catalogo.define_raio_vizinhanca( 1.5 * delta_z );

        // Inicia algum loop nos pontos do catalogo em busca de vizinhanças

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
