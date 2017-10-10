#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <set>

#include "matrix.hpp"

using uint = unsigned int;

class Graph
{
protected:
  
  std::vector<std::list<uint> > _adjacencyList;
  Matrix<uint> _adjacencyMatrix,
    _incidenceMatrix;
  uint _vertexCount,
    _edgeCount;
  bool _isDirected,
    _isAdjMatSet,
    _isAdjListSet,
    _isIncMatSet,
    _isEdgeCountSet,
    _isVertexCountSet;
  std::string _name, _info;

public:
  
  explicit Graph() :
    _vertexCount(-1),
    _edgeCount(-1),
    _isDirected(false),
    _isIncMatSet(false),
    _isAdjMatSet(false),
    _isAdjListSet(false),
    _isEdgeCountSet(false),
    _isVertexCountSet(false) {
    std::cout << "default" << "\n";
  }

  Graph(uint vertices, uint edges) :
    _vertexCount(vertices),
    _edgeCount(edges),
    _isDirected(false),
    _isVertexCountSet(true),
    _isEdgeCountSet(true),
    _isIncMatSet(false),
    _isAdjMatSet(false),
    _isAdjListSet(false) {
    std::cout << "(v, e)" << "\n";
  }
  
  Graph(std::vector<std::list<uint> > adjList) :
    _adjacencyList(adjList),
    _vertexCount(adjList.size()),
    _edgeCount(-1),
    _isDirected(false),
    _isVertexCountSet(true),
    _isEdgeCountSet(false),
    _isIncMatSet(false),
    _isAdjMatSet(false),
    _isAdjListSet(true) {
    std::cout << "list" << "\n";
  }

  Graph(Matrix<uint>& adjMatrix) :
    _adjacencyMatrix(adjMatrix),
    _vertexCount(adjMatrix.rows()),
    _edgeCount(-1),
    _isDirected(false),
    _isEdgeCountSet(false),
    _isVertexCountSet(true),
    _isAdjMatSet(true),
    _isIncMatSet(false),
    _isAdjListSet(false) {
  }

  Graph& FromDotFile(const std::string& filename) {
    // TODO
    return *this;
  }

  Graph& FromGioFile(const std::string& filename) {
    std::ifstream ifs { filename };
    std::vector<std::list<uint> > adjacencyList;
    uint vertex {};
    uint edgesTimes2 {};
    try {
      std::string s {};
      while (!ifs.eof()) {
	vertex++;
	std::list<uint> neighbours;
	std::getline(ifs, s);
	uint pos1 {0}, pos2 {0};
	for (char c : s) {
	  pos2++;
	  if (c == ' ') {
	    pos1 = pos2;
	  }
	  else if (c == ',' || c == ';') {
	    try {
	      neighbours.push_back(std::stoi(s.substr(pos1, pos2 - pos1 - 1)));
	      edgesTimes2++;
	    }
	    catch (std::exception& e) { break; }
	  }
	}
	if (neighbours.size())
	  adjacencyList.push_back(neighbours);
      }
    }
    catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
    ifs.close();
    _vertexCount = vertex - 1;
    _edgeCount = edgesTimes2 / 2;
    _adjacencyList = adjacencyList;
    _isAdjListSet = true;
    return *this;
  }

  void ToDotFile(const std::string path) {
    // TODO
  }
  
  void ToGioFile(const std::string path) {
    std::vector<std::list<uint> >& a = _adjacencyList;
    std::ofstream ofs { path };
    for (uint i = 0; i < a.size(); i++) {
      uint j = 0;
      ofs << (i + 1) << ": ";
      std::list<uint>& l = a.at(i);
      for (uint u : l) {
	ofs << u << (++j == l.size() ? ";\n" : ", ");
      }
    }
    ofs.close();
  }

  uint edges() {
    if (_isEdgeCountSet)
      return _edgeCount;
    else {
      uint edgeCount = 0;
      for (auto l : AdjacencyList()) {
	for (auto u : l) {
	  edgeCount++;
	}
      }
      _edgeCount = edgeCount / 2;
      _isEdgeCountSet = true;
      return _edgeCount;
    }
  }

  uint vertices() {
    if (_isVertexCountSet)
      return _vertexCount;
    else {
      _vertexCount = AdjacencyList().size();
      _isVertexCountSet = true;
      return _vertexCount;
    }
  }

