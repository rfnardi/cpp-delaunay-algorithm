#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <cstring>
#include <cmath>
#include "./Atlas_functions.cpp"


float* sub_charts_building(float* x, float* y, float* z, int number_of_points, float* mins_and_maxs, int* keeping_track_of_which_dimension,
														 int number_of_pre_reorganized_regions, int number_of_reorganized_regions, int* sizes_and_fusions, int global_max_pts_per_chart)
{
	float* result = (float*) malloc(3*number_of_points*sizeof(float));

	float = x_width = mins_and_maxs[1]-mins_and_maxs[0];
	float = y_width = mins_and_maxs[3]-mins_and_maxs[2];
	float = z_width = mins_and_maxs[5]-mins_and_maxs[4];


	float* size_regions_rate = (float*) malloc(number_of_reorganized_regions*sizeof(float));
	float* oversized_regions = (float*) malloc(number_of_reorganized_regions*sizeof(float));

	int number_of_sub_charts;
	number_of_sub_charts =0;

	for (size_t i = 0; i < number_of_reorganized_regions; i++)
	{
		if (sizes_and_fusions[i]<global_max_pts_per_chart)
		{
			size_regions_rate[i] = 0.0;
			oversized_regions[i] = false;
			number_of_sub_charts++;
		}
		else
		{
			oversized_regions[i] = false;
			size_regions_rate[i] = sizes_and_fusions[i]/global_max_pts_per_chart;
			number_of_sub_charts += 1 + (int) size_regions_rate[i];
		}
	}

	int Index_Vector[number_of_reorganized_regions];
	int New_Index_Vector[number_of_sub_charts];

	for (size_t i = 0; i < number_of_sub_charts; i++)
	{
		Index_Vector[i] = 0;
	}


	switch (keeping_track_of_which_dimension[0])
	{
		case 0:
		for (size_t l = 0; l < number_of_points; l++)
		{
			//for (size_t k = 0; k < number_of_reorganized_regions; k++) //plays the role of chart_index

			size_t k, j;
			k=0;
			j=0;
			while(k < number_of_reorganized_regions)
			{
				if (x[l]>=mins_and_maxs[0]+ k*x_width/number_of_pre_reorganized_regions && x[l]< mins_and_maxs[0] + (k + sizes_and_fusions[10+k])*x_width/number_of_pre_reorganized_regions )
				{
					if (size_regions_rate[k] == 0.0)
					{
						//Write_to_Atlas (result, sizes_and_fusions, k, Index_Vector[i], 0, x[l]);
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
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && y[l]>=mins_and_maxs[2]+ b*step2 && y[l]<= mins_and_maxs[3])
										{
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
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && z[l]>=mins_and_maxs[4]+ b*step2 && y[l]<= mins_and_maxs[5])
										{
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
			}

		}
		break;






		case 1:
    for (size_t l = 0; l < number_of_points; l++)
		{
			//for (size_t k = 0; k < number_of_reorganized_regions; k++) //plays the role of chart_index

			size_t k, j;
			k=0;
			j=0;
			while(k < number_of_reorganized_regions)
			{
				if (y[l]>=mins_and_maxs[0]+ k*y_width/number_of_pre_reorganized_regions && y[l]< mins_and_maxs[0] + (k + sizes_and_fusions[10+k])*y_width/number_of_pre_reorganized_regions )
				{
					if (size_regions_rate[k] == 0.0)
					{
						//Write_to_Atlas (result, sizes_and_fusions, k, Index_Vector[i], 0, x[l]);
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
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && x[l]>=mins_and_maxs[2]+ b*step2 && x[l]<= mins_and_maxs[3])
										{
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
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && z[l]>=mins_and_maxs[4]+ b*step2 && z[l]<= mins_and_maxs[5])
										{
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
			}

		}
		break;






		case 2:
    for (size_t l = 0; l < number_of_points; l++)
		{
			//for (size_t k = 0; k < number_of_reorganized_regions; k++) //plays the role of chart_index

			size_t k, j;
			k=0;
			j=0;
			while(k < number_of_reorganized_regions)
			{
				if (z[l]>=mins_and_maxs[0]+ k*z_width/number_of_pre_reorganized_regions && z[l]< mins_and_maxs[0] + (k + sizes_and_fusions[10+k])*z_width/number_of_pre_reorganized_regions )
				{
					if (size_regions_rate[k] == 0.0)
					{
						//Write_to_Atlas (result, sizes_and_fusions, k, Index_Vector[i], 0, x[l]);
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
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && y[l]>=mins_and_maxs[2]+ b*step2 && y[l]<= mins_and_maxs[3])
										{
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
											New_Index_Vector[j]++;
										}
										if (b == (int) size_regions_rate[k] && x[l]>=mins_and_maxs[4]+ b*step2 && x[l]<= mins_and_maxs[5])
										{
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
			}

		}
		break;

	}



	return result;
	free(oversized_regions);
	free(size_regions_rate);
	free(result);
}

int main()
{
  float* sub_charts_building(float* x, float* y, float* z, int number_of_points, float* mins_and_maxs, int* keeping_track_of_which_dimension,
  														 int number_of_pre_reorganized_regions, int number_of_reorganized_regions, int* sizes_and_fusions, int global_max_pts_per_chart)
  return 0;
}
