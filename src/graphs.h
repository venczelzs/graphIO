#ifndef GRAPHS_H
#define GRAPHS_H

#include "graph.hpp"
#include "matrix.hpp"

class Graphs
{
public:
  static Graph Tetrahedron();

  static Graph Octahedron();

  static Graph Hexahedron();

  static Graph Cube();

  static Graph Icosahedron();

  static Graph Dodekahedron();
};

#endif // GRAPHS_H
