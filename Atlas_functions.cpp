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

int* Linear_Density_caculator (float* data_array, int data_array_size, int number_of_regions)
{
	int* linear_Density = (int*) malloc(number_of_regions*sizeof(int));
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
	free(linear_Density);
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
int* resize_regions (int* linear_density, int number_of_regions, int max_number_of_points_per_region /* = 10000 no exemplo usado*/ )
{
  int* new_linear_density = (int*) malloc(number_of_regions*sizeof(int));
	for (size_t i = 0; i < number_of_regions; i++)
	{
		*(new_linear_density +i) = 0;
	}
	int* sizes = (int*) malloc(number_of_regions*sizeof(int));
	for (size_t i = 0; i < number_of_regions; i++)
	{
		*(sizes +i) = 0;
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
			do
			{
				Sum = sum;
				k++;
				j += k;
				if (j >= number_of_regions){ break;}
				sum = sum + linear_density[j];
			}
			while (sum < max_number_of_points_per_region );
			new_linear_density[l] = Sum;

			std::cout << "copiada a soma dos itens desde " << j << " até "<< j+k << " do array líder para a componente " << l << " do array reorganizado." << '\n';

			sizes[l] = k;

			l++;
		}
		if (linear_density[j] >= max_number_of_points_per_region)
		{
			*(new_linear_density + l) = linear_density[j];
			std::cout << "copiado item excedente " << j << " do array líder para a componente " << l << " do array reorganizado." << '\n';
			k = 1;
			sizes[l] = k;
			j++;
			l++;
		}
  }


  return new_linear_density; //work here!

  free(new_linear_density);
	free(sizes);
}



// *********************************************************************************
