#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <cstring>
//#include <bits/stdc++.h>

int sum_sizes(int I, int* index_vec_ptr)
{
	int sum;
	sum = 0;
	for (size_t i = I; i > 0; i--)
	{
		sum = sum + *(index_vec_ptr + sizeof(int)*I);
	}
	return sum;
}


int main (int argc, char* argv[40])
{

  int* ppchart;
  FILE *file;
  char* filename;

  if (argc==1)
  {
    std::cout << "Insira nome do arquivo de pontos a ser particionado." << '\n';
		scanf("%19s", filename);
    std::cout << "Insira o número médio de pontos por região." << '\n';
		scanf("%d", ppchart);

  }
  else if (argc == 2)
  {
		sscanf(argv[1],"%s", filename);
    std::cout << "Insira o número médio de pontos por região." << '\n';
		scanf("%d", ppchart);

  }
  else if (argc == 3)
  {
		sscanf(argv[1],"%s", filename);
    sscanf(argv[2],"%d", ppchart); //converte o terceiro parâmetro de entrada de char para decimal
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

	//tomando dimensões do sólido para efetuar fatiamento:
  float x_min, x_max, y_min, y_max, z_min, z_max;

	currentLine =0;
		{
			float x, y, z;
			x =0.0;
			y =0.0;
			z =0.0;

			do
		  {
				currentLine++;
				lineIterator = fscanf( file, "%E%E%E \n", &x, &y, &z );

				if (currentLine ==1 )
				{
					x_min = x;
					x_max = x;
					y_min = y;
					y_max = y;
					z_min = z;
					z_max = z;
				}

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
		}
    std::cout<<"Dimensões do sólido: \n";

    std::cout<<"x máximo: "<< x_max <<" ; x mínimo: "<< x_min << '\n';
    std::cout<<"y máximo: "<< y_max <<" ; y mínimo: "<< y_min << '\n';
    std::cout<<"z máximo: "<< z_max <<" ; z mínimo: "<< z_min << '\n';

		Total_de_Pontos = currentLine;

    std::cout<<"Quantidade total de pontos: "<< Total_de_Pontos << '\n';

    int number_of_charts;
		number_of_charts = (int) (((float)Total_de_Pontos) /((float)Points_per_Chart));
		number_of_charts++;
    std::cout << "Total de cartas: " << number_of_charts <<'\n';
    float chart_depth = (z_max - z_min)/ ((float) number_of_charts); //futuramente considerar fatiamento ao longo de outros eixos de acordo com as proporções do sólido
    std::cout << "Espessura da carta ao longo de z: " << chart_depth << '\n';

		float* x = (float*) malloc(sizeof(float)*Total_de_Pontos);
		float* y = (float*) malloc(sizeof(float)*Total_de_Pontos);
		float* z = (float*) malloc(sizeof(float)*Total_de_Pontos);

		//fclose(file);
		//file = fopen(filename, "r"); //, stdin);
		rewind(file);

			for (size_t i = 0; i < Total_de_Pontos; i++)
			{
				fscanf( file, "%E%E%E \n", x+i, y+i, z+i );
			}

		fclose(file);

		/*
		//retornando pontos no console de bouas
		for (size_t i = 0; i < (int) ((float) Total_de_Pontos)/4; i++)
		{
			std::cout << "x = " << x[i] << " , y = " << y[i] << " , z = " << z[i] <<'\n';
		}
		*/

		std::cout << "Cópia dos pontos concluída com sucesso." << '\n';

		float* Atlas = (float*) malloc (sizeof(float)*number_of_charts*Points_per_Chart*3);

		int Index_Vector[number_of_charts];
		//char* Oversized_Charts = (char*) malloc (number_of_charts*sizeof(char));
		for (size_t i = 0; i < number_of_charts; i++) {
			Index_Vector[i]=0;
		}

		std::cout << "Criação de conteineres concluída com sucesso." << '\n';

		for (size_t i = 0; i < Total_de_Pontos; i++)
		{
			for (size_t chart_index = 0; chart_index < number_of_charts; chart_index++)
			{
				if (z[i]<=(z_max - chart_index*chart_depth) && z[i]>(z_max - (chart_index + 1)*chart_depth) && Index_Vector[chart_index]<Points_per_Chart)
				{
						memcpy((Atlas + chart_index*Points_per_Chart*3 + 3*Index_Vector[chart_index] + 0), x+i, sizeof(float));
						memcpy((Atlas + chart_index*Points_per_Chart*3 + 3*Index_Vector[chart_index] + 1), y+i, sizeof(float));
						memcpy((Atlas + chart_index*Points_per_Chart*3 + 3*Index_Vector[chart_index] + 2), z+i, sizeof(float));

						Index_Vector[chart_index]++;
				}
				if ((chart_index == number_of_charts -1) && (z[i]<=(z_max - chart_index*chart_depth)) && z[i]>(z_max - (chart_index + 1)*chart_depth) && Index_Vector[chart_index]<Points_per_Chart)
				{
						memcpy((Atlas + chart_index*Points_per_Chart*3 + 3*Index_Vector[chart_index] + 0), x+i, sizeof(float));
						memcpy((Atlas + chart_index*Points_per_Chart*3 + 3*Index_Vector[chart_index] + 1), y+i, sizeof(float));
						memcpy((Atlas + chart_index*Points_per_Chart*3 + 3*Index_Vector[chart_index] + 2), z+i, sizeof(float));

						Index_Vector[chart_index]++;
				}
			}
		}


    std::cout << "Particionamento dos pontos concluído com sucesso." << '\n';

		//Mostrando conteúdo das cartas no console:
		int this_chart_in_particular = 0;
		bool show_points = false;
		for (size_t chart_index = 0; chart_index < number_of_charts; chart_index++)
    {
			if (show_points)
			{
				if(chart_index ==this_chart_in_particular) //mostra pontos da carta de número 'this_chart_in_particular' se show_points for true
		    {
		      std::cout << "Pontos da carta " << chart_index << ": " << '\n';
		      for (size_t j = 0; j < Index_Vector[chart_index]; j++)
		      {
		        std::cout << "x = " << *(Atlas + chart_index*Points_per_Chart*3 + 3*j + 0) <<
						" ; y = " << *(Atlas + chart_index*Points_per_Chart*3 + 3*j + 1) <<
						" ; z = " << *(Atlas + chart_index*Points_per_Chart*3 + 3*j + 2) <<'\n';
		      }
				}
			}
			std::cout << "Quantidade de pontos na carta " << chart_index << ": "<< Index_Vector[chart_index] << " ;    Dimensões:  z max = " << (z_max - chart_index*chart_depth) << " , z min = " << (z_max - (chart_index + 1)*chart_depth) << '\n';
    }

		int sum;
		sum=0;
		for (size_t i = 0; i < number_of_charts; i++) {sum = sum + Index_Vector[i];}
		std::cout << "Confirmando total de pontos: " << sum <<'\n';


		free(x);
		free(y);
		free(z);
		free(Atlas);
		//free(Oversized_Charts);


return 0;
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
