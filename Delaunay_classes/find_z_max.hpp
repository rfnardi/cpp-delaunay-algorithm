#ifndef FIND_EXTREMES_H
#define FIND_EXTREMES_H

#include "./Point.hpp"
#include <vector>

namespace del
{
  class Find_Extremal_Points
  {
    public:

    Find_Extremal_Points();
    ~Find_Extremal_Points();

    del::Point Find_Z_Max(std::vector<del::Point>);
  };

}
#endif
