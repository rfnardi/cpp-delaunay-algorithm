#ifndef FIND_EXTREMES
#define FIND_EXTREMES

#include "./Point.hpp"
#include <vector>
#include "./find_z_max.hpp"

del::Point del::Find_Extremal_Points::Find_Z_Max(std::vector<del::Point> pontos)
{
  del::Point Top_point;
  float z_max = 0.0;
  for(size_t i=0 ; i<pontos.size() ; i++)
  {
    if (pontos[i].p[2]>z_max)
    {
      z_max = pontos[i].p[2];
      Top_point = pontos[i];
    }
  }
  return Top_point;
}
#endif
