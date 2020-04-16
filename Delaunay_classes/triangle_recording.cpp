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
                    ||(A==T.A)&&(B == T.C)          //der mit der anderer Dreieck eine gemeine Kante hat.
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

            del::point Normal ()
            {
                del::point X = B - A;
                del::point Y = C - A;
                
                float N[3] = (  X.p[1]*Y.p[2]-X.p[2]*Y.p[1] , //N é calculado como um produto vetorial
                                X.p[2]*Y.p[0]-X.p[0]*Y.p[2] ,
                                X.p[0]*Y.p[1]-X.p[1]*Y.p[0]
                             );
                float norm = sqqrt(pow(N[0],2)+pow(N[1],2)+pow(N[2],2));
                //normalização de N:
                N[0]=N[0]/norm;
                N[1]=N[1]/norm;
                N[2]=N[2]/norm;

                del::point NORMAL;
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
        



};