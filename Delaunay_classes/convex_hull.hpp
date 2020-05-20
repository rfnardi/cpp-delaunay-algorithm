#ifndef CONVEX_HULL
#define CONVEX_HULL

#include "./Point.hpp"


namespace del
{
    class Edge
    {

    public:
        Edge()
        {
            this->really_a_Convex_Hull_member = false;
        }
        ~Edge();

        del::Point first_Point;
        del::Point second_Point;

        bool really_a_Convex_Hull_member;


    };




    class Convex_Hull
    {

    public:
        Convex_Hull(/* args */);
        ~Convex_Hull();

        std::vector< del::Edge > edge_collection;

    };

} // namespace del
#endif
