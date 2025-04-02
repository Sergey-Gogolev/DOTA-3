#ifndef KFM_LINAL_H
#define KFM_LINAL_H

#include <cmath>
#include <iostream>

#ifndef FLOAT_THRESHOLD
#define FLOAT_THRESHOLD 0.0001
#endif

#ifndef DOUBLE_THRESHOLD
#define DOUBLE_THRESHOLD 0.000001
#endif

template<typename T = double> class Matrix {

protected: 
	unsigned int width; // number of columns
	unsigned int height; // number of rows
	T** data;

public: 
	// Initialise Matrix's data with given value
	void clear(const T& needed_value) {
		this->data = new T*[this->height];
		for (unsigned int i = 0; i < this->height; i++) {
			this->data[i] = new T[this->width];
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] = needed_value;
			}
		}
	}
	
	// Basic initialisation of Matrix filled with default values
	Matrix<T>(unsigned int height, unsigned int width) {
		this->height = height;
		this->width = width;
		
		// T{} --- is a default value of type T
		clear(T{});
	}
	// Basic initialisation of Matrix filled with given value
	Matrix<T>(unsigned int height, unsigned int width, const T& needed_value) {
		this->height = height;
		this->width = width;
		clear(needed_value);
	}
	// Clone Matrix initialisation (Initialise Matrix identical to "root_matrix") (COPY CONSTRUCTOR)
	Matrix<T>(const Matrix<T>& root_matrix) {
		this->height = root_matrix.height;
		this->width = root_matrix.width;
		
		this->data = new T*[root_matrix.height];
		for (unsigned int i = 0; i < root_matrix.height; i++) {
			this->data[i] = new T[root_matrix.width];
			
			for (unsigned int j = 0; j < root_matrix.width; j++) {
				this->data[i][j] = root_matrix.data[i][j];
			}
		}
	}
	// Clone Matrix initialisation (Initialise Matrix identical to "root_matrix", but with different type) (COPY CONSTRUCTOR)
	template<typename Y> Matrix<T>(const Matrix<Y>& root_matrix) {
		this->height = root_matrix.getHeight();
		this->width = root_matrix.getWidth();
		
		this->data = new T*[root_matrix.getHeight()];
		for (unsigned int i = 0; i < root_matrix.getHeight(); i++) {
			this->data[i] = new T[root_matrix.getWidth()];
			
			for (unsigned int j = 0; j < root_matrix.getWidth(); j++) {
				this->data[i][j] = (T)root_matrix.getElement(i, j);
			}
		}
	}
	
	// Obviously destructor
	~Matrix() {
		for (unsigned int i = 0; i < this->height; i++) {
			delete[] this->data[i];
		}
		delete[] this->data;
	}
	
	unsigned int getHeight() const {
		return this->height;
	}
	unsigned int getWidth() const {
		return this->width;
	}
	T getElement(unsigned int vertical_index, unsigned int horisontal_index) const {
		return this->data[vertical_index][horisontal_index];
	}
	
	// Get elements of Matrix in linear T massive
	T* getElements() const {
		
		T* result = new T[this->height * this->width];
		for (unsigned int i = 0; i < this->height; i++) {
			
			for (unsigned int j = 0; j < this->width; j++) {
				result[i * this->width + j] = this->data[i][j];
			}
		}
		return result;
	}
	
	// Get data as it is ( Please, be careful, it's pretty hard to delete this data after )
	T** getData() const {
		
		T** result_data = new T*[this->height];
		for (unsigned int i = 0; i < this->height; i++) {
			result_data[i] = new T[this->width];
			for (unsigned int j = 0; j < this->width; j++) {
				result_data[i][j] = this->data[i][j];
			}
		}
		return result_data;
	}
	
	T* getRow(unsigned int vertical_index) const {
		T* result = new T[this->width];
		for (unsigned int i = 0; i < this->width; i++) {
			result[i] = this->data[vertical_index][i];
		}
		return result;
	}
	
	T* getColumn(unsigned int horisontal_index) const {
		T* result = new T[this->height];
		for (unsigned int i = 0; i < this->height; i++) {
			result[i] = this->data[i][horisontal_index];
		}
		return result;
	}
	
	unsigned int getSize() const {
		return this->height * this->width;
	}
	
	// Change needed element of matrix to value (all values in it)
	void changeElement(unsigned int vertical_index, unsigned int horisontal_index, const T& value) {
		this->data[vertical_index][horisontal_index] = value;
	}
	
	// transpose Matrix
	void transpose() {
		
		T** needed_data = new T*[width];
		for (unsigned int i = 0; i < width; i++) {
			needed_data[i] = new T[height];
			for (unsigned int j = 0; j < height; j++) {
				needed_data[i][j] = this->data[j][i];
			}
		}
		
		for (unsigned int i = 0; i < height; i++) {
			delete[] this->data[i];
		}
		delete[] this->data;
		
		unsigned int tmp_height = this->height;
		this->height = width;
		this->width = tmp_height;
		this->data = needed_data;
		
	}
	
	// Get transpositioned Matrix
	Matrix<T> getTranspositioned() const {
		
		// Creating model of transpositioned matrix by switching width and height
		Matrix<T> result = Matrix<T>(this->width, this->height);
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				result.data[j][i] = this->data[i][j];
			}
		}
		return result;
	}
	
	// Get minor Matrix ( Matrix with excluded elements which vertical_index or horisontal_index matches are given )
	Matrix<T> getMinor(unsigned int vertical_index, unsigned int horisontal_index) const {
		
		Matrix<T> result = Matrix<T>(this->height - 1, this->width - 1);
		
		// Saving amount of rows (ki) and columns (kj) to skip when creating Matrix "result"
		unsigned int ki = 0;
		unsigned int kj = 0;
		for (unsigned int i = 0; i < this->height; i++) {
			if (i == vertical_index) {
				ki = 1;
				continue;
			}
			for (unsigned int j = 0; j < this->width; j++) {
				if (j == horisontal_index) {
					kj = 1;
					continue;
				}
				result.data[i - ki][j - kj] = this->data[i][j];
			}
			kj = 0;
		}
		return result;
	}
	
	// Get determinant of Matrix by first column and first row
	T getDeterminant() const {
		
		if (this->height != this->width) {
			throw std::invalid_argument("determinant doesn't exist, not square Matrix.");
		}
		
		// if there's only one element in Matrix
		if (this->height == 1) {
			return this->data[0][0];
		}
		
		T determinant = 0;
		bool sign = true;
		for (unsigned int j = 0; j < this->width; j++) {
			Matrix<T> needed_minor = this->getMinor(0, j);
			if (sign) {
				determinant += (this->data[0][j] * needed_minor.getDeterminant());
			}
			else {
				determinant -= (this->data[0][j] * needed_minor.getDeterminant());
			}
			sign  = sign ? false : true;
		}
		
		return determinant;
	}
	
	// Get adjugate Matrix<T> ( Matrix, that is made from algebraic adjugation of each element (and transpositioned))
	Matrix<T> getAdjugated() const {
		
		// Transpositioning base Matrix
		Matrix<T> needed_matrix = this->getTranspositioned();
		Matrix<T> result = Matrix<T>(needed_matrix.height, needed_matrix.width);
		
		for (unsigned int i = 0; i < needed_matrix.height; i++) {
			for (unsigned int j = 0; j < needed_matrix.width; j++) {
				Matrix<T> needed_minor = needed_matrix.getMinor(i, j);
				if ((i + j) % 2 == 0) {
					result.data[i][j] = needed_minor.getDeterminant();
				}
				else {
					result.data[i][j] = -(needed_minor.getDeterminant());
				}
			}
		}
		return result;
	}
	
	// Invert Matrix
	void invert() {
		Matrix<T> needed_matrix = this->getAdjugated() / this->getDeterminant();
		
		T** needed_data = new T*[needed_matrix.height];
		for (unsigned int i = 0; i < needed_matrix.height; i++) {
			needed_data[i] = new T[needed_matrix.width];
			for (unsigned int j = 0; j < needed_matrix.width; j++) {
				needed_data[i][j] = needed_matrix.data[i][j];
			}
		}
		
		delete[] this->data;
		this->data = needed_data;
		this->height = needed_matrix.height;
		this->width = needed_matrix.width;
	}
	
	// Get inverted Matrix
	Matrix<T> getInverted() const {
		if (this->getDeterminant() == 0) {
			throw std::invalid_argument("determinant 0, inverted Matrix doesn't exist");
		}
		return  this->getAdjugated() / this->getDeterminant();
	}
	
	// Print Matrix in a classical way
	void print() const {
		
		for (unsigned int i = 0; i < height; i++) {
			std::cout << "||\t\t";
			for (unsigned int j = 0; j < width; j++) {
				std::cout << data[i][j] << "\t\t";
			}
			std::cout << "||\n";
		}
	}
	
	// Fill Matrix with value
	void fill(const T& value) {
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] = value;
			}
		}
	}
	
	// Get sum with matrix
	template <typename Y> Matrix<T> getSum(const Matrix<Y>& b) const {
		
		// Basic checks
		if (this->height != b.getHeight() || this->width != b.getWidth()) {
			throw std::invalid_argument("summing wrong sizes Matrix");
		}
		
		// Taking width and height of Matrix "a"
		Matrix<T> result = Matrix<T>(this->height, this->width);
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				result.data[i][j] = this->data[i][j] + b.getElement(i, j);
			}
		}
		return result;
	}
	
	// Get subtraction of two matrix
	template <typename Y> Matrix<T> getSubtraction(const Matrix<Y>& b) const {
		
		// Basic checks
		if (this->height != b.getHeight() || this->width != b.getWidth()) {
			throw std::invalid_argument("subtracting wrong sizes Matrix");
		}
		
		// Taking width and height of Matrix "a"
		Matrix<T> result = Matrix<T>(this->height, this->width);
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				result.data[i][j] = this->data[i][j] - b.getElement(i, j);
			}
		}
		return result;
	}
	
	// Get multiplication of two Matrix
	template <typename Y> Matrix<T> getMultiplication(const Matrix<Y>& b) const {
		
		// Basic checks
		if (this->width != b.getHeight()) {
			throw std::invalid_argument("multiplying Matrix wrong sizes Matrix");
		}
		
		// Taking height of Matrix "a" and width of Matrix "b"
		Matrix<T> result = Matrix<T>(this->height, b.getWidth());
		
		T tmp_value;
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < b.getWidth(); j++) {
				tmp_value = 0;
				for (unsigned int k = 0; k < this->width; k++) {
					tmp_value += this->data[i][k] * b.getElement(k, j);
				}
				result.data[i][j] = tmp_value;
			}
		}
		return result;
	}
	
	// Get multiplication of Matrix and scalar of type Y
	template <typename Y> Matrix<T> getMultiplication(const Y& b) const {
		
		// Taking height of Matrix "a" and width of Matrix "a"
		Matrix<T> result = Matrix<T>(this->height, this->width);
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				result.data[i][j] = this->data[i][j] * b;
			}
		}
		
		return result;
	}
	
	// Get division of Matrix and scalar of type Y
	template <typename Y> Matrix<T> getDivision(const Y& b) const {
		
		if (b == 0) {
			throw std::invalid_argument("dividing impossible, ZERO, ZERO !!!!!!!!!!!!!!!!!!!!!!!!!!! (exiting)");
		}
		
		// Taking height of Matrix "a" and width of Matrix "a"
		Matrix<T> result = Matrix<T>(this->height, this->width);
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				result.data[i][j] = this->data[i][j] / b;
			}
		}
		
		return result;
	}
	
	// 
	// Operator overloading
	// 
	Matrix<T>& operator = (const Matrix<T>& right) {
		
		// Check self-assignment
		if (this == &right) {
			return *this;
		}
		
		// Delete current "data"
		for (unsigned int i = 0; i < this->height; i++) {
			delete[] this->data[i];
		}
		delete[] this->data;
		
		// Assign needed "right.data"
		this->height = right.getHeight();
		this->width = right.getWidth();
		
		this->data = new T*[right.getHeight()];
		for (unsigned int i = 0; i < right.getHeight(); i++) {
			data[i] = new T[right.getWidth()];
			
			for (unsigned int j = 0; j < right.getWidth(); j++) {
				this->data[i][j] = right.getElement(i, j);
			}
		}
		return *this;
	}
	
	template <typename Y> Matrix<T>& operator += (const Matrix<Y>& right) {
		
		// Basic checks
		if (this->height != right.getHeight() || this->width != right.getWidth()) {
			throw std::invalid_argument("+= wrong sizes Matrix");
		}
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] += (T)right.getElement(i, j);
			}
		}
		return *this;
	}
	template <typename Y> Matrix<T>& operator -= (const Matrix<Y>& right) {
		
		// Basic checks
		if (this->height != right.getHeight() || this->width != right.getWidth()) {
			throw std::invalid_argument("-= wrong sizes Matrix");
		}
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] -= (T)right.getElement(i, j);
			}
		}

		return *this;
	}
	template <typename Y> Matrix<T>& operator *= (const Matrix<Y>& right) {
		
		// Basic checks
		if (this->width != right.getHeight()) {
			throw std::invalid_argument("*= wrong sizes Matrix");
		}
		
		T** result_data = new T*[this->height];
		
		T tmp_value;
		for (unsigned int i = 0; i < this->height; i++) {
			result_data[i] = new T[right.getWidth()];
			for (unsigned int j = 0; j < right.getWidth(); j++) {
				tmp_value = 0;
				for (unsigned int k = 0; k < this->width; k++) {
					tmp_value += this->data[i][k] * (T)right.getElement(k, j);
				}
				result_data[i][j] = tmp_value;
			}
		}
		
		for (unsigned int i = 0; i < this->height; i++) {
			delete[] this->data[i];
		}
		delete[] this->data;
		this->data = result_data;
		this->width = right.getWidth();
		return *this;
	}
	template <typename Y> Matrix<T>& operator /= (const Y& b) {
		if (b == 0) {
			throw std::invalid_argument("/= division by ZERO!");
		}
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] /= b;
			}
		}
		return *this;
	}
	
	template <typename Y> Matrix<T> operator + (const Matrix<Y>& right) const {
		return this->getSum(right);
	}
	template <typename Y> Matrix<T> operator - (const Matrix<Y>& right) const {
		return this->getSubtraction(right);
	}
	template <typename Y> Matrix<T> operator * (const Matrix<Y>& right) const {
		return this->getMultiplication(right); 
	}
	template <typename Y> Matrix<T> operator * (const Y& value) const {
		return this->getMultiplication(value);
	}
	template <typename Y> Matrix<T> operator / (const Y& value) const {
		return this->getDivision(value);
	}
	
	// Operator == if type of "right" is any
	template <typename Y> bool operator == (const Matrix<Y>& right) const {
		
		if (this->height != right.getHeight() || this->width != right.getWidth()) {
			return false;
		}
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				if (this->data[i][j] != right.getElement(i, j)) {
					return false;
				}
			}
		}
		return true;
	}
	// Operator == if type of "right" is double
	template <typename Y> bool operator == (const Matrix<double>& right) const {
		
		if (this->height != right.getHeight() || this->width != right.getWidth()) {
			return false;
		}
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				if (this->data[i][j] < right.getElement(i, j) - DOUBLE_THRESHOLD || this->data[i][j] > right.getElement(i, j) + DOUBLE_THRESHOLD) {
						return false;
				}
			}
		}
		return true;
	}
	// Operator == if type of "right" is float
	template <typename Y> bool operator == (const Matrix<float>& right) const {
		
		if (this->height != right.getHeight() || this->width != right.getWidth()) {
			return false;
		}
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				if (this->data[i][j] < right.getElement(i, j) - FLOAT_THRESHOLD || this->data[i][j] > right.getElement(i, j) + FLOAT_THRESHOLD) {
						return false;
				}
			}
		}
		return true;
	}

	template <typename Y> bool operator != (const Matrix<Y>& right) const {
		return !((*this) == right);
	}
	
	// Access operators overloading !!IS NOT MEMORY SAFE, BE EXTREMELY CAREFUL!!
	T* operator [] (unsigned int index) {
		if (index >= height) {
			throw std::invalid_argument("Array index exceeds boundaries of Matrix");
		}
		return data[index];
	}
	T* operator [] (unsigned int index) const {
		if (index >= height) {
			throw std::invalid_argument("Array index exceeds boundaries of Matrix");
		}
		return data[index];
	}
	
	// Operator of type conversion
	template<typename Y> operator Matrix<Y>() const {
		return Matrix<Y>(*this);
	}
	
};

