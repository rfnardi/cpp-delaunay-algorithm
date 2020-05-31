#include <iostream>

int main ()
{
    int* b = new int[ 2 ];

    for ( int i = 0; i < 3; i++ )
    {
        b[ i ] = i;
    }
    printf( "values: (%i,%i)\n", *b, *(b + 1) );

    delete[] b;
    return 0;
}