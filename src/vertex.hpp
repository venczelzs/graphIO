#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <set>

template<typename T> class Vertex
{
private:
  T _node;
  std::set<Vertex<T>* > _neighbours;

public:
  explicit Vertex() : _neighbours({}) {}
  Vertex(T node) : _node(node), _neighbours({}) {}
  ~Vertex() {
    for (auto p : _neighbours)
      delete p;
  }
};

#endif // VERTEX_HPP
