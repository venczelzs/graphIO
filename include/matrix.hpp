#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <cmath>

namespace Matrica {

  template<typename T> class Matrix
  {
  private:

    // Fields

    std::vector<T> _entries;
    uint _rows, _collumns;
    T _determinant;
    bool _isDetSet;;
  
  public:

    // Constructors

    explicit Matrix();
    Matrix(uint m, uint n, std::vector<T> elements);
    Matrix(uint m, uint n);
    Matrix(std::vector<T> diagElements);
  
    // Getters / setters (properties)
    uint rows();
    uint collumns();
    T& get(uint i, uint j);
    bool isSymmetric();
    bool isAntiSymmetric();
  
    // other
    void show();

    // operators
    bool operator == (Matrix<T>& rhs) {
      bool result = true;
      for (uint i = 1; i <= _rows; i++) {
	for (uint k = 1; k <= rhs.collumns(); k++) {
	  result = result && get(i, k) == rhs.get(i, k);
	}
      }
      return result;
    }

    Matrix<T> operator + (Matrix<T>& rhs) {
      auto result = *this;
      for (uint i = 1; i <= _rows; i++) {
	for (uint k = 1; k <= rhs.collumns(); k++) {
	  result.get(i, k) += rhs.get(i, k);
	}
      }
      return result;
    }

    Matrix<T> operator - (Matrix<T>& rhs) {
      auto result = *this;
      for (uint i = 1; i <= _rows; i++) {
	for (uint k = 1; k <= rhs.collumns(); k++) {
	  result.get(i, k) -= rhs.get(i, k);
	}
      }
      return result;
    }

    Matrix<T> operator - () {
      Matrix<T> result = *this;
      for (uint i = 1; i <= _rows; i++) {
	for (uint k = 1; k <= _collumns; k++) {
	  result.get(i, k) = -result.get(i, k);
	}
      }
      return result;
    }

    Matrix<float> operator / (float divisor) {
      Matrix<float> result { _rows, _collumns };
      for (uint i = 1; i <= _rows; i++) {
	for (uint k = 1; k <= _collumns; k++) {
	  result.get(i, k) = static_cast<float>(get(i, k)) / divisor;
	}
      }
      return result;
    }

    Matrix<T> operator * (Matrix<T>& rhs) {
      try {
	if (collumns() == rhs.rows()) {
	  Matrix<T> result { _rows, rhs.collumns(), {} };
	  for (uint i = 1; i <= _rows; i++) {
	    for (uint k = 1; k <= rhs.collumns(); k++) {
	      T sum = 0;
	      for (uint j = 1; j <= _collumns; j++) {
		sum += get(i, j) * rhs.get(j, k);
	      }
	      result.get(i, k) = sum;
	    }
	  }
	  return result;
	}
	else 
	  throw std::exception {};
      }	
      catch (std::exception& e) {
	std::cout << "(operator * (Matrix<T>& rhs) error) wrong dimension\n";
      }
    }

    // Matrix<T> operator ^ (int exponent) {
    //   if (exponent > 0) {
    //     auto result = *this;
    //     auto square = result * result;
    //     if (exponent % 2 == 0) {
    // 	return square ^ (int)(((float)exponent) / 2.0f);
    //     }
    //     else {
    // 	result = result * square ^ (int)((((float)exponent) - 1) / 2.0f);
    // 	return result;
    //     }
    //   }
    //   else {
    //     return *this;
    //   }
    // }

    // Methods
    Matrix<T> Transpose();

    Matrix<T> SubMatrix(uint k, uint l) { // TODO not perfect
      Matrix<T> sub;
      try {
	if (_rows == _collumns && _rows) {
	  if (_rows > 1) {
	    sub = Matrix<T>(_rows - 1, _collumns - 1);
	    for (uint i = 1; i <= sub.rows(); i++) {
	      for (uint j = 1; j <= sub.collumns(); j++) {
		if (i < k) {
		  if (j < l) {
		    sub.get(i, j) = get(i, j);
		  }
		  else {
		    sub.get(i, j) = get(i, j + 1);
		  }
		}
		else {
		  if (j < l) {
		    sub.get(i, j) = get(i + 1, j);
		  }
		  else {
		    sub.get(i, j) = get(i + 1, j + 1);
		  }
		}
	      }
	    }	
	  }
	  else
	    return Matrix<T>(1, 1, { get(1, 1) });
	}
	else
	  throw std::exception {};
      }
      catch (std::exception& e) {
	std::cout << "(SubMatrix error) Matrix is not rectangular" << std::endl;
	sub = Matrix<T>(1, 1);
      }
      return sub;
    }
  
    T& determinant() {
      if (!_isDetSet)
	_determinant = det(*this);
      return _determinant;
    }

    Matrix<T> adjoint() {
      return adj(*this);
    }

    Matrix<float> inverse() {
      try {
	if (_rows == _collumns) {
	  try {
	    auto dtmnt = determinant();
	    if (dtmnt != 0) {
	      auto result = adjoint() / dtmnt;
	      return result;
	    }
	    else
	      throw std::exception {}; // TODO: custom exceptions
	  }   
	  catch (std::exception& e) {
	    std::cout << "(inverse() error) det = 0\n";
	  }
	}
	else
	  throw std::exception {};
      }
      catch (std::exception& e) {
	std::cout << "(inverse() error) matrix is not rectangulat\n";
      }
    }

    virtual ~Matrix() {}
  };

