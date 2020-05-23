#ifndef ATLAS_H
#define ATLAS_H

namespace del
{
  class Chart
  {

  public:
    Chart (int);
    ~Chart ();
    int Chart_index;
    std::vector<bool> Chart_connections; // Este vetor serve para dizer com quais outras cartas a presente carta possui fronteira
    std::vector<float[3]> Points;
  };

}
#endif