// 
// Overloading operators, that cannot be overloaded inside of Matrix
// 
template<typename T, typename Y> Matrix<T> operator * (Y value, const Matrix<T>& right) {
	return right.getMultiplication(value);
}

// Overloading some std functions for Matrix
template<typename T> std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
	for (unsigned int i = 0; i < matrix.getHeight(); i++) {
		os << "||\t\t";
		for (unsigned int j = 0; j < matrix.getWidth(); j++) {
			os << matrix.getElement(i, j) << "\t\t";
		}
		if (i != matrix.getHeight() - 1) {
			os << "||\n";
		}
		else {
			os << "||";
		}
	}
	return os;
}



template<typename T = double> class Vector : public Matrix<T> {

protected: 
	unsigned int dimension;

public: 
	unsigned int getDimension() const {
		return this->dimension;
	}
	
	// Get Matrix that represents Vector
	Matrix<T> getMatrix() const {
		return Matrix<T>(*this);
	}
	
	// Initialisation of Vector with "coords = 0" and dimension "dimension"
	Vector<T>(unsigned int dimension) : Matrix<T>(dimension, 1) {
		this->dimension = dimension;
	}
	
	// Initialisation of Vector with Matrix, that matches with given "needed_matrix"
	Vector<T>(const Matrix<T>& needed_matrix) : Matrix<T>(needed_matrix) {
		this->dimension = needed_matrix.getSize();
	}
	
	// Initialisation of Vector with given coordinates as "coords_value" and dimension "dimension"
	Vector<T>(unsigned int dimension, T const* const coords_value) : Matrix<T>(dimension, 1) {
		this->dimension = dimension;
		for (unsigned int i = 0; i < dimension; i++) {
			this->data[i][0] = coords_value[i];
		}
	}
	
	// Initialisation clone of Vector "vector" (COPY CONSTRUCTOR)
	Vector<T>(const Vector<T>& vector) : Matrix<T>(vector) {
		this->dimension = vector.getDimension();
	}
	
	// Obviously destructor of Vector
	~Vector() {}
	
	// Get module/length of the Vector !WORKS ONLY IN ORTOGONAL DEKART_SYSTEM OF COORDINAT!
	T getModule() const {
		return sqrt(this->get_scalar_multiplication(*this));
	}
	
	// Get sum of two Vectors
	template <typename Y> Vector<T> getSum(const Vector<Y>& b) const {
		return Vector<T>(this->getMatrix() + b.getMatrix());
	}
	
	// Get subtraction of two Vectors
	template <typename Y> Vector<T> getSubtraction(const Vector<Y>& b) const {
		return Vector<T>(this->getMatrix() - b.getMatrix());
	}
	
	// Get multiplication of Vector and scalar
	template<typename Y> Vector<T> getMultiplication(Y value) const {
		return Vector<T>(this->getMatrix() * value);
	}
		
	// Get division of Vector and scalar
	template<typename Y> Vector<T> getDivision(Y value) const {
		return Vector<T>(this->getMatrix() / value);
	}
	
	// Return result of scalar multiplication of this Vector to another !WORKS ONLY IN ORTOGONAL DEKART_SYSTEM OF COORDINAT!
	template <typename Y> T get_scalar_multiplication(const Vector<Y>& b) const {
		
		Matrix<T> needed_coords_matrix = this->getTranspositioned() * b.getMatrix();
		T* needed_elements = needed_coords_matrix.getElements();
		T result = needed_elements[0];
		
		delete[] needed_elements;
		return result;
	}
	
	// Return result of vector multiplication of this Vector to another !WORKS ONLY ON 3-DIMENSIONAL VECTORS!
	template <typename Y> Vector<T> get_vector_multiplication(const Vector<Y>& b) const {
		
		if (dimension != 3) {
			throw std::invalid_argument("Vector multiplication works only with 3 dimensional Vectors :/");
		}

		T* a_coords = this->getElements();
		Y* b_coords = b.getElements();
		
		// Equation from Wikipedia
		T* result_coords = new T[3];
		result_coords[0] = a_coords[1] * b_coords[2] - b_coords[1] * a_coords[2];
		result_coords[1] = -(a_coords[0] * b_coords[2] - b_coords[0] * a_coords[2]);
		result_coords[2] = a_coords[0] * b_coords[1] - b_coords[0] * a_coords[1];
		
		Vector<T> result = Vector<T>(3, result_coords);
		
		delete[] a_coords;
		delete[] b_coords;
		delete[] result_coords;
		return result;
	}
	
	// Get rotated Vector in 2 dimensions, angle in radians.
	template <typename Y> Vector<T> getRotated(Y needed_angle) const {
		
		if (dimension < 2) {
			throw std::invalid_argument("Too few dimensions to perform 2d rotation");
		}
		Matrix<T> rotate_matrix(dimension, dimension);
		for (unsigned int i = 2; i < dimension; i++) {
			rotate_matrix[i][i] = 1;
		}

		rotate_matrix[0][0] = std::cos(needed_angle);
		rotate_matrix[0][1] = -std::sin(needed_angle);
		rotate_matrix[1][0] = std::sin(needed_angle);
		rotate_matrix[1][1] = std::cos(needed_angle);
		
		Vector<T> result = Vector<T>(rotate_matrix * this->getMatrix());
		return result;
	}
	// Get rotated Vector in 3 dimensions, angle in radians, rotates by axis Z then axis Y
	template <typename Y, typename H> Vector<T> getRotated(Y needed_angle_z, H needed_angle_y) {
		
		if (dimension < 3) {
			throw std::invalid_argument("Too few dimensions to perform 3d rotation");
		}
		Matrix<T> rotate_matrix_z(dimension, dimension);
		for (unsigned int i = 0; i < dimension; i++) {
			rotate_matrix_z[i][i] = 1;
		}
		
		rotate_matrix_z[0][0] = std::cos(needed_angle_z);
		rotate_matrix_z[0][1] = -std::sin(needed_angle_z);
		rotate_matrix_z[1][0] = std::sin(needed_angle_z);
		rotate_matrix_z[1][1] = std::cos(needed_angle_z);
		std::cout << "ROTATE_MATRIX_Z: \n" << rotate_matrix_z << '\n';

		Matrix<T> rotate_matrix(dimension, dimension);
		for (unsigned int i = 0; i < dimension; i++) {
			rotate_matrix[i][i] = 1;
		}

		rotate_matrix[0][0] = std::cos(needed_angle_y);
		rotate_matrix[0][2] = std::sin(needed_angle_y);
		rotate_matrix[2][0] = -std::sin(needed_angle_y);
		rotate_matrix[2][2] = std::cos(needed_angle_y);
		std::cout << "ROTATE_MATRIX_Y: \n" << rotate_matrix << '\n';

		rotate_matrix *= rotate_matrix_z;
		std::cout << "RESULT ROTATE MATRIX: \n" << rotate_matrix << '\n';
		
		Vector<T> result = Vector<T>(rotate_matrix * this->getMatrix());
		return result;
	}

	// 
	// Operators overloading
	// 
	// Algebraic operators overloading 
	template <typename Y> Vector<T>& operator = (const Vector<Y>& right) {
		
		// Check self-assignment
		if (this == &right) {
			return *this;
		}
		
		// Delete current "data"
		for (unsigned int i = 0; i < this->height; i++) {
			delete[] this->data[i];
		}
		delete[] this->data;
		
		// Assign needed "right.data"
		this->dimension = right.getDimension();
		this->height = right.getHeight();
		this->width = right.getWidth();
		
		this->data = new T*[right.getHeight()];
		for (unsigned int i = 0; i < right.getHeight(); i++) {
			this->data[i] = new T[right.getWidth()];
			
			for (unsigned int j = 0; j < right.getWidth(); j++) {
				this->data[i][j] = right.getElement(i, j);
			}
		}
		return *this;
	}
	template <typename Y> Vector<T>& operator += (const Vector<Y>& right) {
		
		// Basic checks
		if (this->height != right.getHeight()) {
			throw std::invalid_argument("+= wrong sizes Vectors");
		}
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] += right.getElement(i, j);
			}
		}
		return *this;
	}
	template <typename Y> Vector<T>& operator -= (const Vector<Y>& right) {
		
		// Basic checks
		if (this->height != right.getHeight()) {
			throw std::invalid_argument("-= wrong sizes Vectors");
		}
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] -= right.getElement(i, j);
			}
		}
		return *this;
	}
	template <typename Y> Vector<T> operator + (const Vector<Y>& right) const {
		return this->getSum(right);
	}
	
	template <typename Y> Vector<T> operator - (const Vector<Y>& right) const {
		return this->getSubtraction(right);
	}
	
	template <typename Y> Vector<T> operator * (Y value) const {
		return this->getMultiplication(value);
	}
	
	template <typename Y> Vector<T> operator / (Y value) const {
		return this->getDivision(value);
	}
	
	template <typename Y> bool operator == (const Vector<Y>& right) const {
		if (this->dimension != right.getDimension() || this->getMatrix() != right.getMatrix()) {
			return false;
		}
		return true;
	}
	template <typename Y> bool operator != (const Vector<Y>& right) const {
		return !((*this) == right);
	}
	
	// Comparsion operators overloading
	template <typename Y> bool operator < (const Vector<Y>& right) const {
		if (this->getModule() < right.getModule() - DOUBLE_THRESHOLD) {
			return true;
		}
		return false;
	}
	template <typename Y> bool operator > (const Vector<Y>& right) const {
		if (this->getModule() > right.getModule() + DOUBLE_THRESHOLD) {
			return true;
		}
		return false;
	}
	template <typename Y> bool operator <= (const Vector<Y>& right) const {
		return !((*this) > right);
	}
	template <typename Y> bool operator >= (const Vector<Y>& right) const {
		return !((*this) < right);
	}
	
	// Access operators overloading
	T& operator [] (unsigned int index) {
		if (index >= dimension) {
			throw std::invalid_argument("Array index exceeds boundaries of Vector");
		}
		return this->data[index][0];
	}
	const T& operator [] (unsigned int index) const {
		if (index >= dimension) {
			throw std::invalid_argument("Array index exceeds boundaries of Vector");
		}
		return this->data[index][0];
	}
	
	// Operator of type conversion
	template<typename Y> operator Vector<Y>() const {
		return Vector<Y>(*this);
	}
};

// 
// Overloading operators, that cannot be overloaded inside of Vector
//
template<typename T, typename Y> Vector<T> operator * (Y value, const Vector<T>& right) {
	return right.getMultiplication(value);
}

// Overloading some std functions for Vector
template<typename T> std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
	os << "(";
	for (unsigned int i = 0; i < vector.getHeight() - 1; i++) {
		os << vector.getElement(i, 0) << "; ";
	}
	os << vector.getElement(vector.getHeight() - 1, 0) << ")";
	return os;
}

template<typename T> std::istream& operator>>(std::istream &is, Vector<T>& vector) {
	T tmp;
	for (unsigned int i = 0; i < vector.getHeight(); i++) {
		is >> tmp;
		vector.changeElement(i, 0, tmp);
	}
	return is;
}

#endif
