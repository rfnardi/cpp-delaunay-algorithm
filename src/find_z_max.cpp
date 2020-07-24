#ifndef FIND_EXTREMES
#define FIND_EXTREMES

#include "./Point.hpp"
#include <vector>
#include "./find_z_max.hpp"

del::Find_Extremal_Points::Find_Extremal_Points(){};
del::Find_Extremal_Points::~Find_Extremal_Points(){};

del::Point del::Find_Extremal_Points::Find_Z_Max(std::vector<del::Point> pontos)
{
  del::Point Top_point;
  float z_max = 0.0;
  for(size_t i=0 ; i<pontos.size() ; i++)
  {
    if (pontos[i].z>z_max)
    {
      z_max = pontos[i].z;
      Top_point = pontos[i];
    }
  }
  return Top_point;
}
#endif
