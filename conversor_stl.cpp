#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <time.h>
#include <array>
#include <vector>
#include <fstream>

#include <bits/stdc++.h>

#include "Delaunay_classes/Point.cpp"
#include "Delaunay_classes/Vizinhanca.cpp"
#include "Delaunay_classes/Centro_Esfera_Aprox.cpp"
#include "Delaunay_classes/triangle_building.cpp"
#include "Delaunay_classes/Triangle.cpp"
#include "Delaunay_classes/convex_hull.cpp"
#include "Delaunay_classes/stl_module.cpp"
#include "Delaunay_classes/find_z_max.cpp"
//#include "Delaunay_classes/slicing_and_gluing.cpp"




long timeBetween( long before, long after ) {
	return ( after - before ) * 1000 / CLOCKS_PER_SEC;
}

void appendToFile ( std::string fileName, std::string line ) {
	std::ofstream fout;
	std::ifstream fin;
	fin.open( fileName );
	fout.open( fileName, std::ios::app );
	if ( fin.is_open() ) {
		fout << line << std::endl;
	}
	fin.close();
	fout.close();
}

int main( int argc, char* argv[] )
{
	time_t t[ 2 ];
	char* filename; // char* instead string because of fopen use bellow
	if ( argc > 3 ) {
		std::cout << "Muitos argumentos inseridos." << std::endl;
		std::cout << "Conversor STL aceita apenas dois parâmetros opcionais." << std::endl;
		std::cout << "	Sintaxe:" << std::endl;
		std::cout << "		conversort-stl [nome do arquivo] [parametro de varredura]" << std::endl;
		exit( EXIT_FAILURE );
	}
	if ( argc >= 2 ) {
		// Utilizando arquivo inserido via linha de comando.
		filename = argv[ 1 ];
	} else {
		// Se nenhum parametro é inserido na execução, pede arquivo ao usuário.
		std::cout << "Digite o nome do arquivo a ser triangulado." << std::endl;
		std::cin >> filename;
	}
	std::cout << "Nome do arquivo inserido:" << filename << std::endl;
	std::cout << std::endl;

	FILE *file;
	file = fopen( filename, "r" );
	if ( file == NULL ) {
		std::cout << "Arquivo não pode ser aberto: Não existe ou está sendo editado por outro programa." << std::endl;
		std::cout << "Conversor STL encerra sua execução retornando erro 1." << std::endl;
		exit( EXIT_FAILURE );
	}

	// Assumir apenas vetores 3D
	// URL fonte desta forma de leitura de arquivo - https://stackoverflow.com/a/11168756/5382576
	float x, y, z, c[ 3 ];
	del::Point ponto;
	std::vector<del::Point> pontos;
	int currentLine = 0;

	t[ 0 ] = clock();
	while ( fscanf( file, "%E%E%E \n", &x, &y, &z ) != EOF ) {
		currentLine++;
		// ponto.setCoordinates( 3, { x, y, z } );
		ponto.p[ 0 ]= x;
		ponto.p[ 1 ]= y;
		ponto.p[ 2 ]= z;
		pontos.push_back( ponto );
	};
	t[ 1 ] = clock();

	fclose( file );
	//delete[] file;

	std::cout << std::endl;
	std::cout << "Total de linhas no arquivo de bloco de dados: " << currentLine << std::endl;
	std::cout << "Total de pontos armazenados em memória: " << pontos.size() << std::endl;
	std::cout << std::endl << "Operação de leitura do arquivo realizada em " << timeBetween( t[ 0 ], t[ 1 ] ) << " ms" << std::endl << std::endl;


	float delta_z;
	if ( argc == 3 ) {
		// Argumento foi inserido via comando
		delta_z = atof( argv[ 2 ] );
	} else {
		// Não foi inserido o segundo parametro no comando
		std::cout << "Insira o valor do parâmetro de resolução de leitura." << std::endl;
		std::cin >> delta_z;
	}
	std::cout << "Parâmetro de resolução de leitura: " << delta_z << std::endl;

	// obter_catalogo_de_vizinhancas de pontos inicia aqui
	// primeiro instancio a classe inserindo os pontos
	del::Vizinhanca vizinhanca( pontos );
	del::Triangle_Building triangle_Builder;
	// ativo ou desativo o debug (para leitura no console)
	vizinhanca.ativar_debug();
	//vizinhanca.desativar_debug();

	// defino o raio da vizinhança
	float radius =  1.5 * delta_z;
	vizinhanca.definir_raio( radius );

	// t[0] armazena a posição do tempo antes do processo de "catalogação"
	t[ 0 ] = clock();
	// processo de catalogação
	std::vector<std::vector<del::Point>> neighboorhoodsBook = vizinhanca.obter_catalogo_de_vizinhancas();
	triangle_Builder.Recebe_Catalogo(neighboorhoodsBook);
	// t[1] armazena o tempo final do processo
	t[ 1 ] = clock();
	appendToFile( "timer.log", std::to_string( currentLine ) + " " + std::to_string( timeBetween( t[ 0 ], t[ 1 ] ) ) + " " + std::to_string( delta_z ) );
	std::cout << std::endl << "Operação de catalogação das vizinhanças realizada em " << timeBetween( t[ 0 ], t[ 1 ] ) << " ms" << std::endl << std::endl;


	//Inicia triangulação
	std::cout << "Iniciando triangulação." << std::endl;
	std::vector< del::Stl_module> Triangulation_with_normals; //Armazena todos os triangulos de Delaunay e suas respectivas normais
	std::cout << "Vetor de armazenamento dos módulos stl criado com sucesso." << '\n';
	del::Triangle_Building Triangle_Building_obj;
	std::cout << "Instância da classe Triangle_Building criada com sucesso." << '\n';
	del::Find_Extremal_Points find_extremal_points_obj;
	std::cout << "Instância da classe Find_Extremal_Points criada com sucesso." << '\n';
	del::Point A = find_extremal_points_obj.Find_Z_Max(pontos);; //ponto mais alto do sólido (maior z)
	std::cout << "Ponto mais alto do sólido localizado com sucesso:" << '\n';
	std::cout << "X=" << A.p[0]<<'\n';
	std::cout << "Y=" << A.p[1]<<'\n';
	std::cout << "Z=" << A.p[2]<<'\n';
	del::Triangle T_0 = Triangle_Building_obj.Point_based_Triangle_Building(A);
	std::cout << "Primeiro triaângulo da triangulação determinado com sucesso:" << '\n';
	std::cout << "Ponto A:" << "X="<<T_0.A.p[0]<<"Y="<<T_0.A.p[1]<<"Z="<<T_0.A.p[2]<<'\n';
	std::cout << "Ponto B:" << "X="<<T_0.B.p[0]<<"Y="<<T_0.B.p[1]<<"Z="<<T_0.B.p[2]<<'\n';
	std::cout << "Ponto C:" << "X="<<T_0.C.p[0]<<"Y="<<T_0.C.p[1]<<"Z="<<T_0.C.p[2]<<'\n';

	del::Point first_Normal = T_0.Normal();
	std::cout << "Normal ao Primeiro triângulo determinada com sucesso:" << '\n';
	std::cout << "Normal:" << "X="<<first_Normal.p[0]<<"Y="<<first_Normal.p[1]<<"Z="<<first_Normal.p[2]<< '\n';

	//orientando corretamente para cima a normal do primeiro triangulo:
	if (first_Normal.p[2]<0)
	{
		T_0.swap();
	}
	std::cout << "Pontos do primeiro triângulo após aplicação do Swap:" << '\n';
	std::cout << "Ponto A:" << "X="<<T_0.A.p[0]<<"Y="<<T_0.A.p[1]<<"Z="<<T_0.A.p[2]<<'\n';
	std::cout << "Ponto B:" << "X="<<T_0.B.p[0]<<"Y="<<T_0.B.p[1]<<"Z="<<T_0.B.p[2]<<'\n';
	std::cout << "Ponto C:" << "X="<<T_0.C.p[0]<<"Y="<<T_0.C.p[1]<<"Z="<<T_0.C.p[2]<<'\n';
	first_Normal = T_0.Normal();
	std::cout << "Normal ao Primeiro triângulo após aplicação do Swap:" << '\n';
	std::cout << "Normal:" << "X="<<first_Normal.p[0]<<"Y="<<first_Normal.p[1]<<"Z="<<first_Normal.p[2]<< '\n';

	del::Stl_module Module_0;
	Module_0.Normal = T_0.Normal();
	Module_0.Triangle = T_0;
	std::cout << "Primeiro módulo Stl determinado com sucesso." << '\n';

	//guardando primeiro módulo do arquivo stl:
	Triangulation_with_normals.push_back(Module_0);
	std::cout << "Primeiro módulo Stl guardado em triangulation with normals com sucesso:" << '\n';
	std::cout << "Triangulo:" << '\n';
	std::cout << "Ponto A:" << "X="<<Triangulation_with_normals[0].Triangle.A.p[0]<<"Y="<<Triangulation_with_normals[0].Triangle.A.p[1]<<"Z="<<Triangulation_with_normals[0].Triangle.A.p[2]<<'\n';
	std::cout << "Ponto B:" << "X="<<Triangulation_with_normals[0].Triangle.B.p[0]<<"Y="<<Triangulation_with_normals[0].Triangle.B.p[1]<<"Z="<<Triangulation_with_normals[0].Triangle.B.p[2]<<'\n';
	std::cout << "Ponto C:" << "X="<<Triangulation_with_normals[0].Triangle.B.p[0]<<"Y="<<Triangulation_with_normals[0].Triangle.B.p[1]<<"Z="<<Triangulation_with_normals[0].Triangle.B.p[2]<<'\n';
	std::cout << "Normal:" << '\n';
	std::cout << "Normal:" << "X="<<Module_0.Normal.p[0]<<"Y="<<Module_0.Normal.p[1]<<"Z="<<Module_0.Normal.p[2]<< '\n';

	//inicia Convex_Hull
	del::Convex_Hull Convex_Hull_obj;
	std::cout << "Instância da classe Convex Hull criada com sucesso." << '\n';

	//constrói primeiros edges a partir do T_0 e os armazena no Convex_Hull_obj
	del::Edge AB;
	AB.first_Point = Module_0.Triangle.A;
	AB.second_Point = Module_0.Triangle.B;
	Convex_Hull_obj.edge_collection.push_back(AB);

	del::Edge BC;
	BC.first_Point = Module_0.Triangle.B;
	BC.second_Point = Module_0.Triangle.C;
	Convex_Hull_obj.edge_collection.push_back(BC);

	del::Edge CA;
	CA.first_Point = Module_0.Triangle.C;
	CA.second_Point = Module_0.Triangle.A;
	Convex_Hull_obj.edge_collection.push_back(CA);
	std::cout << "Primeiras 3 arestas criadas e adicionadas ao Convex Hull com sucesso:" << '\n';
	std::cout << "Aresta AB:" << '\n';
	std::cout << "Primeiro Ponto:" << "X="<<AB.first_Point.p[0]<<"Y="<<AB.first_Point.p[1]<<"Z="<<AB.first_Point.p[2]<< '\n';
	std::cout << "Primeiro Ponto:" << "X="<<AB.second_Point.p[0]<<"Y="<<AB.second_Point.p[1]<<"Z="<<AB.second_Point.p[2]<< '\n';

	std::cout << "Aresta BC:" << '\n';
	std::cout << "Primeiro Ponto:" << "X="<<BC.first_Point.p[0]<<"Y="<<BC.first_Point.p[1]<<"Z="<<BC.first_Point.p[2]<< '\n';
	std::cout << "Primeiro Ponto:" << "X="<<BC.second_Point.p[0]<<"Y="<<BC.second_Point.p[1]<<"Z="<<BC.second_Point.p[2]<< '\n';

	std::cout << "Aresta CA:" << '\n';
	std::cout << "Primeiro Ponto:" << "X="<<CA.first_Point.p[0]<<"Y="<<CA.first_Point.p[1]<<"Z="<<CA.first_Point.p[2]<< '\n';
	std::cout << "Primeiro Ponto:" << "X="<<CA.second_Point.p[0]<<"Y="<<CA.second_Point.p[1]<<"Z="<<CA.second_Point.p[2]<< '\n';

	bool Convex_Hull_test = Convex_Hull_obj.reliability();

	if (Convex_Hull_test)
	{
		std::cout << "Convex Hull iniciado com sucesso." << '\n';
	}
	else
	{
		std::cout << "Convex Hull iniciado com erro no primeiro triângulo." << '\n';
		exit( EXIT_FAILURE );
	}

	del::Stl_module New_Module;
	del::Triangle_Building Build;
	del::Triangle New_Triangle;
	del::Point New_Normal;
	bool not_found;
	del::Edge New_Edge_1;
	del::Edge New_Edge_2;

	del::Point Origem;

	long unsigned int J =0;
	// while Convex_Hull still have 'bool really_a_Convex_Hull_member = false' edges
	while (J < Convex_Hull_obj.edge_collection.size() )
	{
		// varre Convex_Hull testando really_a_Convex_Hull_member para cada edge
		del::Edge working_edge = Convex_Hull_obj.edge_collection[J];

		New_Triangle = Build.Edge_based_Triangle_Building (working_edge, T_0);
		//triângulo construído é trivial
		if (New_Triangle.A == Origem && New_Triangle.B == Origem && New_Triangle.C == Origem)
		{
			Convex_Hull_obj.edge_collection[J].really_a_Convex_Hull_member = true;
			J++; //apenas prossegue na varredura do Convex_Hull quando a aresta working_edge não dá origem a outro triangulo
			working_edge = Convex_Hull_obj.edge_collection[J];
		}
		if (Convex_Hull_obj.edge_collection[J].really_a_Convex_Hull_member = false)
		{

			//extraindo os dois edges do New_Triangle:
			New_Edge_1.first_Point = working_edge.first_Point;
			New_Edge_1.second_Point = New_Triangle.not_common_point_in_this_triangle_comparing_to_the_sharing_edge_triangle(T_0);
			New_Edge_2.first_Point = New_Triangle.not_common_point_in_this_triangle_comparing_to_the_sharing_edge_triangle(T_0);
			New_Edge_2.second_Point = working_edge.second_Point;

			// se achou triangulo, então deve apagar do Convex_Hull
			// o edge que deu base para sua construção
			// e inserir os outros 2 edges do New_Triangle no Convex_Hull:
			Convex_Hull_obj.edge_collection.erase(Convex_Hull_obj.edge_collection.begin()+J);
			Convex_Hull_obj.edge_collection.insert(Convex_Hull_obj.edge_collection.begin()+J,New_Edge_2);
			Convex_Hull_obj.edge_collection.insert(Convex_Hull_obj.edge_collection.begin()+J,New_Edge_1);

			// triangulo já listado em Triangles_with_normals que possui working_edge como um de seus lados
			New_Triangle.same_curl(T_0);
			New_Normal = New_Triangle.Normal();
			New_Module.Normal = New_Normal;
			New_Module.Triangle = New_Triangle;
			not_found = true; //marcador lógico para registrar quando o triangulo encontrado já está guardado no Triangulation_with_normals

			//varre Triangulation_with_normals em busca de um módulo igual ao New_Module:
			for (size_t i = 0; i < Triangulation_with_normals.size(); i++)
			{
				if (Triangulation_with_normals[i] == New_Module)
				{
				// descarta triangulo e o modulo e sai do loop
				not_found = false;
				break;
				}
				else if ((i==Triangulation_with_normals.size() - 1) && (not_found))
				{
				Triangulation_with_normals.push_back(New_Module);
				}
			}
			working_edge = Convex_Hull_obj.edge_collection[J];
			T_0 = New_Triangle;
		}
	} //end while:
	//leia a segunda faixa de dados e adicione os pontos da borda superior ao conjunto
	//repita até computar todas as faixas de dados


	return EXIT_SUCCESS;
	// compilação e utilização testada até esta linha
	// conteúdo abaixo não foi testado ainda!

}
