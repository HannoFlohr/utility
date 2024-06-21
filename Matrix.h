#pragma once
#include<vector>
#include<iostream>
#include<algorithm>

template<typename T> class Matrix {
	private:
		std::vector<std::vector<T>> m;
		unsigned rows;
		unsigned columns;
		
	public:
		Matrix(unsigned _rows, unsigned _columns, const T& _init);
		Matrix(const Matrix<T>& rhs);
		Matrix(const std::vector<std::vector<T>>& v);
		virtual ~Matrix();
		
		Matrix<T>& operator=(const Matrix<T>& rhs);
		
		//matrix mathematical operations
		Matrix<T> operator+(const Matrix<T>& rhs);
		Matrix<T>& operator+=(const Matrix<T>& rhs);
		Matrix<T> operator-(const Matrix<T>& rhs);
		Matrix<T>& operator-=(const Matrix<T>& rhs);
		Matrix<T> operator*(const Matrix<T>& rhs);
		Matrix<T>& operator*=(const Matrix<T>& rhs);
		Matrix<T> transpose();
		Matrix<T> inverse();
		
		//matrix/scalar operations                                                                                                                                                                                                     
		Matrix<T> operator+(const T& rhs);
		Matrix<T> operator-(const T& rhs);
		Matrix<T> operator*(const T& rhs);
		Matrix<T> operator/(const T& rhs);
		
		//matrix/vector operations
		std::vector<T> operator*(const std::vector<T>& rhs);
		std::vector<T> diagonal_vector();
		
		//access elements
		T& operator()(const unsigned& row, const unsigned& col);
		const T& operator()(const unsigned& row, const unsigned& col) const;
	
		unsigned get_rows() const;
		unsigned get_columns() const;
		std::vector<std::vector<T>> get_as_vector() const;
		
		//swap two rows of the matrix m or of another vector<vector<T>>
		void swap_rows(const unsigned& row1, const unsigned& row2);
		void swap_rows(const unsigned& row1, const unsigned& row2, std::vector<std::vector<T>>& v);
		
		void printMatrix();
};

//constructor
template<typename T>
Matrix<T>::Matrix(unsigned _rows, unsigned _columns, const T& _init) {
	m.resize(_rows);
	for(unsigned i=0; i<m.size(); i++)
		m[i].resize(_columns, _init);
	
	rows = _rows;
	columns = _columns;
}	

//copy constructor
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs) {
	m = rhs.m;
	rows = rhs.get_rows();
	columns = rhs.get_columns();
}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& v) {
	m = v;
	rows = v.size();
	columns = v[0].size();
}

//destructor
template<typename T>
Matrix<T>::~Matrix() {}

//assignment
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
	if(&rhs == this)
		return *this;
	
	rows = rhs.get_rows();
	columns = rhs.get_columns();
	
	m.resize(rows);
	for(unsigned i=0; i<m.size(); i++) 
		m[i].resize(columns);
	
	for(unsigned i=0; i<rows; i++) 
		for(unsigned j=0; j<columns; j++)
			m[i][j] = rhs(i, j);
		
	return *this;
}

//addition
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) {
  Matrix result(rows, columns, 0.0);

  for (unsigned i=0; i<rows; i++) 
    for (unsigned j=0; j<columns; j++) 
      result(i,j) = this->m[i][j] + rhs(i,j);

  return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
  for (unsigned i=0; i<rhs.get_rows(); i++) 
    for (unsigned j=0; j<rhs.get_columns(); j++) 
      this->mat[i][j] += rhs(i,j);

  return *this;
}

//subtraction
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) {
  Matrix result(rhs.get_rows(), rhs.get_columns(), 0.0);

  for (unsigned i=0; i<rhs.get_rows(); i++) 
    for (unsigned j=0; j<rhs.get_columns(); j++) 
      result(i,j) = this->m[i][j] - rhs(i,j);

  return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
  for (unsigned i=0; i<rhs.get_rows(); i++) 
    for (unsigned j=0; j<rhs.get_columns(); j++) 
      this->m[i][j] -= rhs(i,j);
  
  return *this;
}

//multiplication
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) {
  Matrix result(rhs.get_rows(), rhs.get_columns(), 0.0);

  for (unsigned i=0; i<rhs.get_rows(); i++) 
    for (unsigned j=0; j<rhs.get_columns(); j++) 
      for (unsigned k=0; k<rhs.get_rows(); k++) 
        result(i,j) += this->m[i][k] * rhs(k,j);

  return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
  return (*this) * rhs;
}

//calculate transpose
template<typename T>
Matrix<T> Matrix<T>::transpose() {
  Matrix result(rows, columns, 0.0);

  for (unsigned i=0; i<rows; i++) 
    for (unsigned j=0; j<columns; j++) 
      result(i,j) = this->m[j][i];

  return result;
}

