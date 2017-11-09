#ifndef OBJECT_GRAPH_HPP
#define OBJECT_GRAPH_HPP

#include <vector>

#include "edge.hpp"
#include "graph.hpp"

template<typename T> class ObjectGraph : public Graph
{
private:
  std::vector<Vertex<T> > _vertices;

public:
  ObjectGraph(std::vector<Vertex<T> > vertices, std::vector<std::list<uint> > adjacencyList) :
    Graph(adjacencyList),
    _vertices(vertices) {
  }

  ObjectGraph(std::vector<Vertex<T> > vertices, Matrix<uint> adjacencyMatrix) :
    Graph(adjacencyMatrix),
    _vertices(vertices) {
  }
};

#endif // OBJECT_GRAPH_HPP
