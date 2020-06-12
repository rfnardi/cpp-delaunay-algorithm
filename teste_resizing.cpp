#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <cstring>
#include <cmath>

int* resize_regions (int* linear_density, int number_of_regions, int max_number_of_points_per_region /* = 10000 no exemplo usado*/ )
{
  //na primeira metate deste array são armazenadas as quantidades de pontos de cada região reorganizada;
  //na segunda metade deste array são armazenadas a quantidade de regiões que se fundiram para formar a presente região
  int* new_linear_density_plus_sizes = (int*) malloc(2*number_of_regions*sizeof(int));


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
        //std::cout << "k = " << k << '\n';
			}

			new_linear_density_plus_sizes[l] = Sum;

			//std::cout << "copiada a soma dos itens desde " << j << " até "<< j+k << " do array líder para a componente " << l << " do array reorganizado." << '\n';
      j += k;
			new_linear_density_plus_sizes[number_of_regions+l] = k;

			l++;
		}
		if (linear_density[j] >= max_number_of_points_per_region)
		{
			*(new_linear_density_plus_sizes + l) = linear_density[j];
			//std::cout << "copiado item excedente " << j << " do array líder para a componente " << l << " do array reorganizado." << '\n';
			k = 1;
      new_linear_density_plus_sizes[number_of_regions+l] = k;
			j++;
			l++;
		}
  }

  return new_linear_density_plus_sizes;

  free(new_linear_density_plus_sizes);
}

int main()
{
  int* array_in = (int*) malloc(10*sizeof(int));
  int* array_out = (int*) malloc(20*sizeof(int));

  array_in[0] = 2201;
  array_in[1] = 4537;
  array_in[2] = 5822;
  array_in[3] = 8011;
  array_in[4] = 13435;
  array_in[5] = 14158;
  array_in[6] = 8028;
  array_in[7] = 5812;
  array_in[8] = 4351;
  array_in[9] = 2465;

  array_out = resize_regions (array_in, 10, 10000);
  for (size_t i = 0; i < 10; i++)
  {
    std::cout << "Região " << i << " : " << array_in[i] << "  -----> " << array_out[i] << '\n';
  }

  for (size_t i = 10; i < 20; i++)
  {
    std::cout << "Quantidade de regiões que se fundiram para formar a região " << i-10 << " : "  << array_out[i] << '\n';
  }


  free(array_out);
  free(array_in);
  return 0;

}