  Matrix<uint>& AdjacencyMatrix() {
    try {
      if (_isAdjMatSet)
	return _adjacencyMatrix;
      else if (_isAdjListSet)
	return AdjListToAdjMatrix();
      else
	throw std::exception {};
    }
    catch (std::exception& e) {
      std::cout << "Could not return adjacency matrix. " 
		<< "Neither of adjacency matrix and adjacency list is set.\n";
    }  
  }

  std::vector<std::list<uint> >& AdjacencyList() {
    try {
      if (_isAdjListSet)
	return _adjacencyList;
      else if (_isAdjMatSet)
	return AdjMatToAdjList();
      else
	throw std::exception {};
    }
    catch (std::exception& e) {
      std::cout << "Could not return adjacency list. "
		<< "Neither of adjacency matrix and adjacency list is set.\n";
    }
  }
  
  virtual ~Graph() {}

private:

  std::vector<std::list<uint> >& AdjMatToAdjList() {
    if (_isAdjListSet)
      return _adjacencyList;
    else
      return AdjMatToAdjList(_adjacencyMatrix);
  }

  std::vector<std::list<uint> >& AdjMatToAdjList(Matrix<uint>& adjMat) {
    std::vector<std::list<uint> > adjList {};
    for (uint u = 1; u <= adjMat.rows(); u++) {
      std::list<uint> neighbours {};
      for (uint v = 1; v <= adjMat.collumns(); v++) {
	if (adjMat.get(u, v) == 1)
	  neighbours.push_back(v);
      }
      adjList.push_back(neighbours);
    }
    _adjacencyList = adjList;
    return _adjacencyList;
  }

  Matrix<uint>& AdjListToAdjMatrix() {
    if (_isAdjMatSet)
      return _adjacencyMatrix;
    else
      return AdjListToAdjMatrix(_adjacencyList);
  }

  Matrix<uint>& AdjListToAdjMatrix(const std::vector<std::list<uint> >& adjList) {
    uint dim = adjList.size();
    Matrix<uint> adjMat { dim, dim, {} };
    for (uint i = 1; i <= adjList.size(); i++) {
      for (uint u : adjList.at(i - 1)) {
	adjMat.get(i, u) = 1;
      }
    }
    _adjacencyMatrix = adjMat;
    return _adjacencyMatrix;
  }
};

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

template<typename T> class ObjectGraph : public Graph
{
private:
  std::vector<Vertex<T> > _vertices;

public:
  ObjectGraph(std::vector<Vertex<T> > vertices, std::vector<uint> adjacencyList) :
    Graph(adjacencyList),
    _vertices(vertices) {
  }

  ObjectGraph(std::vector<Vertex<T> > vertices, Matrix<uint> adjacencyMatrix) :
    Graph(adjacencyMatrix),
    _vertices(vertices) {
  }
};

class Graphs
{
public:
  static Graph Tetrahedron() {
    Matrix<uint> m { 4, 4,
	{ 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0 } };
    return Graph(m);
  }

  static Graph Octahedron() {
    Matrix<uint> m(6, 6);
    for (uint  i = 1; i <= 5; i++) {
      for (uint j = i + 1; j <= 6; j++) {
	if ((i + j) % 6 != 1)
	  m.get(i, j) = m.get(j, i) = 1;
      }
    }
    return Graph(m);
  }

  static Graph Hexahedron() {
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

  static Graph Cube() {
    return Hexahedron();
  }

  static Graph Icosahedron() {            // TODO doesn't work
    Matrix<uint> m(12, 12);
    for (uint u = 1; u <= 5; u++) {
      m.get(1, u + 1) = 1;                // rays from south pole
      m.get(u + 1, 1) = 1;                // --symmetry
      m.get(12, u + 6) = 1;               // rays from north pole
      m.get(u + 6, 12) = 1;               // --same
      m.get(u + 1, (u + 1) % 5 + 1) = 1;  // circle on tropic of capricorn
      m.get((u + 1) % 5 + 1, u + 1) = 1;  // --same
      m.get(u + 6, (u + 1) % 5 + 6) = 1;  // circle on tropic of cancer
      m.get((u + 1) % 5 + 6, u + 6) = 1;  //
      m.get(u + 1, u + 6) = 1;            // 5 edges across the equator
      m.get(u + 6, u + 1) = 1;            //
      m.get(u + 1, u % 5 + 7) = 1;        // other 5 edges across the
      m.get(u % 5 + 7, u + 1) = 1;        // equator
    }
    return Graph(m);
  }
};

#endif // GRAPH_HPP
