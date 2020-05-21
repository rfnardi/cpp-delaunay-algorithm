#ifndef CONVEX_HULL
#define CONVEX_HULL

#include "./Point.hpp"

del::Edge::Edge()
{
  this->really_a_Convex_Hull_member = false;
  del::Point Origin;
  this -> first_Point = Origin;
  this -> second_Point = Origin;
}

#endif
