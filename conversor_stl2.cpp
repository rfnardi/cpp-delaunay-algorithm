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
              
        //inicia convex_hull
        del::convex_hull convex_hull_obj;

        //constrói primeiros edges a partir do T_0 e os armazena no convex_hull_obj
        del::edge AB;
        AB.first_point = Module_0.Triangle.A;
        AB.second_point = Module_0.Triangle.B;
        convex_hull_obj.push_back(AB);

        del::edge BC;
        BC.first_point = Module_0.Triangle.B;
        BC.second_point = Module_0.Triangle.C;
        convex_hull_obj.push_back(BC);

        del::edge CA;
        CA.first_point = Module_0.Triangle.C;
        CA.second_point = Module_0.Triangle.A;
        convex_hull_obj.push_back(CA);

        del::stl_module New_Module;
        del::triangle_building Build; 
        del::triangle_Delaunay New_Triangle;
        del::point New_Normal;
        bool not_found;
        del::edge New_Edge_1;
        del::edge New_Edge_2;

        del::point Origem;
        Origem.p[0]=0;
        Origem.p[1]=0;
        Origem.p[2]=0;

        while (/* convex_hull still have 'bool really_a_convex_hull_member = false' edges*/) 
        {
          /*varre convex_hull testando really_a_convex_hull_member para cada edge*/
          del::edge working_edge = convex_hull_obj[i];

          New_Triangle = Build.edge_based_triangle_building_obj (working_edge);
          if (New_Triangle.A == Origem && New_Triangle.B == Origem &&New_Triangle.C == Origem)
          {
              working_edge.really_a_convex_hull_member = true;
          }
          if (working_edge.really_a_convex_hull_member=false)
          {
              
              //extraindo os dois edges do New_Triangle:
              New_Edge_1.first_point = ;
              New_Edge_1.second_point = ;           //to be done!!!!!!!!
              New_Edge_2.first_point = ;
              New_Edge_2.second_point = ;

              /*se achou triangulo, então deve apagar do convex_hull 
              o edge que deu base para sua construção 
              e inserir os outros 2 edges do New_Triangle no convex_hull: */
              convex_hull.erase(i);
              convex_hull.insert(i,New_Edge_2);
              convex_hull.insert(i,New_Edge_1);

              New_Triangle.same_curl(/* triangulo já listado em Triangles_with_normals que possui working_edge como um de seus lados*/);
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
          }
          
          i++;
          if (i==convex_hull.size())
          {
            i=0;
          }
          
          
             

        }//end while: 
        

        //leia a segunda faixa de dados e adicione os pontos da borda superior ao conjunto

        //repita até computar todas as faixas de dados

  }
