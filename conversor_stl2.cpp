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

        //Chama método da classe catalogo que monta as vizinhanças

        //Inicia triangulação
        std::cout<<"Iniciando triangulação."<<'\n';

        std::vector< del::stl_module> Triangulation_with_normals; //Armazena todos os triangulos de Delaunay e suas respectivas normais

        del::triangle_building triangle_building_obj;

        del::point A; //ponto mais alto do sólido (maior z)

        A.p[0] = catalogo[0][0][0];
        A.p[1] = catalogo[0][0][1];
        A.p[2] = catalogo[0][0][2];

        del::triangle_Delaunay T_0 = triangle_building_obj.point_based_triangle_building(A);

        //orientando corretamente para cima a normal do primeiro triangulo:
        if (T_0.Normal.p[2]<0)
        {
            del::T_0.swap();
        }
        
        del::stl_module Module_0;
        Module_0.Normal = T_0.Normal;
        Module_0.Triangle = T_0;

        //guardando primeiro módulo do arquivo stl:
        Triangulation_with_normals.push_back(Module_0);
              /*esta condição abaixo para o loop while não vai funcionar. 
              Como saber que um ponto já esgotou seus triangulos??? 
              Alternativa: construir triangulos a partir dos edges
              do convex_hull dinâmico até que todos esses edges  
              não fornecam novos triangulos. Quando isso ocorrer, o convex hull 
              é finalizado e identificado como a borda "de facto" da região*/

        //inicia convex_hull
        del::convex_hull convex_hull_obj;
        while (/* Catalogo is not empty */) 
        {
          /*pega último triangulo incluído em "Triangulation_w_normals" --> */
          triangle_Delaunay T_last = Triangulation_with_normals[Triangulation_with_normals.size()-1].Triangle;
            /* pega aresta por aresta deste triangulo -->*/
                      
          del::stl_module New_Module;
          del::triangle_building Build; 
          del::triangle_Delaunay New_Triangle;
          del::point New_Normal;
          bool not_found;

          New_triangle = Build.edge_based_triangle_building_obj (T_last.A, T_last.B);
          New_Triangle.same_curl(T_last);
          New_Normal = New_Triangle.Normal();
          New_Module.Normal = New_Normal;
          New_Module.Triangle = New_Triangle;
          not_found = true;
          //varre Triangulation_with_normals em busca de um módulo igual ao New_Module:
          for (size_t i = 0; i < Triangulation_with_normals.size(); i++)
                {
                  if (Triangulation_with_normals[i] == New_Module)
                  {
                    /* descarta triangulo e o modulo e sai do loop */
                    not_found = false;
                    break;
                  }
                  else if ((i==Triangulation_with_normals.size() - 1) && (not_found))
                  {
                    Triangulation_with_normals.push_back(New_Module);
                  }
                  
                }

          
            
             

        }//end while: catálogo está vazio <-------- não vai funcionar
        

        


        
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
