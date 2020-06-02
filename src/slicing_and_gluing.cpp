#include "obter_catalogo_de_vizinhancas_vizinhos.cpp"
#include "Centro_Esfera_Aprox.cpp"
#include "Triangle_Building.cpp"
#include "triangle_recording.cpp"
#include "Convex_Hull.cpp"

namespace del {

    

    class slicing
    {
    private:
        /* data */
    public:
        slicing(/* args */);
        ~slicing();

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
    
    std::cout<<"x máximo: "<< x_max <<"x mínimo: "<< x_min << '\n';
    std::cout<<"y máximo: "<< y_max <<"y mínimo: "<< y_min << '\n';
    std::cout<<"z máximo: "<< z_max <<"z mínimo: "<< z_min << '\n';

    std::cout<<"Quantidade total de pontos: "<< currentLine << '\n';

    //aqui precisamos definir quantos pontos o programa deve pegar por vez. 200 pontos? ----->

    long number_of_slices = currentLine/200;

    float slice_depth = (z_max - z_min)/number_of_slices; //futuramente considerar fatiamento ao longo de outros eixos de acordo com as proporções do sólido

    long int slice_index = 0;

    for (slice_index = 0; slice_index < number_of_slices; slice_index++)
    {
        currentLine = 0;
        lineIterator;
        do {
            currentLine++;
            lineIterator = fscanf( file, "%E%E%E \n", &x, &y, &z );
            if (z<=(z_max - slice_index*slice_depth) && z<(z_max - (slice_index + 1)*slice_depth)) //fatiamento do processo de montagem das vizinhanças
            {
                pontos.push_back( {x, y, z} );
            }
            
            //aqui deve entrar praticamente todo o código do main !!!!!!!!!!!!!!!!!!!!!!!!!
            
            
            //------>  é preciso decidir a melhor estratégia de escrita dos módulos stl para economizar memória !!!!!!!!!!
            //escrever todos módulos stl no arquivo de saída 
            //esvaziar vetor de módulos stl

            
                

        } while ( lineIterator != EOF );
        /* code */
    }
    

    

    };//end class slicing

    slicing::slicing(/* args */)
    {
    }

    slicing::~slicing()
    {
    }




    class gluing
    {
    private:
        /* data */
    public:
        gluing(/* args */);
        ~gluing();

               
        //varrer obter_catalogo_de_vizinhancas de vizinhanças e apagar todas com exceção daquelas que tiverem pontos do convex hull:
        for (size_t VIZ = 0; VIZ < obter_catalogo_de_vizinhancas.size(); VIZ++)
        {
            for (size_t Convex_Hull_index = 0; Convex_Hull_index < del::Convex_Hull.edge_collection.size(); Convex_Hull_index++)
            {
                if (/*ponto do convex hull != primeiro ponto da vizinhança*/)
                {
                   obter_catalogo_de_vizinhancas.erase(VIZ); //apaga vizinhança do catálogo
                }
            }
                        
        }
        //fazer update das vizinhanças dos pontos do convex hull na nova região
        //colocar 'FALSE' em 'bool really_a_Convex_Hull_member' de todos os edges que tiverem pontos cujas vizinhanças sofreram atualização
        //monta todas as outras vizinhanças de pontos na nova região
        //vizinhanças que receberem novos pontos vizinhos (isto é, que sofreram atualização) devem ser ponto de partida para triangulação da região

    };//end of class gluing
    
    gluing::gluing(/* args */)
    {
    }
    
    gluing::~gluing()
    {
    }
    
}; //end namespace del