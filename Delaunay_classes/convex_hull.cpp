namespace del
{
    class Edge
    {

    public:
        Edge()
        {
            this->really_a_convex_hull_member = false;
        }
        ~Edge();

        del::Point first_Point;
        del::Point second_Point;

        bool really_a_convex_hull_member;


    };




    class convex_hull
    {
  
    public:
        convex_hull(/* args */);
        ~convex_hull();

        std::vector< del::Edge > edge_collection;

    };

} // namespace del
