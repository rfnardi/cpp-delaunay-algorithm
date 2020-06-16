// *********************************************************************************
// ******* Useful functions to access information inside array of arrays with different sizes each:
// **
int sum_sizes(int I, int* index_vec_ptr)
{
	int sum;
	sum = 0;
	if (I>0)
	{
		for (size_t i = 0; i < I; i++)
		{
			sum = sum + (int) index_vec_ptr[i];
		}
	}
	return sum;
}

void Write_to_Atlas (float * Atlas_ptr, int* Chart_sizes_vec_ptr, int k, int i, int j, float Data)
{
	memcpy((Atlas_ptr + 3*sum_sizes(k, Chart_sizes_vec_ptr) + 3*i + j), &Data, sizeof(float));
}

float Read_from_Atlas (float * Atlas_ptr, int* Chart_sizes_vec_ptr, int k, int i, int j)
{
	return *(Atlas_ptr + 3*sum_sizes(k, Chart_sizes_vec_ptr) + 3*i + j);
}

// *********************************************************************************

//Função para trabalhar com tomada de dimensões de uma carta com excesso de pontos para efetuar sub-fatiamento:
float* Taking_measures(int arrays_size , float* x_vec, float* y_vec, float* z_vec)
	{
		float  x_min, x_max, y_min, y_max, z_min, z_max;
		static float result[6];

		for (size_t i = 0; i < arrays_size; i++)
		{
			if (i ==0 ) //iniciando valores para os mins e maxs:
			{
				x_min = *(x_vec+i);
				x_max = *(x_vec+i);
				y_min = *(y_vec+i);
				y_max = *(y_vec+i);
				z_min = *(z_vec+i);
				z_max = *(z_vec+i);
			}
			if(*(x_vec + i)<x_min){x_min = *(x_vec + i);}
			if(*(x_vec + i)>x_max){x_max = *(x_vec + i);}
			if(*(y_vec + i)<y_min){y_min = *(y_vec + i);}
			if(*(y_vec + i)>y_max){y_max = *(y_vec + i);}
			if(*(z_vec + i)<z_min){z_min = *(z_vec + i);}
			if(*(z_vec + i)>z_max){z_max = *(z_vec + i);}
		}
		result[0] = x_min;
		result[1] = x_max;
		result[2] = y_min;
		result[3] = y_max;
		result[4] = z_min;
		result[5] = z_max;

		return result; // result = {x_min , x_max , y_min , y_max , z_min , z_max }
	}
// *********************************************************************************


//Fazendo overloading da Função 'Taking measures' para trabalhar com tomada de dimensões de um array simples:
float* Taking_measures(int array_size , float* data_array)
	{
		float  min, max;
		static float result[2];

		for (size_t i = 0; i < array_size; i++)
		{
			if (i ==0 ) //iniciando valores para os mins e maxs:
			{
				min = *(data_array+i);
				max = *(data_array+i);
			}
			if(*(data_array + i)<min){min = *(data_array + i);}
			if(*(data_array + i)>max){max = *(data_array + i);}
		}
		result[0] = min;
		result[1] = max;

		return result; // result = {x_min , x_max }
	}


// *********************************************************************************


// ***** Função de avaliação da densidade linear: Basicamente monta o histograma dos valores armazenados em data_array 1-dimensional
// ***** localizado em array separando a contagem de pontos em 'number_of_regions'

int* Linear_Density_caculator ( int* linear_Density /*!!!! ARRAY DE RESULTADO !!!! TAMANHO: number_of_regions */ , float* data_array, int data_array_size, int number_of_regions)
{
	//inicializando linear_Density:
	for (size_t j = 0; j < number_of_regions; j++)
	{
		*(linear_Density +j) = 0;
	}
	//tomando limites dos valores contidos em data_array:
	float Data_Extremes[2];
	memcpy(Data_Extremes, Taking_measures(data_array_size , data_array), 2*sizeof(float));
	float region_size = Data_Extremes[1] - Data_Extremes[0];
	float subregion_size;
	subregion_size = (float) (region_size/((float) number_of_regions));

	//determinando quantidade de pontos dentro de cada região:
	for (size_t i = 0; i < data_array_size; i++)
	{
		for (size_t j = 0; j < number_of_regions; j++)
		{
			if ( (j != number_of_regions -1) && (data_array[i]>=(Data_Extremes[0] + j*subregion_size)) && data_array[i]<(Data_Extremes[0] + (j + 1)*subregion_size) )
			{
				linear_Density[j]++;
			}
			//making sure the last region will take points at the uper border:
			if ((j == number_of_regions -1) && (data_array[i]>=(Data_Extremes[0] + j*subregion_size)) && data_array[i]<=(Data_Extremes[1]) )
			{
				linear_Density[j]++;
			}
		}
	}
	return linear_Density;

}
// *********************************************************************************

