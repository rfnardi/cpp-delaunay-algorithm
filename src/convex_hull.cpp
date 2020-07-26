#ifndef CONVEX_HULL
#define CONVEX_HULL

#include "./Point.hpp"
#include "./convex_hull.hpp"
#include "./Triangle.hpp"
#include <cstddef>
#include <vector>

del::Edge::~Edge(){};

del::Edge::Edge()
{
  this->really_a_Convex_Hull_member = false;
  del::Point Origin;
  this -> first_Point = Origin;
  this -> second_Point = Origin;
}

del::Convex_Hull::~Convex_Hull(){};

del::Convex_Hull::Convex_Hull()
{
  del::Edge trivial_edge;
  edge_collection.push_back(trivial_edge);
}

bool del::Convex_Hull::reliability ()
{
	// é necessário alterar este método. O convex_hull pode ser formado por mais do que um anel de edges.
	//
  return (this->edge_collection[0].first_Point == this->edge_collection[this->edge_collection.size()-1].second_Point);
}

bool del::Convex_Hull::all_points_in_convex_hull(del::Triangle T )
{
	bool A_check = false;
	bool B_check = false;
	bool C_check = false;
	bool all_check = false;
	for (size_t i = 0; i < this->edge_collection.size(); ++i) 
	{
		if ( this->edge_collection[i].first_Point == T.A |  this->edge_collection[i].second_Point == T.A){A_check=true;}
		if ( this->edge_collection[i].first_Point == T.B |  this->edge_collection[i].second_Point == T.B){B_check=true;}
		if ( this->edge_collection[i].first_Point == T.C |  this->edge_collection[i].second_Point == T.C){C_check=true;}
	}
	if (A_check && B_check && C_check){all_check = true;}

	return all_check;
}
#endif
