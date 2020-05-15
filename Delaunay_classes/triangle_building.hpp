#ifndef TRIANGLE_BUILD
#define TRIANGLE_BUILD
#include "./triangle_recording.hpp"

namespace del {


	//classe que determina quais são os triangulos de Delaunay
	class Triangle_building
	{

	public:
		Triangle_building ();

		Triangle point_based_triangle_building (del::Point );

		unsigned long int VIZ_A, VIZ_B, VIZ_C;

		del::Point A;
		del::Point B;
		del::Point P;

		//cria objeto da classe que calcula centro da esfera que circunscreve 3 pontos
		del::Find_Centro_Esfera find_center_sphere_obj;

		del::Point Centro_Circunf_ABC; //variável para armazenar o centro da esfera que circunscreve os pontos A, B e C.
		float Raio; //variável para armazenar o raio da esfera calculada pelo método da classe Find_Centro_esfera
		bool encontrou;
		float d;
		float ABC[3][3]; //armazena os 3 pontos A, B e C : candidatos a triangulo de Delaunay


		del::Edge AB;

		del::Point P1;
		del::Point P2;
		del::Point C;

		Triangle edge_based_triangle_building (del::Edge , Triangle );

		del::Triangle T;
		del::Triangle New_triangle;
		bool encontrou_triangulo_valido, encontrou_ponto_dentro_da_esfera;

		del::Point Origem;

	}; //fim da classe "triangle building"



					//caso o triangulo seja admitido na triangulação, ENTÃO determina orientação correta dos vértices
		//faz segunda busca por triangulo de Delaunay nas vizinhanças de A e B.
			//Se encontrar segundo triangulo de Delaunay, então aresta AB é colocada no conjunto de arestas internas.
			//Se não encontrar segundo triângulo de Delaunay, então aresta é colocada no conjunto de arestas de borda.



}; /* fim do namespace del */
#endif
