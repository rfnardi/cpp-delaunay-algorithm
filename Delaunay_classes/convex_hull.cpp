namespace del
{
    class edge
    {
    private:
        /* data */
    public:
        edge(/* args */);
        {
            this->really_a_convex_hull_member = false;
        }
        ~edge();

        del::Point first_Point;
        del::Point second_Point;
        
        bool really_a_convex_hull_member;


    };
    
    edge::edge(/* args */)
    {
    }
    
    edge::~edge()
    {
    }
    
    
    class convex_hull
    {
    private:
        /* data */
    public:
        convex_hull(/* args */);
        ~convex_hull();

        std::vector< del::edge > edge_collection;
        
    };
    
    convex_hull::convex_hull(/* args */)
    {
    }
    
    convex_hull::~convex_hull()
    {
    }
    
} // namespace del
