//#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <cstring>
#include <cmath>
#include "./Atlas_functions.cpp"
//#include <bits/stdc++.h>



// *********************************************************************************
int main (int argc, char* argv[40])
{

  int* ppchart = new int;
  FILE *file;
  char* filename = new char;

  if (argc==1)
  {
    std::cout << "Insira nome do arquivo de pontos a ser particionado." << '\n';
		scanf("%s", filename);
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

				if(x<x_min){x_min = x;}
        if(x>x_max){x_max = x;}
        if(y<y_min){y_min = y;}
        if(y>y_max){y_max = y;}
        if(z<z_min){z_min = z;}
        if(z>z_max){z_max = z;}

			} while ( lineIterator != EOF );
		}
		Total_de_Pontos = currentLine;
    std::cout<<"Dimensões do sólido: \n";
    std::cout<<"x máximo: "<< x_max <<" ; x mínimo: "<< x_min << '\n';
    std::cout<<"y máximo: "<< y_max <<" ; y mínimo: "<< y_min << '\n';
    std::cout<<"z máximo: "<< z_max <<" ; z mínimo: "<< z_min << '\n';


    std::cout<<"Quantidade total de pontos: "<< Total_de_Pontos << '\n';

    int number_of_charts;
		number_of_charts = (int) (((float)Total_de_Pontos) /((float)Points_per_Chart));
		number_of_charts++;
    std::cout << "Total de cartas: " << number_of_charts <<'\n';
    float chart_depth = (z_max - z_min)/ ((float) number_of_charts); //futuramente considerar fatiamento ao longo de outros eixos de acordo com as proporções do sólido
    std::cout << "Espessura da carta ao longo de z: " << chart_depth << '\n';

		//criando arrays sob medida para armazenar pontos do arquivo:
		float* x = (float*) malloc(sizeof(float)*Total_de_Pontos);
		float* y = (float*) malloc(sizeof(float)*Total_de_Pontos);
		float* z = (float*) malloc(sizeof(float)*Total_de_Pontos);


		//Armazenando pontos do arquivo em arrays sob medida:
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

		std::cout << "Cópia dos pontos concluída com sucesso." << '\n'<< '\n';

		float* Atlas = (float*) malloc (sizeof(float)*Total_de_Pontos*3);

		int Index_Vector[number_of_charts]; //conta o número de pontos em cada carta
		bool* Oversized_Charts = (bool*) malloc(sizeof(bool)*number_of_charts); //marcador lógico para as cartas cujo número de pontos excedeu o máximo admitido
																																						//deve ser usado para prosseguir com cortes da região coberta pela carta em outros planos
		//inicializando vetores Index_Vector e Oversized_Charts:
		for (size_t i = 0; i < number_of_charts; i++)
		{
			Index_Vector[i]=0;
			Oversized_Charts[i]=false;
		}

		std::cout << "Memória para as cartas alocada com sucesso." << '\n';

		//Contando os pontos de cada carta:
		for (size_t i = 0; i < Total_de_Pontos; i++)
		{
			for (size_t chart_index = 0; chart_index < number_of_charts; chart_index++)
			{
				if ( (chart_index != number_of_charts -1) && (z[i]<=(z_max - chart_index*chart_depth)) && z[i]>(z_max - (chart_index + 1)*chart_depth) )
				{
					Index_Vector[chart_index]++;
				}
				//making sure the last chart will take points at the inferior border:
				if ((chart_index == number_of_charts -1) && (z[i]<=(z_max - chart_index*chart_depth)) && z[i]>=(z_min) )
				{
					Index_Vector[chart_index]++;
				}
			}
		}

		std::cout << "Contagem de pontos em cada carta realizada com sucesso." << '\n';

		//passando o conteúdo do vetor de índices para Qtd_pts_na_Carta
		// e reinicializando-o para orientar o armazenamento dos pontos na carta:
		int Qtd_pts_na_Carta[number_of_charts];
		for (size_t i = 0; i < number_of_charts; i++)
		{
			Qtd_pts_na_Carta[i] = Index_Vector[i];
			Index_Vector[i]=0;
		}

		std::cout << "Entropia associada à distribuição dos pontos nas cartas: " << Shannon_Entropy (Qtd_pts_na_Carta, number_of_charts) <<'\n';

		// **** alocando pontos nas cartas:
		// **** O Atlas é uma coleção de matrizes (cartas), todas com 3 colunas
		// **** mas cada uma com uma quantidade de linhas diferente.
		// **** A quantidade de linhas em cada carta é guardada no array 'Qtd_pts_na_Carta';
		// **** o elemento que está na linha i e na coluna j da k-ésima carta se localiza na seguinte posição de memória:
		// **** (Atlas + 3*sum_sizes(k, Qtd_pts_na_Carta) + 3*i + j)

		for (size_t i = 0; i < Total_de_Pontos; i++)
		{
			for (size_t chart_index = 0; chart_index < number_of_charts; chart_index++)
			{
				if ( (chart_index != number_of_charts -1) && (z[i]<=(z_max - chart_index*chart_depth)) && z[i]>(z_max - (chart_index + 1)*chart_depth) )
				{
					Write_to_Atlas (Atlas , Qtd_pts_na_Carta, chart_index, Index_Vector[chart_index], 0, *(x+i));
					Write_to_Atlas (Atlas , Qtd_pts_na_Carta, chart_index, Index_Vector[chart_index], 1, *(y+i));
					Write_to_Atlas (Atlas , Qtd_pts_na_Carta, chart_index, Index_Vector[chart_index], 2, *(z+i));

					Index_Vector[chart_index]++;
				}
				//making sure the last chart will take points at the inferior border:
				if ((chart_index == number_of_charts -1) && (z[i]<=(z_max - chart_index*chart_depth)) && z[i]>=(z_min) )
				{
					Write_to_Atlas (Atlas , Qtd_pts_na_Carta, chart_index, Index_Vector[chart_index], 0, *(x+i));
					Write_to_Atlas (Atlas , Qtd_pts_na_Carta, chart_index, Index_Vector[chart_index], 1, *(y+i));
					Write_to_Atlas (Atlas , Qtd_pts_na_Carta, chart_index, Index_Vector[chart_index], 2, *(z+i));

					Index_Vector[chart_index]++;
				}
			}
		}

		std::cout << "Registro de pontos nas cartas realizado com sucesso." << '\n';

    std::cout << "Particionamento dos pontos concluído com sucesso." << '\n' << '\n';

		//Mostrando conteúdo das cartas no console:
		int this_chart_in_particular = 0;
		bool show_points = false;
		for (size_t chart_index = 0; chart_index < number_of_charts; chart_index++)
    {
			if (show_points && (chart_index ==this_chart_in_particular))//mostra pontos da carta de número 'this_chart_in_particular' se show_points for true
			{
	      std::cout << "Pontos da carta " << chart_index << ": " << '\n';
	      for (size_t j = 0; j < Qtd_pts_na_Carta[chart_index]; j++)
	      {
	        std::cout << "x = " << Read_from_Atlas (Atlas, Qtd_pts_na_Carta, chart_index, j, 0) /* raw way: *(Atlas + 3*sum_sizes(chart_index, Qtd_pts_na_Carta) + 3*j + 0) */ <<
					" ; y = " << Read_from_Atlas (Atlas, Qtd_pts_na_Carta, chart_index, j, 1) <<
					" ; z = " << Read_from_Atlas (Atlas, Qtd_pts_na_Carta, chart_index, j, 2) <<'\n';
	      }
			}
			std::cout << "Quantidade de pontos na carta " << chart_index << ": "<< Qtd_pts_na_Carta[chart_index] <<
			" ;    Dimensões:  z max = " << (z_max - chart_index*chart_depth) << " ; z min = " << (z_max - (chart_index + 1)*chart_depth) << '\n';
		}

		//registrando o excesso de pontos nas cartas:
		for (size_t i = 0; i < number_of_charts; i++)
		{
			if (Index_Vector[i] >= Points_per_Chart)
			{
				int Excess = Index_Vector[i] - Points_per_Chart;
			}
		}

		{
		int sum;
		sum=0;
		for (size_t i = 0; i < number_of_charts; i++) {sum = sum + Index_Vector[i];}
		std::cout << "\nTotal de pontos copiados para as cartas: " << sum <<'\n' << '\n';
		}

		std::cout << "\nIniciando sub-divisão das cartas com excedente de pontos." << '\n';

		int Max_number_of_points;
		Max_number_of_points = 0;
		//marcando quais são as cartas que excederam o limite de pontos e pegando a quantidade de pontos da maior carta:
		for (size_t chart_index = 0; chart_index < number_of_charts; chart_index++)
		{
			if (Qtd_pts_na_Carta[chart_index]>=Points_per_Chart)
			{
				Oversized_Charts[chart_index]=true;
				if (Max_number_of_points<Qtd_pts_na_Carta[chart_index]){ Max_number_of_points = Qtd_pts_na_Carta[chart_index]; }
			}
		}


		// ****
		// ****
		// **** Liberando memória para guardar apenas os pontos das cartas que excedem a quantidade de pontos:
		float *new_x, *new_y, *new_z;
		new_x = (float*) realloc ((void*) x, Max_number_of_points * sizeof(float));
		new_y = (float*) realloc ((void*) y, Max_number_of_points * sizeof(float));
		new_z = (float*) realloc ((void*) z, Max_number_of_points * sizeof(float));

		for (size_t chart_index = 0; chart_index < number_of_charts; chart_index++)
		{
      int* resized_regions = (int*) malloc (10*sizeof(int)); // array para armazenar dados da leading dimension reorganizada
      for (size_t i = 0; i < 10; i++)
      {
        resized_regions[i] = 0; //inicializando array
      }
      if (Oversized_Charts[chart_index])
			{
				std::cout << "\n\nCopiando pontos da carta " << chart_index << " para arrays de trabalho." << '\n';
				for (size_t i = 0; i < Qtd_pts_na_Carta[chart_index]; i++)
				{
					memcpy((new_x + i), (Atlas + 3*sum_sizes(chart_index, Qtd_pts_na_Carta) + 3*i + 0), sizeof(float));
					memcpy((new_y + i), (Atlas + 3*sum_sizes(chart_index, Qtd_pts_na_Carta) + 3*i + 1), sizeof(float));
					memcpy((new_z + i), (Atlas + 3*sum_sizes(chart_index, Qtd_pts_na_Carta) + 3*i + 2), sizeof(float));
				}

				std::cout << "Tomando dimensões da carta." << '\n';
				float * Chart_Extremes = (float*) malloc(6 * sizeof(float));
				memcpy(Chart_Extremes , Taking_measures(Max_number_of_points , new_x, new_y, new_z), 6*sizeof(float));

				std::cout << "x_min = " << *(Chart_Extremes+0) <<" ; x_max = " << *(Chart_Extremes+1) <<
									" ; y_min = " << *(Chart_Extremes+2) <<" ; y_max = " << *(Chart_Extremes+3) <<
									" ; z_min = " << *(Chart_Extremes+4) <<" ; z_max = " << *(Chart_Extremes+5) <<'\n';


				std::cout << "Iniciando medidas de densidade linear de pontos ao longo dos eixos coordenados." << '\n';

				//reunindo num único array todas as densidades lineares na seguinte ordem: (x_density[10], y_density[10], z_density[10])
				int linear_density[30];

				memcpy (linear_density , Linear_Density_caculator ( new_x, Max_number_of_points, 10), sizeof(float)*10);
				memcpy (linear_density + 10, Linear_Density_caculator ( new_y, Max_number_of_points, 10), sizeof(float)*10);
				memcpy (linear_density + 20, Linear_Density_caculator ( new_z, Max_number_of_points, 10), sizeof(float)*10);



				std::cout << "\nMostrando distribuição dos pontos ao longo do eixo x: " << '\n';
				for (size_t i = 0; i < 10; i++)	{	std::cout << "Quantidade de pontos na faixa "<< i << " : " << linear_density[i]<<'\n';}
				std::cout << "Entropia associada à distribuição dos pontos ao longo do eixo x : " << Shannon_Entropy(linear_density, 10) << '\n';


				std::cout << "\nMostrando distribuição dos pontos ao longo do eixo y: " << '\n';
				for (size_t i = 10; i < 20; i++){std::cout << "Quantidade de pontos na faixa "<< i << " : " << linear_density[i]<<'\n';}
				std::cout << "Entropia associada à distribuição dos pontos ao longo do eixo y : " << Shannon_Entropy(linear_density + 10, 10) << '\n';


				std::cout << "\nMostrando distribuição dos pontos ao longo do eixo z: " << '\n';
				for (size_t i = 20; i < 30; i++){std::cout << "Quantidade de pontos na faixa "<< i << " : " << linear_density[i]<<'\n';}
				std::cout << "Entropia associada à distribuição dos pontos ao longo do eixo z : " << Shannon_Entropy(linear_density + 20, 10) << '\n';

				int leading_density[10]; //associada ao maior espalhamento das coordenadas
				int body_density[10];
				int tail_density[10]; //associada ao menor espalhamento das coordenadas (valores mais reunidos )
				int keeping_track_of_which_dimension[3];

        //classificando distribuição de valores das coordenadas de acordo com a entropia:
				for (size_t i = 0; i < 3; i++)
				{
					if (Shannon_Entropy(linear_density + i*10 , 10) > Shannon_Entropy(linear_density + ((i+1)%3)*10 , 10)
								&& Shannon_Entropy(linear_density + i*10 , 10) > Shannon_Entropy(linear_density + ((i+2)%3)*10 , 10))
					{
						memcpy(leading_density , linear_density + i*10, 10*sizeof(int));
						keeping_track_of_which_dimension[0] = i; //guardando qual das distribuições lineares apresenta maior entropia (maior distribuição linear de valores)
					}
				}


				for (size_t i = 0; i < 3; i++)
				{
					if ( (Shannon_Entropy(linear_density + i*10 , 10) < Shannon_Entropy(linear_density + ((i+1)%3)*10 , 10)
								&& Shannon_Entropy(linear_density + i*10 , 10) > Shannon_Entropy(linear_density + ((i+2)%3)*10 , 10))
							| (Shannon_Entropy(linear_density + i*10 , 10) > Shannon_Entropy(linear_density + ((i+1)%3)*10 , 10)
										&& Shannon_Entropy(linear_density + i*10 , 10) < Shannon_Entropy(linear_density + ((i+2)%3)*10 , 10)))
					{
						memcpy(body_density , linear_density + i*10, 10*sizeof(int));
						keeping_track_of_which_dimension[1] = i; //guardando qual das distribuições lineares apresenta o valor intermediário de entropia
					}
				}



				for (size_t i = 0; i < 3; i++)
				{
					if (Shannon_Entropy(linear_density + i*10 , 10) < Shannon_Entropy(linear_density + ((i+1)%3)*10 , 10)
								&& Shannon_Entropy(linear_density + i*10 , 10) < Shannon_Entropy(linear_density + ((i+2)%3)*10 , 10))
					{
						memcpy(tail_density , linear_density + i*10, 10*sizeof(int));
						keeping_track_of_which_dimension[2] = i; //guardando qual das distribuições lineares apresenta menor entropia (maior concentração linear de valores)
					}
				}

				std::cout << "Leading dimension: " <<  keeping_track_of_which_dimension[0] << '\n';
				std::cout << "Intermediate dimension: " <<  keeping_track_of_which_dimension[1] << '\n';
				std::cout << "Tail dimension: " <<  keeping_track_of_which_dimension[2] << '\n';

        memcpy(resized_regions , resize_regions(leading_density, 10, 10000) , 10);

        std::cout << "Dimensão Líder reorganizada:" << '\n';
        for (size_t i = 0; i < 10; i++)
        {
          std::cout << "Quantidade de pontos na região " << i << " : " << resized_regions[i] << '\n';
        }


				free(Chart_Extremes);
			}
      free(resized_regions);
		}



		//int* X_Linear_Points_density = (int*) malloc(    );
		//int* Y_Linear_Points_density = (int*) malloc(    );
		//int* Z_Linear_Points_density = (int*) malloc(    );









		//free(X_Linear_Points_density);
		//free(Y_Linear_Points_density);
		//free(Z_Linear_Points_density);


		free(Oversized_Charts);
		free(Atlas);
		free(new_z);
		free(new_y);
		free(new_x);
		delete filename;
		delete ppchart;



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
