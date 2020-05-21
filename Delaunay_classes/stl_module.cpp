#ifndef STL_MODULE
#define STL_MODULE

#include "./Point.hpp"
#include "./Triangle.hpp"
#include "stl_module.hpp"


bool del::Stl_module::operator == (del::Stl_module Module)
{
  return (this->Normal == Module.Normal && this-> Triangle == Module.Triangle);
}
#endif
