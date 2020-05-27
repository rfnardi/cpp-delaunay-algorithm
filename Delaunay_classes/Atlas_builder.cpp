#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
//#include <bits/stdc++.h>




int main (int argc, char* argv[40])
{
  //tomando dimensões do sólido para efetuar fatiamento:
	float x, y, z;
  float x_min, x_max, y_min, y_max, z_min, z_max;
  int* ppchart;// = new long;
  FILE *file;
  char filename[20]; // = new char; //= new char[20];
	//char file_name[20]; // WORKING OVER HERE!!!!!!

  void* ptr;

  if (argc==1)
  {
    std::cout << "Insira nome do arquivo de pontos a ser particionado." << '\n';
		//std::cin >> *filename;
		scanf("%19s", filename);
		//filename = (char*)(&file_name);
		//filename =(file_name);//(char*)
    //ptr = filename; //ponteiro ptr armazena o endereço de memória da variável filename
    std::cout << "Insira o número médio de pontos por região." << '\n';
		//printf("Insira o número médio de pontos por região.\n");
		scanf("%d", ppchart);
    //std::cin >> *ppchart;
		//file = fopen(file_name, "r" );
  }
  else if (argc == 2)
  {
		//ptr =(void*)argv[1];
		sscanf(argv[1],"%s", filename);
    //filename = (char[20])(*argv[1]);
		//sscanf(argv[1], "%c", filename);
    std::cout << "Insira o número médio de pontos por região." << '\n';
		scanf("%d", ppchart); //experimentando com scanf
		//std::cin >> *ppchart;                     //bugando aqui!!!
		//file = fopen(filename, "r" );
  }
  else if (argc == 3)
  {
    //filename = (char[20])(*argv[1]);
		sscanf(argv[1],"%s", filename);
		//sscanf(argv[1], "%c", filename);
    //ptr = argv[2];
    sscanf(argv[2],"%d", ppchart); //converte o terceiro parâmetro de entrada de char para decimal
		//file = fopen(filename, "r" );
  }
  else if (argc>3)
  {
    std::cout << "Muitos argumentos inseridos." << '\n';
    std::cout << "Sintaxe:" << '\n';
    std::cout << "atlas-composition" << "[nome do arquivo]" << "[numero médio de pontos por carta]" << '\n';
    exit (EXIT_FAILURE);
  }

	int Points_per_Chart = *ppchart;

	file = fopen(filename, "r" );

	unsigned long Total_de_Pontos;
	unsigned long currentLine;
	unsigned long lineIterator;

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

    int number_of_charts = currentLine/(Points_per_Chart);
    std::cout << "Total de cartas: " << number_of_charts <<'\n';
    float chart_depth = (z_max - z_min)/number_of_charts; //futuramente considerar fatiamento ao longo de outros eixos de acordo com as proporções do sólido
    std::cout << "Espessura da carta ao longo de z: " << chart_depth << '\n';

		//float* Atlas[number_of_charts][Points_per_Chart][3] = new float[number_of_charts][Points_per_Chart][3];
		float*** Atlas = (float***) malloc (sizeof(float)*number_of_charts*Points_per_Chart*3 + 20);
		int Index_Vector[number_of_charts];
		for (size_t i = 0; i < number_of_charts; i++) {
			Index_Vector[i]=0;
		}

		fclose(file);
		file = freopen(filename, "r", stdin);


		do
		{
			lineIterator = fscanf( file, "%E%E%E \n", &x, &y, &z );
			for (size_t chart_index = 0; chart_index < number_of_charts; chart_index++)
			{
				if (z<=(z_max - chart_index*chart_depth) && z>(z_max - (chart_index + 1)*chart_depth))
				{
					if (Index_Vector[chart_index]<Points_per_Chart)
					{
						Atlas[chart_index][Index_Vector[chart_index]][0] = x;
						Atlas[chart_index][Index_Vector[chart_index]][1] = y;
						Atlas[chart_index][Index_Vector[chart_index]][2] = z;
						Index_Vector[chart_index]++; // = Index_Vector[chart_index] + 1;
					}
				}
			}
			currentLine++;
		} while ( lineIterator != EOF );

    std::cout << "Particionamento dos pontos concluído com sucesso." << '\n';

    for (size_t i = 0; i < number_of_charts; i++)
    {
      std::cout << "Quantidade de pontos na carta " << i << ": "<< Index_Vector[i] <<'\n';
			/*
      std::cout << "Pontos da carta " << i << ":" << '\n';
      for (size_t j = 0; j < Atlas[i].Points.size(); j++)
      {
        std::cout << "x=" << Atlas[i].Points[j].p[0] << "; y=" << Atlas[i].Points[j].p[1] <<"; z=" << Atlas[i].Points[j].p[2] <<'\n';
      }
			*/
    }
//delete[] Atlas;
for (size_t i = 0; i < number_of_charts; i++)
{
	for (size_t j = 0; j < Index_Vector[i]; j++)
	{
		for (size_t k = 0; k < 3; k++) {
			free(&Atlas[i][j][k]);
		}
	}
}

fclose(file);

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
