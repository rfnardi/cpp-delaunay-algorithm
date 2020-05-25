#ifndef ATLAS_H
#define ATLAS_H

#include <vector>
#include <array>
#include "./Point.hpp"

namespace del
{
  class Chart
  {
  public:
    Chart ();
    Chart (int);
    ~Chart ();
    int Chart_index;
    std::vector<bool> This_Chart_Connections; // Este vetor serve para dizer com quais outras cartas a presente carta possui fronteira
    std::vector<del::Point> Points;
  };

}
#endif
