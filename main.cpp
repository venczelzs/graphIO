#include <iostream>
#include <fstream>
#include <string>

#include "matrix.hpp"
#include "graph.hpp"

using uint = unsigned int;

static Graph FromDotFile(const std::string& filename) {
  std::ifstream ifs { filename };
  std::vector<std::list<uint> > adjacencyList;
  uint vertex {0};
  try {
    std::string line {};
    while (!ifs.eof()) {
      std::getline(ifs, line);

      bool shouldContinue = true;

      for (uint u = 0; shouldContinue && u < line.size(); u++) {

	if (line.at(u) == ' ')
	  u++;
	
	if (line.substr(u, 2) == "//") {
	  shouldContinue = false;
	  std::cout << "this is a comment\n";
	}

	if (line.at(u) == 'g') {
	  
	  if (line.substr(u, 6) == "graph ") {
	    std::cout << "this is a graph" << "\n";
	    u += 6;
	    if (line.at(u) != '{') {
	      std::cout << "it has a name, ";

	      uint v = 1;

	      while (line.at(u + v) != '{') {
		v++;
	      }
	      std::string name = line.substr(u, v - 1);
	      std::cout << "it is " << name << ".\n";
	    }
	    else { // line.at(u+1) == '{'
	      std::cout << "it has not got a name." << "\n";
	    }
	  }
	}
      }
    }
    return Graph();
  }
  catch (std::exception& e) {
    std::cout << e.what() << "(FromDotFile() error)\n";
  }
  ifs.close();
  adjacencyList.push_back({1});
  return Graph(adjacencyList);
}

int main()
{
  std::string filename { "graph1.dot" };
  Graph g = FromDotFile(filename);

  // std::string filename { "./oct.gio" };
  // Graph g = Graphs::FromGioFile(filename);
  // g.ToGioFile("./oct2.gio");
  
  // Graph g1 = Graphs::Hexahedron();
  // Graph g2 = Graphs::Tetrahedron();
  // Graph g3 = Graphs::Octahedron();
  // Graph g4 = Graphs::Icosahedron();
  
  // std::list<Graph> l { g1, g2, g3, g4 };

  // for (auto g : l) {
  //   Matrix<uint> m = g.AdjacencyMatrix();
  //   // std::cout << "\n m = " << "\n";
  //   // m.show();
  //   // std::cout << "\n m^2 = " << "\n";
  //   // (m * m).show();
  //   // std::cout << "\nvertices = " << g.vertices()
  //   // 	      << ", edges = " << g.edges() << "\n\n";
    
  //   std::cout << "Symmetric? : "
  // 	      << (m.isSymmetric() ? "symmetric" : "not")
  // 	      << " Antisymmetric? : "
  // 	      << (m.isAntiSymmetric() ? "antisymmetric" : "not")
  // 	      << std::endl;
  // }

  // Matrix<int> m({ 1, 2, 3 });

  // m = m ^ 4;
  
  // m.show();

  return 0;
}
