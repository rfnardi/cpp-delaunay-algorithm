#ifndef ATLAS
#define ATLAS
#include "./atlas.hpp"

del::Atlas::Atlas (){};

del::Atlas::Atlas (int number_of_points , int number_of_charts)
{
  this->ptr = (int*) malloc(sizeof(float)*number_of_points);
};

del::Atlas::~Atlas ()
{
  free(this->ptr);
  std::cout << "Atlas destruído com sucesso." << '\n';
};

#endif
