// ********************* TORNAR ESTE BLOCO UMA FUNÇÃO SEPARADA *************************vvvvvvvvv



  size_t region_index, sub_chart_index, l;
  l = 0;
  bool jump_out, over_counting_warning;

  if (keeping_track_of_which_dimension[0] = 1) // se y for a dimensão líder
  {
    std::cout << "Direção líder: y" << '\n';
    float step1 = y_width/( (float) number_of_original_regions);
    std::cout << "Valor de step1: " << step1 << ". \n";

    while(l<number_of_points)
    {
      //std::cout << "\nClassificando ponto (" << x[l] << ", "<< y[l] << ", " << z[l] << "):" <<'\n';
      region_index=0;
      sub_chart_index=0;
      while(sub_chart_index < number_of_sub_charts && region_index < number_of_re_shaped_regions)
      {
        jump_out = false;
        over_counting_warning = false;
        if (size_regions_rate[region_index] == 0.0)//happens when the number of points doesn't exceed the max per chart
        {
          if (sub_chart_index != (number_of_sub_charts - 1) && y[l]>=mins_and_maxs[2] + sum_sizes(region_index, sizes_and_fusions + number_of_re_shaped_regions)*step1 && y[l]< mins_and_maxs[2] + (sum_sizes(region_index + 1, sizes_and_fusions + number_of_re_shaped_regions))*step1)
          {
            Index_Vector[region_index]++;
            New_Index_Vector[sub_chart_index]++;
            //std::cout << "Em sub_charts_building. Encontrou ponto em carta secundária: region_index = " << region_index << " ; sub_chart_index = "<< sub_chart_index << '\n';
            break;
          }
          if (sub_chart_index == (number_of_sub_charts - 1) && y[l]>=mins_and_maxs[2] + sum_sizes(region_index, sizes_and_fusions + number_of_re_shaped_regions)*step1 && y[l]<= mins_and_maxs[3] )
          {
            Index_Vector[region_index]++;
            New_Index_Vector[sub_chart_index]++;
            //std::cout << "Em sub_charts_building. Encontrou ponto em carta secundária: region_index = " << region_index << " ; sub_chart_index = "<< sub_chart_index << '\n';
            break;
          }
        }

        if (size_regions_rate[region_index] != 0.0)
        {
          float step2;
          step2 = x_width/ ((float) (1 + (int) size_regions_rate[region_index]));         //OK
          for (size_t b = 0; b < (1 + (int) size_regions_rate[region_index]); b++)
          {
            if (sub_chart_index != (number_of_sub_charts - 1) && y[l]>=mins_and_maxs[2] + sum_sizes(region_index, sizes_and_fusions + number_of_re_shaped_regions)*step1 && y[l]< mins_and_maxs[2] + (sum_sizes(region_index + 1, sizes_and_fusions + number_of_re_shaped_regions))*step1)
            {
              if (b != (int) size_regions_rate[region_index] && x[l]>=mins_and_maxs[0]+ b*step2 && x[l]< mins_and_maxs[0] + (b + 1)*step2)
              {
                New_Index_Vector[sub_chart_index]++;
                //std::cout << "Em sub_charts_building. Encontrou ponto em carta terciária: region_index = " << region_index << " ; sub_chart_index = " << sub_chart_index << " ; b = " << b << '\n';
                jump_out = true;
                break;
              }
              if (b == (int) size_regions_rate[region_index] && x[l]>=mins_and_maxs[0]+ b*step2 && x[l]<= mins_and_maxs[1])
              {
                New_Index_Vector[sub_chart_index]++;
                //std::cout << "Em sub_charts_building. Encontrou ponto em carta terciária: region_index = " << region_index << " ; sub_chart_index = " << sub_chart_index << " ; b = " << b << '\n';
                jump_out = true;
                break;
              }
            }
            if (sub_chart_index == (number_of_sub_charts - 1) && y[l]>=mins_and_maxs[2] + sum_sizes(region_index, sizes_and_fusions + number_of_re_shaped_regions)*step1 && y[l]<= mins_and_maxs[3] )
            {
              if (b != (int) size_regions_rate[region_index] && x[l]>=mins_and_maxs[0]+ b*step2 && x[l]< mins_and_maxs[0] + (b + 1)*step2)
              {
                New_Index_Vector[sub_chart_index]++;
                //std::cout << "Em sub_charts_building. Encontrou ponto em carta terciária: region_index = " << region_index << " ; sub_chart_index = " << sub_chart_index << " ; b = " << b << '\n';
                jump_out = true;
                break;
              }
              if (b == (int) size_regions_rate[region_index] && x[l]>=mins_and_maxs[0]+ b*step2 && x[l]<= mins_and_maxs[1])
              {
                New_Index_Vector[sub_chart_index]++;
                //std::cout << "Em sub_charts_building. Encontrou ponto em carta terciária: region_index = " << region_index << " ; sub_chart_index = " << sub_chart_index << " ; b = " << b << '\n';
                jump_out = true;
                break;
              }
            }
            //std::cout << "PASSOU AQUI. region_index = " << region_index << " ; sub_chart_index = " << sub_chart_index << " ; b = " << b << '\n';
            sub_chart_index++;
            over_counting_warning = true;
          }
          if (jump_out) {
            //std::cout << "jump out" << '\n';
            break;}
        }
        region_index++;
        if (!over_counting_warning) {sub_chart_index++;}
        else{over_counting_warning = false;}

      }
      l++;
    }
  }

  // ********************* TORNAR ESTE BLOCO UMA FUNÇÃO SEPARADA *************************^^^^^
