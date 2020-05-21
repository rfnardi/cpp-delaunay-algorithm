#ifndef CONVEX_HULL
#define CONVEX_HULL

#include "./Point.hpp"
#include "./convex_hull.hpp"
#include <vector>

del::Edge::Edge()
{
  this->really_a_Convex_Hull_member = false;
  del::Point Origin;
  this -> first_Point = Origin;
  this -> second_Point = Origin;
}

del::Convex_Hull::Convex_Hull()
{

}

#endif
