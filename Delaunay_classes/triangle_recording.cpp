namespace del {

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

    std::vector< del::triangle_Delaunay> Triangulacao; //armazena todos os triangulos de Delaunay

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
    void swap ( A , B) //troca a orientação de uma aresta 
    {
        del::point P = A;
        A = B;
        B = P;
    }
    bool operator == (triangle_Delaunay T) //equivalencia entre triangulos de Delaunay
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

};

triangle_Delaunay::triangle_Delaunay(/* args */)
{
}

triangle_Delaunay::~triangle_Delaunay()
{
}



};