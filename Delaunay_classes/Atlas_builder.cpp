#include <cmath>
#include <vector>
#include <string>
#include <iostream>
//#include <time.h>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include "./atlas.cpp"
#include "./Point.cpp"
/*
#include "obter_catalogo_de_vizinhancas_vizinhos.cpp"
#include "Centro_Esfera_Aprox.cpp"
#include "Triangle_Building.cpp"
#include "triangle_recording.cpp"
#include "Convex_Hull.cpp"
*/



int main (int argc, char* argv[])
{
  //tomando dimensões do sólido para efetuar fatiamento:
	float x, y, z;
  float x_min, x_max, y_min, y_max, z_min, z_max;
  long* ppchart;// = new long;
  FILE *file;
  char* filename; // = new char; //= new char[20];

  void* ptr;

  if (argc==1)
  {
    std::cout << "Insira nome do arquivo de pontos a ser particionado." << '\n';
		//std::cin >> *filename;
		scanf("%s", filename);
    //ptr = filename; //ponteiro ptr armazena o endereço de memória da variável filename
    std::cout << "Insira o número médio de pontos por região." << '\n';
		//printf("Insira o número médio de pontos por região.\n");
		scanf("%ld", ppchart);
    //std::cin >> *ppchart;
  }
  else if (argc == 2)
  {
		//ptr =(void*)argv[1];
    filename = argv[1];
		//sscanf(argv[1], "%c", filename);
    std::cout << "Insira o número médio de pontos por região." << '\n';
		scanf("%ld", ppchart); //experimentando com scanf
		//std::cin >> *ppchart;                     //bugando aqui!!!
  }
  else if (argc == 3)
  {
    filename = argv[1];
		//sscanf(argv[1], "%c", filename);
    //ptr = argv[2];
    sscanf(argv[2],"%ld", ppchart); //converte o terceiro parâmetro de entrada de char para decimal
  }
  else if (argc>3)
  {
    std::cout << "Muitos argumentos inseridos." << '\n';
    std::cout << "Sintaxe:" << '\n';
    std::cout << "atlas-composition" << "[nome do arquivo]" << "[numero médio de pontos por carta]" << '\n';
    exit (EXIT_FAILURE);
  }

	file = fopen(filename, "r" );

	unsigned long int Total_de_Pontos;
	unsigned long int currentLine;
	int lineIterator;

	currentLine =0;

	do
  {
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

    std::cout<<"x máximo: "<< x_max <<" x mínimo: "<< x_min << '\n';
    std::cout<<"y máximo: "<< y_max <<" y mínimo: "<< y_min << '\n';
    std::cout<<"z máximo: "<< z_max <<" z mínimo: "<< z_min << '\n';

		Total_de_Pontos = currentLine;

    std::cout<<"Quantidade total de pontos: "<< Total_de_Pontos << '\n';

    int number_of_charts = currentLine/(*ppchart);
    std::cout << "Total de cartas: " << number_of_charts <<'\n';
    float chart_depth = (z_max - z_min)/number_of_charts; //futuramente considerar fatiamento ao longo de outros eixos de acordo com as proporções do sólido
    std::cout << "Espessura da carta ao longo de z: " << chart_depth << '\n';
    int chart_index;

    std::vector<del::Chart> *Atlas = new std::vector<del::Chart>;
    del::Chart New_Chart;
    for (chart_index = 0; chart_index < number_of_charts; chart_index++)
    {
      New_Chart.Chart_index = chart_index;
      (*Atlas).push_back( New_Chart);
      std::cout << "Carta " << chart_index  << " adicionada ao atlas com sucesso"<<'\n';
    }
    std::cout << "Cartas iniciadas com sucesso." << '\n';
    std::cout << "Iniciando particionamento dos pontos" << '\n';
    currentLine = 0;
    del::Point ponto;


    file = freopen(filename, "r" , stdin); //volta o stream para o início do arquivo

    do
    {
      lineIterator = fscanf( file, "%E%E%E \n", &x, &y, &z );
      for (chart_index = 0; chart_index < number_of_charts; chart_index++)
      {
        if (z<=(z_max - chart_index*chart_depth) && z>(z_max - (chart_index + 1)*chart_depth))
        {
          ponto.p[0]= x;
          ponto.p[1]= y;
          ponto.p[2]= z;
          (*Atlas)[chart_index].Points.push_back(ponto);
        }
      }
      currentLine++;
    } while ( lineIterator != EOF );

    std::cout << "Particionamento dos pontos concluído com sucesso." << '\n';

    for (size_t i = 0; i < (*Atlas).size(); i++)
    {
      std::cout << "Quantidade de pontos na carta " << i << ": "<< (*Atlas)[i].Points.size()<<'\n';
			/*
      std::cout << "Pontos da carta " << i << ":" << '\n';
      for (size_t j = 0; j < Atlas[i].Points.size(); j++)
      {
        std::cout << "x=" << Atlas[i].Points[j].p[0] << "; y=" << Atlas[i].Points[j].p[1] <<"; z=" << Atlas[i].Points[j].p[2] <<'\n';
      }
			*/
    }
delete Atlas;
//free(ppchart);
//free(ptr);
//free(filename);
fclose(file);
//free(file);

return 1;
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