double Shannon_Entropy(int* data_array, int array_size)
{
	int sum;
	sum =0;
	for (size_t i = 0; i < array_size; i++)
	{
		sum = sum + *(data_array+i);
	}
	double* stat_weights = (double*) malloc(sizeof(double)*array_size);

	for (size_t i = 0; i < array_size; i++)
	{
		*(stat_weights + i) = ((double) *(data_array + i))/( (double) sum) ;
	}

	double Entropy;
	Entropy = 0.0;
	for (size_t i = 0; i < array_size; i++)
	{
		if (*(stat_weights +i) != 0)
		{
			Entropy = Entropy -  *(stat_weights +i)*log(*(stat_weights+i));
		}
	}

	return Entropy;

	free(stat_weights);
}

// *********************************************************************************
//função que detecta se a região é ou não simplesmente conexa
bool checking_connectiveness(int* histogram, int histogram_size)
{
	bool result;
	result = true;
	for (size_t i = 0; i < histogram_size; i++)
	{
		if (*(histogram + i) == 0)
		{
			result = false;
		}
	}
	return result;
}

// *********************************************************************************
int* resize_regions ( int* new_linear_density_plus_sizes /* !!!!ARRAY DE RESULTADO!!!! */ , int* linear_density, int number_of_regions, int max_number_of_points_per_region /* = 10000 no exemplo usado*/ )
{
  //na primeira metate deste array são armazenadas as quantidades de pontos de cada região reorganizada;
  //na segunda metade deste array são armazenadas a quantidade de regiões que se fundiram para formar a presente região
	std::cout << "Em resize_regions. ******************" << '\n';


  //int* new_linear_density_plus_sizes = (int*) malloc(2*number_of_regions*sizeof(int));


	for (size_t i = 0; i < number_of_regions; i++)
	{
		*(new_linear_density_plus_sizes +i) = 0;
	}

  int Sum, sum, j, k, l;
  j=0;
	l=0;
	k=0;
	sum =0;
	Sum =0;
  while (j<number_of_regions)
  {
		if (linear_density[j]<max_number_of_points_per_region)
		{
			sum = linear_density[j];
			k = 0;
			while (true)
			{
				Sum = sum;
				k++;
				if (j+k >= number_of_regions){ break;}
				sum = sum + linear_density[j+k];
        if (sum >= max_number_of_points_per_region ){ break;}
        std::cout << "k = " << k << '\n';
			}

			new_linear_density_plus_sizes[l] = Sum;

			std::cout << "copiada a soma dos itens desde " << j << " até "<< j+k << " do array líder para a componente " << l << " do array reorganizado." << '\n';
      j += k;
			new_linear_density_plus_sizes[number_of_regions+l] = k;
			l++;
		}
		if (linear_density[j] >= max_number_of_points_per_region)
		{
			*(new_linear_density_plus_sizes + l) = linear_density[j];
			std::cout << "copiado item excedente " << j << " do array líder para a componente " << l << " do array reorganizado." << '\n';
			k = 1;
      new_linear_density_plus_sizes[number_of_regions+l] = k;
			j++;
			l++;
		}
  }

	std::cout << "Saindo de resize_regions. ******************** " << '\n';

  return new_linear_density_plus_sizes;

  //free(new_linear_density_plus_sizes);

}

// *********************************************************************************
//contando o número de sub-cartas total:
int sub_charts_counting(int number_of_reorganized_regions, int* sizes_and_fusions, int global_max_pts_per_chart)
{
	std::cout << "Em sub_charts_counting. Valores dos parâmetros passados para a função:" << '\n';
	std::cout << "number_of_reorganized_regions: " << number_of_reorganized_regions << '\n';
	std::cout << "global_max_pts_per_chart: " << global_max_pts_per_chart << '\n';
	for (size_t i = 0; i < number_of_reorganized_regions*2; i++)
	{
		std::cout << "sizes_and_fusions [" << i << "] : "<<  sizes_and_fusions[i] << '\n';
	}

	int number_of_sub_charts;
	float* size_regions_rate = (float*) malloc(number_of_reorganized_regions*sizeof(float));

	for (size_t i = 0; i < number_of_reorganized_regions; i++)
	{
		if (sizes_and_fusions[i]<global_max_pts_per_chart)
		{
			size_regions_rate[i] = 0.0;
			number_of_sub_charts++;
		}
		else
		{
			size_regions_rate[i] = sizes_and_fusions[i]/global_max_pts_per_chart;
			number_of_sub_charts += 1 + (int) size_regions_rate[i];
		}
	}

	return number_of_sub_charts;
	free(size_regions_rate);
}

