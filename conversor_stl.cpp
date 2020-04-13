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

#include "Delaunay_classes/Vizinhanca.cpp"

int main() {

        std::string filename; // cria objeto da classe string para armazenar string com o nome do arquivo de dados

        std::cout << "Digite o nome do arquivo a ser triangulado." << '\n';
        std::cin >> filename;
        std::cout << "Nome do arquivo inserido:" << filename << '\n';

        std::fstream file ( filename );
        // se não conseguiu abrir o arquivo, retorna erro e para o programa.
        if ( ! file.is_open() ) {
          std::cout << "Arquivo não existente ou está sendo editado por outro programa." << std::endl;
          return 1;
        }
        std::string line;
        std::string coord;
        std::vector<float> ponto;
        std::vector<std::vector<float>> pontos;
        int num_linhas = 0;
        // loop para cada linha line do arquivo file
        while ( getline( file, line ) ) {
          num_linhas++;
          // loop para cada caracter n da linha line
          for ( auto n:line ) {
            if ( n != ' ' ) {
              // se não for espaço faz parte de uma coordenada
              coord += n;
            } else
            if ( n == ' ' && coord != "" ) {
              // se for espaço então acabou a coordenada
              // adiciona a coordenada ao ponto
              ponto.push_back( stof( coord ) );
              coord = "";
            }
          }
          // acabou a leitura dos caracteres n da linha line, ou seja, já se conhece o ponto com suas coordenadas
          // adiciona o ponto  a lista de pontos
          pontos.push_back( ponto );
        }
        // encerra as operações com o arquivo
        // esquecer esta parte pode proibir de outra rotina usar o arquivo (até mesmo do proprio sistema!)
        file.close();

        //
        //
        std::cout << "Insira o valor do parâmetro de resolução de leitura." << '\n';
        float delta_z;
        std::cin >> delta_z;

        //CONTAGEM DE PONTOS DO BLOCO DE DADOS:
        std::cout << "Total de pontos (num_linhas) do bloco de dados:" << num_linhas << std::endl;

        // catalogo de pontos inicia aqui
        del::Vizinhanca vizinhanca( pontos );
        vizinhanca.definir_raio( 1.5 * delta_z );
        std::vector<std::vector<std::vector<float>>> catalogo = vizinhanca.obter_catalogo_de_vizinhancas();

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
        return 0;

  }