  template<typename T>
  Matrix<T>::Matrix() :
    _isDetSet(false) {
  }

  template<typename T>
  Matrix<T>::Matrix(uint m, uint n, std::vector<T> elements) :
    _rows(m),
    _collumns(n) {
    try {
      if (elements.size() != n * m)
	throw std::exception {};
      _entries = elements;
    }
    catch (std::exception& e) {
      for (uint u = 0; u < n * m; u++)
	_entries.push_back(0);
    }
  }

  template<typename T>
  Matrix<T>::Matrix(std::vector<T> diagElements) {
    size_t dim = diagElements.size();
    _rows = dim;
    _collumns = dim;
    for (uint u = 1; u <= dim; u++) {
      for (uint v = 1; v <= dim; v++) {
	if (u == v)
	  _entries.push_back(diagElements.at(u - 1));
	else
	  _entries.push_back(0);
      }
    }
  }

  template<typename T>
  Matrix<T>::Matrix(uint m, uint n) : Matrix(m, n, {}) {}

  // Getters / setters (properties)

  template<typename T>
  uint Matrix<T>::collumns() {
    return _collumns;
  }

  template<typename T>
  uint Matrix<T>::rows() {
    return _rows;
  }

  template<typename T>
  T& Matrix<T>::get(uint i, uint j) {
    return _entries.at((i - 1) * _collumns + (j - 1));
  }

  // other

  template<typename T>
  void Matrix<T>::show() {
    for (uint i = 1; i <= _rows; i++) {
      std::cout << "[ ";
      for (uint j = 1; j <= _collumns; j++) {
	std::cout << get(i, j) << (j != _collumns ? ", " : " ]\n");
      }
    }
  }

  // Methods
  template<typename T>
  Matrix<T> Matrix<T>::Transpose() {
    Matrix<T> result { _collumns, _rows };
    for (uint i = 1; i <= _rows; i++) {
      for (uint k = 1; k <= _collumns; k++) {
	result.get(k, i) = get(i, k);
      }
    }
    return result;
  }

  template<typename T>
  bool Matrix<T>::isSymmetric() {
    auto transpose = Transpose();
    if (*this == transpose)
      return true;
    else
      return false;
  }

  template<typename T>
  bool Matrix<T>::isAntiSymmetric() {
    auto minusTranspose = -Transpose();
    if (*this == minusTranspose)
      return true;
    else
      return false;    
  }


  // Non member functions:
  //
  // - adj (adjoint)
  // - det (determinant)

  template<typename T> Matrix<T> adj(Matrix<T>& m) {
    try {
      if (m.rows() == m.collumns()) {
	uint dim = m.rows();
	Matrix<T> adjM(dim, dim);
	for (uint i = 1; i <= dim; i++) {
	  for (uint j = 1; j <= dim; j++) {
	    auto sub = m.SubMatrix(j, i);
	    adjM.get(i, j) = std::pow(-1, i + j) * det(sub);
	  }
	}
	return adjM;
      }
      else
	throw std::exception {};
    }
    catch (std::exception& e) {
      std::cout << "(det(Matrix<T>& m) error) m is not rectangular\n";
    }
  }

  template<typename T> T det(Matrix<T>& m) {
    try {
      if (m.rows() == m.collumns()) {
	if (m.rows() > 1) {
	  T determinant = 0;      
	  for (uint i = 1; i <= m.rows(); i++) {
	    auto sub = m.SubMatrix(1, i);
	    determinant += std::pow(-1, 1 + i) * m.get(1, i) * det(sub);
	  }
	  return determinant;
	}
	else
	  return m.get(1, 1);
      }
      else
	throw std::exception {};
    }
    catch (std::exception& e) {
      std::cout << "(det(Matrix<T>& m) error) m is not rectangular\n";
    }
  }

  class Matrices {
  public:
    static Matrix<uint> Identity(uint dim) {
      auto diag = std::vector<uint>(dim, 1);
      return Matrix<uint>(diag);
    }

    static Matrix<uint> Zero(uint rows, uint collumns) {
      return Matrix<uint>(rows, collumns);
    }
  };

}

#endif // MATRIX_HPP
