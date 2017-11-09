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

  /* FIELDS */

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

  /* CONSTRUCTORS */

  /// Default constructor.
  ///
  ///
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

  /// Constructor.
  /// Sets only the number of vertices and edges.
  ///
  Graph(uint vertices, uint edges) :
    _vertexCount(vertices),
    _edgeCount(edges),
    _isDirected(false),
    _isVertexCountSet(true),
    _isEdgeCountSet(true),
    _isIncMatSet(false),
    _isAdjMatSet(false),
    _isAdjListSet(false) {
  }

  /// Constructor.
  /// Takes an adjacency list, sets it for the graph and sets the number of vertices.
  ///
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
  }

  /// Constructor.
  ///
  ///
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

  /* METHODS */

  /* Methods for constructing graphs from input files. */

  Graph& FromDotFile(const std::string& filename) {

    // This parser function assumes the syntax is correct.
    // In the future a syntax check function must be implemented
    // and called before calling this function.

    std::ifstream ifs { filename };

    std::vector<std::list<uint> > adjacencyList;

    try {
      std::string line;
      
      while (std::getline(ifs, line)) {

	size_t comment_pos = line.find("//"); // If the line has a comment in it
	                                      // truncate the line to the part
	if (comment_pos != -1)                // before the comment.
	  line = line.substr(0, comment_pos); //

	std::string ws = " \t\n\v\f\r";       // white space characters
	
	if (line.find_first_not_of(ws) == -1) // If the line only has white space
	  continue;                           // skip it.

	std::string graph_name;

	auto graphTokenPos = line.find("graph");

	std::cout << line << "\n";

      }

    }
    catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }

    return *this;
  }

  Graph& FromGioFile(const std::string& filename) {
    std::ifstream ifs { filename };
    std::vector<std::list<uint> > adjacencyList;
    uint vertex {};
    uint edgesTimes2 {};
    try {
      std::string s;
      while (std::getline(ifs, s)) {
	vertex++;
	std::list<uint> neighbours;
	
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

  /* Methods for saving graph objects to text files. */

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

  /* Properties. */

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

  /// Virtual destructor.
  ///
  ///
  virtual ~Graph() {}

private:

  /* Private methods to calculate and set the fields of the given graph object.  */

  /// This method returns the adjacency list of the graph object.
  ///
  ///
  std::vector<std::list<uint> >& AdjMatToAdjList() {
    if (_isAdjListSet)
      return _adjacencyList;
    else
      return AdjMatToAdjList(_adjacencyMatrix);
  }

  /// This method converts an arbitrary adjacency matrix to an adjacency list.
  ///
  ///
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

  ///
  ///
  ///
  Matrix<uint>& AdjListToAdjMatrix() {
    if (_isAdjMatSet)
      return _adjacencyMatrix;
    else
      return AdjListToAdjMatrix(_adjacencyList);
  }

  ///
  ///
  ///
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

// std::list<std::string> split(const std::string& s, char delim) {
//   std::list<std::string> res;
//   auto delim_pos = s.find(delim);
//   res.push_back(s.substr(0, delim_pos));

//   res.splice(res);
  
//   return res;
// }

#endif // GRAPH_HPP
