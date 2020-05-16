#ifndef TRIANGLE_RECORD_H
#define TRIANGLE_RECORD_H



namespace del
{

    class Triangle
    {

    public:
        Triangle(); //constructor
        ~Triangle(); //destructor

        del::Point A;
        del::Point B;
        del::Point C;


        bool contem (del::Point P);


        bool edge_sharing (del::Triangle T);

        void swap (); //Austauscht die Orientierung einer Kante


        bool operator == (del::Triangle T); //Gleichwertigkeit zwischen zwei Delaunay Dreiecke


        del::Triangle same_curl (del::Triangle T ); //ACHTUNG1! T muss schon ein orientierte Dreieck sein


        del::Point Normal ();


    };



    class stl_module
    {

    public:
        stl_module(); //constructor
        ~stl_module(); //destructor

        del::Point Normal;
        del::Triangle triangle;

    };



}; //end namespace
#endif
