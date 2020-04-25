#include "Point.hpp"

namespace del 
{

class Triangle 
{
    private:
        /* data */
    public:
        Point A; 
        Point B;
        Point C;

        Triangle ( Point A, Point B, Point C ) ;

        bool contem ( Point P );

        bool edge_sharing ( Triangle T );

        void swap (); //Austauscht die Orientierung einer Kante 
        
        bool operator == ( Triangle T ); //Gleichwertigkeit zwischen zwei Delaunay Dreiecke 

        Triangle same_curl ( Triangle T ); //ACHTUNG1! T muss schon ein orientierte Dreieck sein 

        Point Normal ();

};

}; // end of namespace