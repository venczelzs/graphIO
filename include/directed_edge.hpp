#ifndef DIRECTED_EDGE
#define DIRECTED_EDGE

#include "edge.hpp"
#include "vertex.hpp"

template<typename T> class DirectedEdge : public Edge<T>
{
private:
  Vertex<T>* _start, _end;
  DirectedEdge() {}
  bool _isDirected;
  
public:
  DirectedEdge(Vertex<T>* start, Vertex<T>* end) :
    _isDirected(true),
    _start(start),
    _end(end) {
  }
};

#endif // DIRECTED_EDGE
