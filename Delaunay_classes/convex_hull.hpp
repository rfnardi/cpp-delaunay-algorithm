#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "./Point.hpp"
#include <vector>


namespace del
{
    class Edge
    {

    public:
        Edge();

        //~Edge();

        del::Point first_Point;
        del::Point second_Point;

        bool really_a_Convex_Hull_member;


    };




    class Convex_Hull
    {

    public:
        Convex_Hull();
        //~Convex_Hull();

        std::vector< del::Edge > edge_collection;

    };

} // namespace del
#endif
