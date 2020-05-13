#include "Point.hpp" 
#include <vector>

namespace del
{
    class Edge
    {
    private:
        /* data */
    public:
        Edge(/* args */);
        {
            this->really_a_convex_hull_member = false;
        }
        ~Edge();

        del::Point first_point;
        del::Point second_point;
        
        bool really_a_convex_hull_member;


    };
    
        
    
    class Convex_hull
    {
    private:
        /* data */
    public:
        Convex_hull(/* args */);
        ~Convex_hull();

        std::vector< del::Edge > edge_collection;
        
    };
    
    
} // namespace del
