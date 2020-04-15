namespace del 
{

        class triangle_Delaunay 
        {
        private:
            /* data */
        public:
            triangle_Delaunay(/* args */);
            ~triangle_Delaunay();

            del::point A; 
            del::point B;
            del::point C;

            std::vector< del::triangle_Delaunay> Triangulation; //Speichert alle Delaunay Dreiecke

            bool contem (point P)
            {
                if (P==A || P==B || P==C)
                {
                    return true;
                }
                else
                {
                    return false;
                }       
            }

            bool edge_sharing (triangle_Delaunay T)
            {
                if (    (contem(T.A)&&contem(T.B))
                        ||(contem(T.A)&&contem(T.C))
                        ||(contem(T.B)&&contem(T.C))
                    )
                {
                    return true;
                }
                else
                {
                    return false;
                }
                
                
            }
            void swap () //Austauscht die Orientierung einer Kante 
            {
                del::point P = A;
                A = B;
                B = P;
            }
            
            bool operator == (triangle_Delaunay T) //Gleichwertigkeit zwischen zwei Delaunay Dreiecke 
            {

                if (   ((A == T.A) && (B == T.B) && (C == T.C))
                    || ((A == T.B) && (B == T.C) && (C == T.A))
                    || ((A == T.C) && (B == T.A) && (C == T.B))
                    )
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            bool same_curl (triangle_Delaunay T ) //ACHTUNG1! T muss schon ein orientierte Dreieck sein 
            {                                       //um diese Funktion richtig funktioniert.
                if ( (A==T.B)&&(B == T.A)           //ACHTUNG2: T muss auch ein Dreieck sein 
                    ||(A==T.A)&&(B == T.C)         //der mit der anderer Dreieck ein gemeine Kante hat.
                    ||(A==T.C)&&(B == T.B)
                    )
                {
                    return true;
                }
                else
                {
                    swap();
                    return true;
                }
                
            }



        };

        triangle_Delaunay::triangle_Delaunay(/* args */)
        {
        }

        triangle_Delaunay::~triangle_Delaunay()
        {
        }



};