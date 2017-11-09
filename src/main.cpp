#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#include "matrix.hpp"
#include "graph.hpp"
#include "object_graph.hpp"
#include "graphs.h"

using uint = unsigned int;

int main()
{
  std::string filename { "res/test.dot" };
  Graph g;
  g = g.FromDotFile(filename);

  filename = "res/oct.gio";
  
  g = g.FromGioFile(filename);
  g.ToGioFile("res/oct2.gio");
  
  Graph g1 = Graphs::Hexahedron();
  Graph g2 = Graphs::Tetrahedron();
  Graph g3 = Graphs::Octahedron();
  Graph g4 = Graphs::Cube();

  std::vector<std::list<uint> > adjList = g1.AdjacencyList();
  std::vector<Vertex<float> > vertices = { Vertex<float>(0.1f), Vertex<float>(0.5f) };
  ObjectGraph<float> og(vertices, adjList);

  std::list<Graph*> l { &g1, &g2, &g3, &g4 };

  for (auto gp : l) {
    Matrix<uint> m = gp->AdjacencyMatrix();
    std::cout << "\n m = " << "\n";
    m.show();
    std::cout << "\n m^2 = " << "\n";
    (m * m).show();
    std::cout << "\nvertices = " << g.vertices()
    	      << ", edges = " << g.edges() << "\n\n";
    
    std::cout << "Symmetric? : "
  	      << (m.isSymmetric() ? "symmetric" : "not")
  	      << " Antisymmetric? : "
  	      << (m.isAntiSymmetric() ? "antisymmetric" : "not")
  	      << std::endl;
  }

  Matrix<int> m({ 1, 2, 3 });
  
  m.show();

  return 0;
}
