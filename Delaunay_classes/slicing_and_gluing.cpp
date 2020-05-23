#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <time.h>

/*
#include "obter_catalogo_de_vizinhancas_vizinhos.cpp"
#include "Centro_Esfera_Aprox.cpp"
#include "Triangle_Building.cpp"
#include "triangle_recording.cpp"
#include "Convex_Hull.cpp"
*/



int main ()
{
  //tomando dimensões do sólido para efetuar fatiamento:
  // URL fonte desta forma de leitura de arquivo - https://stackoverflow.com/a/11168756/5382576
	float x, y, z;
  float x_min, x_max, y_min, y_max, z_min, z_max;

  FILE *file;
	file = fopen( parafuso_teste, "r" );

	int currentLine = 0;
	int lineIterator;
	do {
		currentLine++;
		lineIterator = fscanf( file, "%E%E%E \n", &x, &y, &z );
		if(x<x_min)
        {
            x_min = x;
        }
        if(x>x_max)
        {
            x_max = x;
        }
        if(y<y_min)
        {
            y_min = y;
        }
        if(y>y_max)
        {
            y_max = y;
        }
        if(z<z_min)
        {
            z_min = z;
        }
        if(z>z_max)
        {
            z_max = z;
        }


	} while ( lineIterator != EOF );

    std::cout<<"Dimensões do sólido: \n";

    std::cout<<"x máximo: "<< x_max <<"x mínimo: "<< x_min << '\n';
    std::cout<<"y máximo: "<< y_max <<"y mínimo: "<< y_min << '\n';
    std::cout<<"z máximo: "<< z_max <<"z mínimo: "<< z_min << '\n';

    std::cout<<"Quantidade total de pontos: "<< currentLine << '\n';

    //aqui precisamos definir quantos pontos o programa deve pegar por vez. 200 pontos? ----->

    long number_of_chart = currentLine/200;
    std::cout << "Total de cartas:" << number_of_chart <<'\n';
    float chart_depth = (z_max - z_min)/number_of_chart; //futuramente considerar fatiamento ao longo de outros eixos de acordo com as proporções do sólido
    std::cout << "Espessura da carta ao longo de z:" << chart_depth << '\n';
    unsigned long int chart_index = 0;

    std::vector<del::Chart> Atlas;
    currentLine = 0;
    do
    {
      lineIterator = fscanf( file, "%E%E%E \n", &x, &y, &z );
      for (chart_index = 0; chart_index < number_of_chart; chart_index++)
      {
        if (z<=(z_max - chart_index*chart_depth) && z<(z_max - (chart_index + 1)*chart_depth))
        {
            Atlas[chart_index].Points.push_back( {x, y, z} );
        }
      }

      currentLine++;
    } while ( lineIterator != EOF );



}


    /*
    class gluing
    {
    private:

    public:
        gluing();
        ~gluing();


        //varrer obter_catalogo_de_vizinhancas de vizinhanças e apagar todas com exceção daquelas que tiverem pontos do convex hull:
        for (size_t VIZ = 0; VIZ < obter_catalogo_de_vizinhancas.size(); VIZ++)
        {
            for (size_t Convex_Hull_index = 0; Convex_Hull_index < del::Convex_Hull.edge_collection.size(); Convex_Hull_index++)
            {
                if ()// se ponto do convex hull != primeiro ponto da vizinhança
                {
                   obter_catalogo_de_vizinhancas.erase(VIZ); //apaga vizinhança do catálogo
                }
            }

        }
        //fazer update das vizinhanças dos pontos do convex hull na nova região
        //colocar 'FALSE' em 'bool really_a_Convex_Hull_member' de todos os edges que tiverem pontos cujas vizinhanças sofreram atualização
        //monta todas as outras vizinhanças de pontos na nova região
        //vizinhanças que receberem novos pontos vizinhos (isto é, que sofreram atualização) devem ser ponto de partida para triangulação da região

    };//end of class gluing

 */
