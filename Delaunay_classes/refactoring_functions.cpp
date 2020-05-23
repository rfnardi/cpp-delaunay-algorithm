#ifndef REFACTORING_FUNCTIONS
#define REFACTORING_FUNCTIONS

#include "./Point.hpp"
#include "./refactoring_functions.hpp"
#include <vector>


//encontra no catálogo a vizinhança cujo primeiro ponto é igual ao fornecido
int refac::find_neighboorhood_in_neithboorhoodsbook(del::Point A , del::Point Point_in_Book)
{
  long unsigned int VIZ;
  std::vector<std::vector<del::Point> Book;
  for (size_t k = 0; k < Book.size(); k++)
  {
    del::Point P = Book[k][0];

    if (A == P)
    {
      VIZ = k;
    }

  return VIZ;
  }
};

#endif
