#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>

#include <time.h>

#include <vector>
#include <fstream>
#include <bits/stdc++.h>

#include "Delaunay_classes/Vizinhanca.cpp"

long timeBetween( long before, long after ) {
	return ( after - before ) * 1000 / CLOCKS_PER_SEC;
}

int main( int argc, char* argv[] ) {
	time_t t[ 2 ];
	char* filename; // char* instead string because of fopen use bellow
	if ( argc > 3 ) {
		std::cout << "Muitos argumentos inseridos." << std::endl;
		std::cout << "Conversor STL aceita apenas dois parâmetros opcionais. Sintaxe:" << std::endl;
		std::cout << "COMMANDO [nome do arquivo] [parametro de varredura]" << std::endl;
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

	t[ 0 ] = clock();
	FILE *file;
	file = fopen( filename, "r" );
	if ( file == NULL ) {
		std::cout << "Arquivo não pode ser aberto: Não existe ou está sendo editado por outro programa." << std::endl;
		std::cout << "Conversor STL encerra sua execução retornando erro 1." << std::endl;
		exit( EXIT_FAILURE );
	}
	// Assumir apenas vetores 3D
	// URL fonte desta forma de leitura de arquivo - https://stackoverflow.com/a/11168756/5382576
	float x, y, z;
	std::vector<std::vector<float>> pontos;
	int currentLine = 0;
	int lineIterator;
	do {
		currentLine++;
		lineIterator = fscanf( file, "%E%E%E \n", &x, &y, &z );
		pontos.push_back( { x, y, z } );
	} while ( lineIterator != EOF );
	// CONTAGEM DE PONTOS DO BLOCO DE DADOS:
	std::cout << std::endl;
	std::cout << "Total de linhas no arquivo de bloco de dados: " << currentLine << std::endl;
	std::cout << "Total de pontos armazenados em memória: " << pontos.size() << std::endl;
	// encerra as operações com o arquivo
	// esquecer esta parte pode proibir de outra rotina usar o arquivo (até mesmo do proprio sistema!)
	fclose( file );
	t[ 1 ] = clock();
	std::cout << std::endl << "Operação de leitura do arquivo realizada em " << timeBetween( t[ 1 ], t[ 2 ] ) << " ms" << std::endl << std::endl;


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

	// catalogo de pontos inicia aqui
	del::Vizinhanca vizinhanca( pontos );
	vizinhanca.ativar_debug();
	float radius =  1.5 * delta_z;
	vizinhanca.definir_raio( radius );

	t[ 0 ] = clock();
	std::vector<std::vector<std::vector<float>>> neighboorhoodsBook = vizinhanca.obter_catalogo_de_vizinhancas();
	t[ 1 ] = clock();
	std::cout << std::endl << "Operação de catalogação das vizinhanças realizada em " << timeBetween( t[ 0 ], t[ 1 ] ) << " ms" << std::endl << std::endl;


	return EXIT_SUCCESS;
	/*

	//montando primeira aresta:
	std::cout << "Primeira aresta encontrada:" << "(" x[0] << "," << y[0] << "," << z[0] << ")" << "----"
																							<< "(" x[I_min] << "," << y[I_min] << "," << z[I_min] << ")"  std::endl;
	del::Vizinhanca vizinhanca( pontos );
	vizinhanca.definir_raio( 1.5 * delta_z );
	std::vector<std::vector<std::vector<float>>> catalogo = vizinhanca.obter_catalogo_de_vizinhancas();

	//montando triangulação (Critério de Delaunay):

	//medindo as distâncias d(P_i,P_j) entre todos os ptos:

	for ( i = 0; i < n; i++) {
		for (long j = 0; j < count; j++) {
			d = sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)+pow(z[i]-z[j],2));
			if (d<delta_z*1.5) {
				construct 
			}
		}

	}
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
