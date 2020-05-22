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
  del::Edge trivial_edge;
  edge_collection.push_back(trivial_edge);
}

bool del::Convex_Hull::reliability ()
{
  return (this->edge_collection[0].first_Point == this->edge_collection[this->edge_collection.size()-1].second_Point);
}

#endif
