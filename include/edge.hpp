#ifndef EDGE_HPP
#define EDGE_HPP

#include "vertex.hpp"

template<typename T> class Edge
{
private:
  Vertex<T>* _v1, _v2;
  Edge() {}

protected:
  bool _isDirected;
  
public:
  Edge(Vertex<T>* v1, Vertex<T>* v2) :
    _isDirected(false),
    _v1(v1),
    _v2(v2) {
  }

  virtual ~Edge() {}
};

#endif // EDGE_HPP