// *********************************************************************************

float* sub_charts_building (float* sub_atlas /* !!!!!ARRAY DE RESULTADO: float* sub_atlas = (float*) malloc(3*number_of_points*sizeof(float));*/ ,
															float* x, float* y, float* z,
															int number_of_points, //tamanho dos arrays x, y e z
															float* mins_and_maxs, //mins_and_maxs[0] = menor valor de x, mins_and_maxs[1] = maior valor de x , etc
															int* keeping_track_of_which_dimension, //keeping_track_of_which_dimension[0] = leading_density;
																																		 //keeping_track_of_which_dimension[1] = body_density;
																																		 //keeping_track_of_which_dimension[2] = tail_density;
														  int number_of_pre_reorganized_regions, //tamanho da leading_density antes de passar pela função resize_regions
															int number_of_reorganized_regions, 		 //tamanho da leading_density após passar pela resize_regions
															int* sizes_and_fusions, 							 //quantidade de pontos em cada região e número de fusões ocorridas ao passar pela resize_regions
															int global_max_pts_per_chart)					 //número máximo de pontos por carta definido globalmente no programa
{

	std::cout << "\n\nEm sub_charts_building. ******************************************************* \n" << '\n';

	float x_width = mins_and_maxs[1]-mins_and_maxs[0];
	float y_width = mins_and_maxs[3]-mins_and_maxs[2];
	float z_width = mins_and_maxs[5]-mins_and_maxs[4];


	float* size_regions_rate = (float*) malloc(number_of_reorganized_regions*sizeof(float));

	int number_of_sub_charts;
	number_of_sub_charts = 0;

	std::cout << "number_of_reorganized_regions = " << number_of_reorganized_regions << '\n';

	//contando o número de sub-cartas total:
	for (size_t i = 0; i < number_of_reorganized_regions; i++)
	{
		if (sizes_and_fusions[i]<global_max_pts_per_chart)
		{
			*(size_regions_rate + i) = 0.0;
			number_of_sub_charts++;
		}
		else
		{
			*(size_regions_rate + i) = ((float) sizes_and_fusions[i])/((float) global_max_pts_per_chart);
			number_of_sub_charts += 1 + (int) size_regions_rate[i];
		}
	}

	std::cout << "Em sub_charts_building: contagem de subcartas realizada com sucesso. number_of_sub_charts = " << number_of_sub_charts << '\n';

	int Index_Vector[number_of_reorganized_regions];
	int New_Index_Vector[number_of_sub_charts];

	for (size_t i = 0; i < number_of_reorganized_regions; i++)
	{
		*(Index_Vector+i) = 0;
	}

	for (size_t i = 0; i < number_of_sub_charts; i++)
	{
		*(New_Index_Vector+i) = 0;
	}

	std::cout << "Iniciando contagem de pontos em cada subcarta." << '\n';
	//------------------------------------------------------------------------------------------------



	//contando a quantidade de pontos em cada carta:

	// ********************* TORNAR ESTE BLOCO UMA FUNÇÃO SEPARADA *************************vvvvvvvvv



		size_t k, j;
		size_t l;
		l = 0;
		//for (size_t l = 0; l < number_of_points ; l++)
		while(l<number_of_points)
		{
			k=0;
			j=0;
			while(j < number_of_sub_charts) //j plays the role of chart_index
			{
				if (x[l]>=mins_and_maxs[0]+ k*x_width/number_of_pre_reorganized_regions && x[l]< mins_and_maxs[0] + (k + sizes_and_fusions[number_of_pre_reorganized_regions+k])*x_width/number_of_pre_reorganized_regions )
				{
					if (size_regions_rate[k] == 0.0)
					{
						Index_Vector[k]++;
						New_Index_Vector[j]++;
						j++;
						k++;
						std::cout << "Em sub_charts_building. Encontrou ponto em carta secundária: k = " << k << " ; j = "<< j << '\n';
						break;
					}

					if (size_regions_rate[k] != 0.0)
					{
						float step2;
						switch (keeping_track_of_which_dimension[1])
						{
							case 1:
									step2 = y_width/ ((float) (1 + (int) size_regions_rate[k]));
									for (size_t b = 0; b < (1 + (int) size_regions_rate[k]); b++)
									{
										if (b != (int) size_regions_rate[k] && y[l]>=mins_and_maxs[2]+ b*step2 && y[l]< mins_and_maxs[2] + (b + 1)*step2)
										{
											New_Index_Vector[j]++;
											j++;
											std::cout << "Em sub_charts_building. Encontrou ponto em carta terciária: k = " << k << " ; j = " << j << " ; b = " << b << '\n';

										}
										if (b == (int) size_regions_rate[k] && y[l]>=mins_and_maxs[2]+ b*step2 && y[l]<= mins_and_maxs[3])
										{
											New_Index_Vector[j]++;
											j++;
											std::cout << "Em sub_charts_building. Encontrou ponto em carta terciária: k = " << k << " ; j = " << j << " ; b = " << b << '\n';

										}
									}
							break;

							case 2:
									step2 = z_width/((float) (1 + (int) size_regions_rate[k]));
									for (size_t b = 0; b < (1 + (int) size_regions_rate[k]); b++)
									{
										if (b != (int) size_regions_rate[k] && z[l]>=mins_and_maxs[4]+ b*step2 && y[l]< mins_and_maxs[4] + (b + 1)*step2)
										{
											New_Index_Vector[j]++;
											j++;
											std::cout << "Em sub_charts_building. Encontrou ponto em carta terciária: k = " << k << " ; j = " << j << " ; b = " << b << '\n';
											break;
										}
										if (b == (int) size_regions_rate[k] && z[l]>=mins_and_maxs[4]+ b*step2 && y[l]<= mins_and_maxs[5])
										{
											New_Index_Vector[j]++;
											j++;
											std::cout << "Em sub_charts_building. Encontrou ponto em carta terciária: k = " << k << " ; j = " << j << " ; b = " << b << '\n';
											break;
										}
									}
							break;
						}
					}
				}
			}
			l++;
		}


		// ********************* TORNAR ESTE BLOCO UMA FUNÇÃO SEPARADA *************************^^^^^








	//------------------------------------------------------------------------------------------------

	int* chart_sizes = (int*) malloc(number_of_sub_charts*sizeof(int));
	memcpy(chart_sizes , New_Index_Vector, number_of_sub_charts*sizeof(int));

	for (size_t i = 0; i < number_of_sub_charts; i++)
	{
		*(New_Index_Vector+i) = 0;
	}

	//------------------------------------------------------------------------------------------------
	std::cout << "Iniciando alocação de pontos nas cartas." << '\n';
	//alocando pontos nas subcartas:
	switch (keeping_track_of_which_dimension[0])
	{
		case 0:
		for (size_t l = 0; l < number_of_points; l++)
		{
			size_t k, j;
			k=0;
			j=0;
			while(k < number_of_reorganized_regions) //k plays the role of chart_index
			{
				if (x[l]>=mins_and_maxs[0]+ k*x_width/number_of_pre_reorganized_regions && x[l]< mins_and_maxs[0] + (k + sizes_and_fusions[number_of_pre_reorganized_regions+k])*x_width/number_of_pre_reorganized_regions )
				{
					if (size_regions_rate[k] == 0.0)
					{
						Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
						Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
						Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);

						Index_Vector[k]++;
						New_Index_Vector[j]++;
					}

					if (size_regions_rate[k] != 0.0)
					{
						float step2;
						switch (keeping_track_of_which_dimension[1])
						{
							case 1:
									step2 = y_width/(1 + (int) size_regions_rate[k]);
									for (size_t b = 0; b < (1 + (int) size_regions_rate[k]); b++)
									{
										if (b != (int) size_regions_rate[k] && y[l]>=mins_and_maxs[2]+ b*step2 && y[l]< mins_and_maxs[2] + (b + 1)*step2)
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && y[l]>=mins_and_maxs[2]+ b*step2 && y[l]<= mins_and_maxs[3])
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										j++;
									}
							break;

							case 2:
									step2 = z_width/(1 + (int) size_regions_rate[k]);
									for (size_t b = 0; b < (1 + (int) size_regions_rate[k]); b++)
									{
										if (b != (int) size_regions_rate[k] && z[l]>=mins_and_maxs[4]+ b*step2 && y[l]< mins_and_maxs[4] + (b + 1)*step2)
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && z[l]>=mins_and_maxs[4]+ b*step2 && y[l]<= mins_and_maxs[5])
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										j++;
									}
							break;
						}
					}
					k++;
					j++;
				}
				l++;
			}

		}
		break;

		case 1:
    for (size_t l = 0; l < number_of_points; l++)
		{
			size_t k, j;
			k=0;
			j=0;
			while(k < number_of_reorganized_regions) //k plays the role of chart_index
			{
				if (y[l]>=mins_and_maxs[0]+ k*y_width/number_of_pre_reorganized_regions && y[l]< mins_and_maxs[0] + (k + sizes_and_fusions[number_of_pre_reorganized_regions+k])*y_width/number_of_pre_reorganized_regions )
				{
					if (size_regions_rate[k] == 0.0)
					{
						Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
						Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
						Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
						Index_Vector[k]++;
						New_Index_Vector[j]++;
					}

					if (size_regions_rate[k] != 0.0)
					{
						float step2;
						switch (keeping_track_of_which_dimension[1])
						{
							case 0:
									step2 = x_width/(1 + (int) size_regions_rate[k]);
									for (size_t b = 0; b < (1 + (int) size_regions_rate[k]); b++)
									{
										if (b != (int) size_regions_rate[k] && x[l]>=mins_and_maxs[2]+ b*step2 && x[l]< mins_and_maxs[2] + (b + 1)*step2)
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && x[l]>=mins_and_maxs[2]+ b*step2 && x[l]<= mins_and_maxs[3])
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										j++;
									}
							break;

							case 2:
									step2 = z_width/(1 + (int) size_regions_rate[k]);
									for (size_t b = 0; b < (1 + (int) size_regions_rate[k]); b++)
									{
										if (b != (int) size_regions_rate[k] && z[l]>=mins_and_maxs[4]+ b*step2 && z[l]< mins_and_maxs[4] + (b + 1)*step2)
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && z[l]>=mins_and_maxs[4]+ b*step2 && z[l]<= mins_and_maxs[5])
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										j++;
									}
							break;
						}
					}
					k++;
					j++;
				}
				l++;
			}

		}
		break;

		case 2:
    for (size_t l = 0; l < number_of_points; l++)
		{
			size_t k, j;
			k=0;
			j=0;
			while(k < number_of_reorganized_regions) //k plays the role of chart_index
			{
				if (z[l]>=mins_and_maxs[0]+ k*z_width/number_of_pre_reorganized_regions && z[l]< mins_and_maxs[0] + (k + sizes_and_fusions[number_of_pre_reorganized_regions+k])*z_width/number_of_pre_reorganized_regions )
				{
					if (size_regions_rate[k] == 0.0)
					{
						Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
						Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
						Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
						Index_Vector[k]++;
						New_Index_Vector[j]++;
					}

					if (size_regions_rate[k] != 0.0)
					{
						float step2;
						switch (keeping_track_of_which_dimension[1])
						{
							case 1:
									step2 = y_width/(1 + (int) size_regions_rate[k]);
									for (size_t b = 0; b < (1 + (int) size_regions_rate[k]); b++)
									{
										if (b != (int) size_regions_rate[k] && y[l]>=mins_and_maxs[2]+ b*step2 && y[l]< mins_and_maxs[2] + (b + 1)*step2)
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && y[l]>=mins_and_maxs[2]+ b*step2 && y[l]<= mins_and_maxs[3])
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										j++;
									}
							break;

							case 0:
									step2 = x_width/(1 + (int) size_regions_rate[k]);
									for (size_t b = 0; b < (1 + (int) size_regions_rate[k]); b++)
									{
										if (b != (int) size_regions_rate[k] && x[l]>=mins_and_maxs[4]+ b*step2 && x[l]< mins_and_maxs[4] + (b + 1)*step2)
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && x[l]>=mins_and_maxs[4]+ b*step2 && x[l]<= mins_and_maxs[5])
										{
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 0, x[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 1, y[l]);
											Write_to_Atlas (sub_atlas, chart_sizes, k, New_Index_Vector[j], 2, z[l]);
											New_Index_Vector[j]++;
										}
										j++;
									}
							break;
						}
					}
					k++;
					j++;
				}
				l++;
			}

		}
		break;

	}
	//------------------------------------------------------------------------------------------------

	std::cout << "Alocação de pontos realizada com sucesso." << '\n';

	std::cout << "Alocando dados em array de resultado." << '\n';

	sub_atlas = (float*) realloc((void*) sub_atlas , 3*number_of_points*sizeof(float) + number_of_sub_charts*sizeof(float) + 1);

	memmove ( sub_atlas + number_of_sub_charts*sizeof(float) + 1, sub_atlas, 3*number_of_points*sizeof(float) ); //FAZER TESTE DISSO
	memcpy(sub_atlas, chart_sizes, number_of_sub_charts*sizeof(int));
	*(sub_atlas + number_of_sub_charts*sizeof(int)) = -42; //MARCADOR DO FIM DO CHART_SIZES

	free(chart_sizes);
	free(size_regions_rate);

	return sub_atlas;



}









// *********************************************************************************
