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
        
        FILE *arq;
        arq=fopen(filename, "r"); //abertura de arquivo para leitura
        

        //passando dados do arquivo para arrays:
        std::vector<float> P;                               
        long i=0;
        while (i<=n) {
          fscanf(arq, "%E%E%E \n", &P[0], &P[1], &P[2]);
          pontos.push_back(P);
          i++;
        }
        
        //
        std::cout << "Insira o valor do parâmetro de resolução de leitura." << '\n';
        float delta_z;
        std::cin >> delta_z;

        
        // catalogo de pontos inicia aqui
        std::cout<<"Iniciando Catálogo de vizinhanças."<<'\n';
        del::catalogo_vizinhos catalogo( pontos );
        catalogo.define_raio_vizinhanca( 1.5 * delta_z );

        // Inicia algum loop nos pontos do catalogo em busca de vizinhanças

        //Inicia triangulação
        std::cout<<"Iniciando triangulação."<<'\n';

        std::vector< del::stl_module> Triangulation_with_normals; //Armazena todos os triangulos de Delaunay e suas respectivas normais

        del::triangle_building triangle_building_obj;

        del::point A;

        A.p[0] = catalogo[0][0][0];
        A.p[1] = catalogo[0][0][1];
        A.p[2] = catalogo[0][0][2];

        triangle_Delaunay T0 = triangle_building_obj.point_based_triangle_building(A);

        //orientando corretamente para cima a normal do primeiro triangulo:
        if (T0.Normal.p[2]<0)
        {
            del::T0.swap();
        }
        
        del::stl_module Module1;
        Module1.Normal = T0.Normal;
        Module1.Triangle = T0;

        //guardando primeiro módulo do arquivo stl:
        Triangulation_with_normals.push_back(Module1);
        
        while (/* Catalogo is not empty */)
        {
          /*pega último triangulo incluído em "Triangulation_w_normals" --> */
          triangle_Delaunay T_last = Triangulation_with_normals[Triangulation_with_normals.size()-1].Triangle;
            /* pega aresta por aresta deste triangulo -->*/
                      
          del::stl_module New_Module;
          del::triangle_building Build; 
          del::triangle_Delaunay New_Triangle;
          del::point New_Normal;
          New_triangle = Build.edge_based_triangle_building_obj (T_last.A, T_last.B);
          if (/* triangulo encontrado não é trivial e ainda não consta no Triangles_with_normals*/)
          {
            New_Triangle.same_curl(T_last);
            New_NOrmal=New_Triangle.Normal()
            Triangulation_with_normals.push_back(New_Triangle);
          }

          New_triangle = Build.edge_based_triangle_building_obj (T_last.A, T_last.C);
          if (/* triangulo encontrado não é trivial e ainda não consta no Triangles_with_normals*/)
          {
            Triangulation_with_normals.push_back(New_Triangle);
          }
          
          New_triangle = Build.edge_based_triangle_building_obj (T_last.B, T_last.C);
          if (/* triangulo encontrado não é trivial e ainda não consta no Triangles_with_normals*/)
          {
            Triangulation_with_normals.push_back(New_Triangle);
          }
            /*procura ponto no catalogo que seja vizinho comum dos dois pontos de cada aresta -->
            monta triangulo com este ponto e testa a validade do critério de Delaunay*/
             

        }
        

        


        
        //proceder com ordenação dos pontos (seguindo regra da mão direita)  <--- no arquivo principal
        //determinar vetor normal (produto vetorial normalizado)             <--- no arquivo principal

        //montando triangulação (Critério de Delaunay):

        
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
