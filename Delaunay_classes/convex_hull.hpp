#include "Point.hpp" 
#include <vector>

namespace del
{
    class Edge
    {
        public:
        Edge();
        
        ~Edge();

        del::Point first_point;
        del::Point second_point;
        
        bool really_a_convex_hull_member;


    };
    
        
    
    class Convex_hull
    {
    
    public:
        Convex_hull(/* args */);
        ~Convex_hull();

        std::vector< del::Edge > edge_collection;
        
    };
    
    
} // namespace del