//calculate the inverse of the matrix
template<typename T>
Matrix<T> Matrix<T>::inverse() {
	const int n = m.size();
	T factor;
	std::vector<std::vector<T>> cur = this->m;
	std::vector<std::vector<T>> res(n, std::vector<T>(n,0));
	for (int i = 0; i < n; i++)
		res[i][i] = 1;
	
	//convert to row-echelon form
	for (int j = 0; j < n - 1; j++) {
		if (cur[j][j] == 0)
			for (int i = j + 1; i < n; i++) {
				if (cur[i][j] != 0) {
					swap_rows(j, i, cur);
					swap_rows(j, i, res);
					break;
				}
			}
		if (cur[j][j] == 0)
			continue;
		for (int i = j + 1; i < n; i++) {
			factor = -cur[i][j] / cur[j][j];
			for (int k = 0; k < n; k++) {
				cur[i][k] += factor * cur[j][k]; 
 				res[i][k] += factor * res[j][k]; 
			}
		}
	}
	
	//convert to diagonal form
	for (int i = n - 1; i > 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			factor = -cur[j][i] / cur[i][i];
			for (int k = 0; k < n; k++) { 
				cur[j][k] += factor * cur[i][k];
				res[j][k] += factor * res[i][k];
			}
		}
	}
	//converting to unit
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			res[i][j] /= cur[i][i];

	return Matrix<T>(res);;
}

//addition matrix+scalar
template<typename T>
Matrix<T> Matrix<T>::operator+(const T& rhs) {
  Matrix result(rows, columns, 0.0);

  for (unsigned i=0; i<rows; i++) 
    for (unsigned j=0; j<columns; j++) 
      result(i,j) = this->m[i][j] + rhs;

  return result;
}

//subtraction matrix-scalar
template<typename T>
Matrix<T> Matrix<T>::operator-(const T& rhs) {
  Matrix result(rows, columns, 0.0);

  for (unsigned i=0; i<rows; i++) 
    for (unsigned j=0; j<columns; j++) 
      result(i,j) = this->m[i][j] - rhs;

  return result;
}

//multiplication matrix*scalar
template<typename T>
Matrix<T> Matrix<T>::operator*(const T& rhs) {
  Matrix result(rows, columns, 0.0);

  for (unsigned i=0; i<rows; i++) 
    for (unsigned j=0; j<columns; j++) 
      result(i,j) = this->m[i][j] * rhs;

  return result;
}

//divison matrix/scalar
template<typename T>
Matrix<T> Matrix<T>::operator/(const T& rhs) {
  Matrix result(rows, columns, 0.0);

  for (unsigned i=0; i<rows; i++) 
    for (unsigned j=0; j<columns; j++) 
      result(i,j) = this->m[i][j] / rhs;

  return result;
}

//multiplication matrix*vector
template<typename T>
std::vector<T> Matrix<T>::operator*(const std::vector<T>& rhs) {
  std::vector<T> result(rhs.size(), 0.0);

  for (unsigned i=0; i<rows; i++) 
    for (unsigned j=0; j<columns; j++) 
      result[i] = this->m[i][j] * rhs[j];

  return result;
}

//returns a vector of the diagonal
template<typename T>
std::vector<T> Matrix<T>::diagonal_vector() {
  std::vector<T> result(rows, 0.0);

  for (unsigned i=0; i<rows; i++) 
    result[i] = this->mat[i][i];

  return result;
}

//access element of the matrix
template<typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) {
  return this->m[row][col];
}

template<typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const {
  return this->m[row][col];
}

template<typename T>
unsigned Matrix<T>::get_rows() const {
  return this->rows;
}

template<typename T>
unsigned Matrix<T>::get_columns() const {
  return this->columns;
}

template<typename T>
std::vector<std::vector<T>> Matrix<T>::get_as_vector() const {
	return this->m;
}

template<typename T>
void Matrix<T>::swap_rows(const unsigned& row1, const unsigned& row2) {
	for(unsigned i=0; i<columns; i++) 
		std::swap(m[row1][i],m[row2][i]);
	
}

template<typename T>
void Matrix<T>::swap_rows(const unsigned& row1, const unsigned& row2, std::vector<std::vector<T>>& v) {
	for(unsigned i=0; i<v[0].size(); i++) 
		std::swap(v[row1][i],v[row2][i]);
}

template<typename T>
void Matrix<T>::printMatrix() {
  for(unsigned int i=0; i<rows; i++) {
	for(unsigned int j=0; j<columns; j++) 
	  std::cout << m[i][j] << " ";
	std::cout << std::endl;
  }
}