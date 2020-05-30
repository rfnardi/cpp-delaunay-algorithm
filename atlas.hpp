#ifndef ATLAS_H
#define ATLAS_H

#include <vector>
#include <array>
#include "./Point.hpp"

namespace del
{
  class Atlas
  {
  public:
    int * ptr;
    Atlas ();
    Atlas (int , int );
    ~Atlas ();
    int Chart_index;
    std::vector<bool> This_Chart_Connections; // Este vetor serve para dizer com quais outras cartas a presente carta possui fronteira
    std::vector<del::Point> Points;
  };

}
#endif
