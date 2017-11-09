#include "graphs.h"

Graph Graphs::Tetrahedron() {
  Matrix<uint> m { 4, 4,
      { 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0 } };
  return Graph(m);
}

Graph Graphs::Octahedron() {
  Matrix<uint> m(6, 6);
  for (uint  i = 1; i <= 5; i++) {
    for (uint j = i + 1; j <= 6; j++) {
      if ((i + j) % 6 != 1)
	m.get(i, j) = m.get(j, i) = 1;
    }
  }
  return Graph(m);
}

Graph Graphs::Hexahedron() {
  Matrix<uint> m(8, 8);
  for (uint u = 1; u <= 4; u++) {
    m.get(u, u % 4 + 1) = 1;
    m.get(u % 4 + 1, u) = 1;
    m.get(u + 4, u % 4 + 5) = 1;
    m.get(u % 4 + 5, u + 4) = 1;
    m.get(u, u + 4) = 1;
    m.get(u + 4, u) = 1;
  }
  return Graph(m);
}

Graph Graphs::Cube() {
  return Hexahedron();
}

Graph Graphs::Icosahedron() {
  // TODO
  return Graph();
}

Graph Graphs::Dodekahedron() {
  // TODO
  return Graph();
}
