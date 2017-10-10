#include <iostream>
#include <fstream>
#include <string>

#include "matrix.hpp"
#include "graph.hpp"

using uint = unsigned int;

int main()
{
  // std::string filename { "./oct.gio" };
  // Graph g;
  // g = g.FromGioFile(filename);

  Graph g1 = Graphs::Hexahedron();
  Graph g2 = Graphs::Tetrahedron();
  Graph g3 = Graphs::Octahedron();
  Graph g4 = Graphs::Icosahedron();
  
  std::list<Graph> l { g1, g2, g3, g4 };

  for (auto g : l) {
    Matrix<uint> m = g.AdjacencyMatrix();
    // std::cout << "\n m = " << "\n";
    // m.show();
    // std::cout << "\n m^2 = " << "\n";
    // (m * m).show();
    // std::cout << "\nvertices = " << g.vertices()
    // 	      << ", edges = " << g.edges() << "\n\n";
    
    std::cout << "Symmetric? : "
	      << (m.isSymmetric() ? "symmetric" : "not")
	      << " Antisymmetric? : "
	      << (m.isAntiSymmetric() ? "antisymmetric" : "not")
	      << std::endl;
  }

  // Matrix<int> m({ 1, 2, 3 });

  // m = m ^ 4;
  
  // m.show();

  return 0;
}
