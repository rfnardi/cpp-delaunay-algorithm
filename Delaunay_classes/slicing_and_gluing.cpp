#include "catalogo_vizinhos.cpp"
#include "Centro_Esfera_Aprox.cpp"
#include "triangle_building.cpp"
#include "triangle_recording.cpp"
#include "convex_hull.cpp"

namespace del {

    

    class slicing_and_gluing
    {
    private:
        /* data */
    public:
        slicing_and_gluing(/* args */);
        ~slicing_and_gluing();

    //tomando dimensões do sólido para efetuar fatiamento:
    // URL fonte desta forma de leitura de arquivo - https://stackoverflow.com/a/11168756/5382576
	float x, y, z;
    float x_min, x_max, y_min, y_max, z_min, z_max;
	
	int currentLine = 0;
	int lineIterator;
	do {
		currentLine++;
		lineIterator = fscanf( file, "%E%E%E \n", &x, &y, &z );
		if(x<x_min)
        {
            x_min = x;
        }
        if(x>x_max)
        {
            x_max = x;
        }
        if(y<y_min)
        {
            y_min = y;
        }
        if(y>y_max)
        {
            y_max = y;
        }
        if(z<z_min)
        {
            z_min = z;
        }
        if(z>z_max)
        {
            z_max = z;
        }
               

	} while ( lineIterator != EOF );

    std::cout<<"Dimensões do sólido: \n";
    

    };//end class slicing_and_gluing

    slicing_and_gluing::slicing_and_gluing(/* args */)
    {
    }

    slicing_and_gluing::~slicing_and_gluing()
    {
    }


}; //end namespace del