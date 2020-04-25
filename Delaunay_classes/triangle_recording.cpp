#include "Point.hpp"

namespace del 
{

class triangle_Delaunay 
{
    private:
        /* data */
    public:
        del::Point A; 
        del::Point B;
        del::Point C;

        triangle_Delaunay ( del::Point A, del::Point B, del::Point C ) 
        {
            this->A = A;
            this->B = B;
            this->C = C;
        }


        
        bool contem ( del::Point P )
        {
            return ( P == this->A || P == this->B || P == this->C );
        }

        bool edge_sharing ( triangle_Delaunay T )
        {
            return (
                ( this->contem(T.A) && this->contem(T.B) )
                ||
                ( this->contem(T.A) && this->contem(T.C) )
                ||
                ( this->contem(T.B) && this->contem(T.C) )
            );
        }

        void swap () //Austauscht die Orientierung einer Kante 
        {
            del::Point P = this->A;
            this->A = this->B;
            this->B = P;
        }
        
        bool operator == ( triangle_Delaunay T ) //Gleichwertigkeit zwischen zwei Delaunay Dreiecke 
        {
            return (
                ( ( this->A == T.A ) && ( this->B == T.B ) && ( this->C == T.C ) )
                ||
                ( ( this->A == T.B ) && ( this->B == T.C ) && ( this->C == T.A ) )
                ||
                ( ( this->A == T.C ) && ( this->B == T.A ) && ( this->C == T.B ) )
            );
        }

        triangle_Delaunay same_curl ( triangle_Delaunay T ) //ACHTUNG1! T muss schon ein orientierte Dreieck sein 
        {                                       //um diese Funktion richtig funktioniert.
            if (
                ( this->A == T.B ) && ( this->B == T.A )           //ACHTUNG2: T muss auch ein Dreieck sein 
                ||
                ( this->A == T.A ) && ( this->B == T.C )          //der mit der anderer Dreieck eine gemeine Kante hat.
                ||
                ( this->A == T.C ) && ( this->B == T.B )
            )
            {
                triangle_Delaunay tr ( this->A, this->B, this->C );
                return this; 
            }
            else
            {
                this->swap();
                return this;
            }
        }

        del::Point Normal ()
        {
            del::Point X = this->B - this->A;
            del::Point Y = this->C - this->A;
            
            float N[3] = (  X.p[1]*Y.p[2]-X.p[2]*Y.p[1] , //N é calculado como o produto vetorial X x Y normalizado
                            X.p[2]*Y.p[0]-X.p[0]*Y.p[2] ,
                            X.p[0]*Y.p[1]-X.p[1]*Y.p[0]
                            );
            float norm = sqqrt(pow(N[0],2)+pow(N[1],2)+pow(N[2],2));
            //normalização de N:
            N[0]=N[0]/norm;
            N[1]=N[1]/norm;
            N[2]=N[2]/norm;

            del::Point NORMAL;
            NORMAL.p[0]=N[0];
            NORMAL.p[1]=N[1];
            NORMAL.p[2]=N[2];

            return NORMAL;

        }



};

triangle_Delaunay::triangle_Delaunay(/* args */)
{
}

triangle_Delaunay::~triangle_Delaunay()
{
}


class stl_module
{
    private:
        /* data */
    public:
        stl_module(/* args */);
        ~stl_module();

        del::Point Normal;
        del::triangle_Delaunay Triangle;
        
};
    
stl_module::stl_module(/* args */)
{
}

stl_module::~stl_module()
{
}
    



}; // end of namespace