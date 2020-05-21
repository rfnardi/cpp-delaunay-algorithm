#ifndef STL_MODULE_H
#define STL_MODULE_H

#include "./Point.hpp"
#include "./Triangle.hpp"

namespace del
{

        class Stl_module
        {

        public:
            //Stl_module();
            //~Stl_module();

            del::Point Normal;
            del::Triangle Triangle;

            bool operator == (del::Stl_module);
        };
};
#endif
