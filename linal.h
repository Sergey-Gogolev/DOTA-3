#include<iostream>
#include<cmath>
using std::cout;

#define DOUBLE_THRESHOLD 0.000001


class Matrix {

protected: 
	unsigned int width; // number of columns
	unsigned int height; // number of rows
	double** data;

public: 
	// Fill Matrix with zeros
	void clear() {
		this->data = new double*[this->height];
		for (unsigned int i = 0; i < this->height; i++) {
			this->data[i] = new double[this->width];
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] = 0;
			}
		}
	}
	
	// Basic initialisation of Matrix filled with zeros
	Matrix(unsigned int height, unsigned int width) {
		this->height = height;
		this->width = width;
		clear();
	}
	
	// Clone Matrix initialisation (Initialise Matrix identical to "root_matrix")
	Matrix(const Matrix& root_matrix) {
		this->height = root_matrix.height;
		this->width = root_matrix.width;
		
		
		this->data = new double*[root_matrix.height];
		for (unsigned int i = 0; i < root_matrix.height; i++) {
			data[i] = new double[root_matrix.width];
			
			for (unsigned int j = 0; j < root_matrix.width; j++) {
				this->data[i][j] = root_matrix.data[i][j];
			}
		}
	}

	// Obviosly destructor
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
	double getElement(unsigned int vertical_index, unsigned int horisontal_index) const {
		return this->data[vertical_index][horisontal_index];
	}

	// Get elements of Matrix in linear double massive
	double* getElements() const {
		
		double* result = new double[this->height * this->width];
		for (unsigned int i = 0; i < this->height; i++) {
			
			for (unsigned int j = 0; j < this->width; j++) {
				result[i * this->width + j] = this->data[i][j];
			}
		}
		return result;
	}
	
	// Get data as it is ( Please, be careful, it's pretty hard to delete this data after )
	double** getData() const {
		
		double** result_data = new double*[this->height];
		for (unsigned int i = 0; i < this->height; i++) {
			result_data[i] = new double[this->width];
			for (unsigned int j = 0; j < this->width; j++) {
				result_data[i][j] = this->data[i][j];
			}
		}
		return result_data;
	}
	
	double* getRow(unsigned int vertical_index) const {
		double* result = new double[this->width];
		for (unsigned int i = 0; i < this->width; i++) {
			result[i] = this->data[vertical_index][i];
		}
		return result;
	}
	
	double* getColumn(unsigned int horisontal_index) const {
		double* result = new double[this->height];
		for (unsigned int i = 0; i < this->height; i++) {
			result[i] = this->data[i][horisontal_index];
		}
		return result;
	}
	
	// Change needed element of matrix to value (all values in it)
	void changeElement(unsigned int vertical_index, unsigned int horisontal_index, double value) {
		this->data[vertical_index][horisontal_index] = value;
	}
	
	// transpose Matrix
	void transpose() {
		
		double** needed_data = new double*[width];
		for (unsigned int i = 0; i < width; i++) {
			needed_data[i] = new double[height];
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
	Matrix getTranspositioned() const {
		
		// Creating model of transpositioned matrix by switching width and height
		Matrix result = Matrix(this->width, this->height);
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				result.data[j][i] = this->data[i][j];
			}
		}
		return result;
	}
	
	// Get minor Matrix ( Matrix with excluded elements which vertical_index or horisontal_index matches with given )
	Matrix getMinor(unsigned int vertical_index, unsigned int horisontal_index) const {
		
		Matrix result = Matrix(this->height - 1, this->width - 1);
		
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
	double getDeterminant() const {
		
		if (this->height != this->width) {
			cout << "\tdeterminant doesn't exist, not square matrix.\n";
			throw std::invalid_argument("determinant doesn't exist, not square matrix.");
		}
		
		// if there's only one element in Matrix
		if (this->height == 1) {
			return this->data[0][0];
		}
		
		double determinant = 0;
		double sign = 1;
		for (unsigned int j = 0; j < this->width; j++) {
			Matrix needed_minor = this->getMinor(0, j);
			determinant += sign * (this->data[0][j] * needed_minor.getDeterminant());
			sign *= -1;
		}
		
		return determinant;
	}
	
	// Get adjugate Matrix ( Matrix, that is made from algebraic adjugation of each element (and transppositioned))
	Matrix getAdjugated() const {
		
		// Transpositioning base Matrix
		Matrix needed_matrix = this->getTranspositioned();
		Matrix result = Matrix(needed_matrix.height, needed_matrix.width);
		
		for (unsigned int i = 0; i < needed_matrix.height; i++) {
			for (unsigned int j = 0; j < needed_matrix.width; j++) {
				Matrix needed_minor = needed_matrix.getMinor(i, j);
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
		Matrix needed_matrix = this->getAdjugated() / this->getDeterminant();
		
		double** needed_data = new double*[needed_matrix.height];
		for (unsigned int i = 0; i < needed_matrix.height; i++) {
			needed_data[i] = new double[needed_matrix.width];
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
	Matrix getInverted() const {
	    return  this->getAdjugated() / this->getDeterminant();
	}
	
	// Print Matrix in classical way
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
	void fill(double value) {
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] = value;
			}
		}
	}
	
	// Get sum of two matrix
	static Matrix sum(const Matrix& a, const Matrix& b) {
		
		// Basic checks
		if (a.height != b.height || a.width != b.width) {
			cout << "\tsumming impossible, wrong sizes.\n";
			throw std::invalid_argument("summing wrong sizes matrix");
		}
		
		// Taking width and height of Matrix "a"
		Matrix result = Matrix(a.height, a.width);
		
		for (unsigned int i = 0; i < a.height; i++) {
			for (unsigned int j = 0; j < a.width; j++) {
				result.data[i][j] = a.data[i][j] + b.data[i][j];
			}
		}
		return result;
	}
	
	// Get subtraction of two matrix
	static Matrix subtract(const Matrix& a, const Matrix& b) {
		
		// Basic checks
		if (a.height != b.height || a.width != b.width) {
			cout << "\tsubtracting impossible, wrong sizes, leaving and returning NULL.\n";
			throw std::invalid_argument("subtracting wrong sizes matrix");
		}
		
		// Taking width and height of Matrix "a"
		Matrix result = Matrix(a.height, a.width);
		
		for (unsigned int i = 0; i < a.height; i++) {
			for (unsigned int j = 0; j < a.width; j++) {
				result.data[i][j] = a.data[i][j] - b.data[i][j];
			}
		}
		return result;
	}
	
	// Get multiplication of two Matrix
	static Matrix multiply(const Matrix& a, const Matrix& b) {
		
		// Basic checks
		if (a.width != b.height) {
			cout << "\tmultiplying impossible, wrong sizes.\n";
			throw std::invalid_argument("multiplying wrong sizes matrix");
		}

		// Taking height of Matrix "a" and width of Matrix "b"
		Matrix result = Matrix(a.height, b.width);
		
		double tmp_value;
		for (unsigned int i = 0; i < a.height; i++) {
			for (unsigned int j = 0; j < b.width; j++) {
				tmp_value = 0;
				for (unsigned int k = 0; k < a.width; k++) {
					tmp_value += a.data[i][k] * b.data[k][j];
				}
				result.data[i][j] = tmp_value;
			}
		}
		return result;
	}
	
	// Get multiplication of Matrix and scalar
	static Matrix multiply(const Matrix& a, double b) {

		// Taking height of Matrix "a" and width of Matrix "a"
		Matrix result = Matrix(a.height, a.width);
		
		for (unsigned int i = 0; i < a.height; i++) {
			for (unsigned int j = 0; j < a.width; j++) {
				result.data[i][j] = a.data[i][j] * b;
			}
		}
		
		return result;
	}
	
	// Get multiplication of Matrix and scalar
	static Matrix divide(const Matrix& a, double b) {
		
		if (b == 0) {
			cout << "\tdividing impossible, ZERO, ZERO !!!!!!!!!!!!!!!!!!!!!!!!!!! (exiting)\n";
			throw std::invalid_argument("dividing impossible, ZERO, ZERO !!!!!!!!!!!!!!!!!!!!!!!!!!! (exiting)");
		}
		
		// Taking height of Matrix "a" and width of Matrix "a"
		Matrix result = Matrix(a.height, a.width);
		
		for (unsigned int i = 0; i < a.height; i++) {
			for (unsigned int j = 0; j < a.width; j++) {
				result.data[i][j] = a.data[i][j] / b;
			}
		}
		
		return result;
	}
	
	// Operator overloading
	Matrix operator + (Matrix& right) {
		return Matrix::sum(*this, right);
	}
	
	Matrix operator - (Matrix& right) {
		return Matrix::subtract(*this, right);
	}
	
	Matrix operator * (Matrix& right) {
		return Matrix::multiply(*this, right); 
	}
	
	Matrix operator * (double value) {
		return Matrix::multiply(*this, value);
	}

	Matrix operator / (double value) {
		return Matrix::divide(*this, value);
	}
	
};

class Vector : public Matrix {

protected: 
	unsigned int dimension;

public: 
	unsigned int getDimension() const {
		return this->dimension;
	}
	
	// Get Matrix that represents Vector
	Matrix getMatrix() const {
		Matrix result = Matrix(this->dimension, 1);
		for (unsigned int i = 0; i < dimension; i++) {
			result.changeElement(i, 0, this->data[i][0]);
		}
		return result;
	}
	
	// Initialisation of Vector with "coords = 0" and dimension "dimension"
	Vector(unsigned int dimension) : Matrix(dimension, 1) {
		this->dimension = dimension;
	}
	
	// Initialisation of Vector with given coordinates as "coords_value" and dimension "dimension"
	Vector(unsigned int dimension, double* coords_value) : Matrix(dimension, 1) {
		this->dimension = dimension;
		for (unsigned int i = 0; i < dimension; i++) {
			this->data[i][0] = coords_value[i];
		}
	}
	
	// Initialisation clone of Vector "vector"
	Vector(const Vector& vector) : Matrix(vector) {
		this->dimension = vector.getDimension();
	}
	
	// Obviously destructor of Vector
	~Vector() {}
	
	// Get module/length of the Vector !WORKS ONLY IN ORTOGONAL DEKART_SYSTEM OF COORDINAT!
	double getModule() const {
		return sqrt(scalar_multiply(*this, *this));
	}
	
	// Get sum of two Vectors
	static Vector sum(const Vector& a, const Vector& b) {
		
		Matrix needed_matrix = Matrix::sum(a, b);
		double* needed_elements = needed_matrix.getElements();
		
		// Taking Matrix's "a" dimension as dimension of result Matrix
		Vector result = Vector(a.getDimension(), needed_elements);
		
		delete[] needed_elements;
		return result;
	}
	
	// Get subtract of two Vectors
	static Vector subtract(const Vector& a, const Vector& b) {
		
		Matrix needed_matrix = Matrix::subtract(a, b);
		double* needed_elements = needed_matrix.getElements();
		
		// Taking Matrix's "a" dimension as dimension of result Matrix
		Vector result = Vector(a.getDimension(), needed_elements);
		
		delete[] needed_elements;
		return result;
	}
	
	// Return result of scalar multiplication of two Vectors !WORKS ONLY IN ORTOGONAL DEKART_SYSTEM OF COORDINAT!
	static double scalar_multiply(const Vector& a, const Vector& b) {
		
		Matrix needed_coords_matrix = Matrix::multiply(a.getTranspositioned(), b);
		double* needed_elements = needed_coords_matrix.getElements();
		double result = needed_elements[0];
		
		delete[] needed_elements;
		return result;
	}
	
	// Return result of vector multiplication of two Vectors, !WORKS ONLY ON 3-DIMENSIONAL VECTORS!
	static Vector vector_multiply(const Vector& a, const Vector& b) {
		
		double* a_coords = a.getElements();
		double* b_coords = b.getElements();
		
		// Equation from Wikipedia
		double* result_coords = new double[3];
		result_coords[0] = a_coords[1] * b_coords[2] - b_coords[1] * a_coords[2];
		result_coords[1] = -(a_coords[0] * b_coords[2] - b_coords[0] * a_coords[2]);
		result_coords[2] = a_coords[0] * b_coords[1] - b_coords[0] * a_coords[1];
		
		Vector result = Vector(3, result_coords);
		
		delete[] a_coords;
		delete[] b_coords;
		delete[] result_coords;
		return result;
	}

};

// 3-dimensional Decart Ortogonal System of Coordinates
class Dekart_System {

protected: 
	Vector* base_dot;
	Vector** basis;

public: 
	// Basic initialisation of Dekart System of Coordinates
	Dekart_System() {
		base_dot = new Vector(3, (double[]){ 0, 0, 0 });
		basis = new Vector*[3];
		basis[0] = new Vector(3, (double[]){ 1, 0, 0 });
		basis[1] = new Vector(3, (double[]){ 0, 1, 0 });
		basis[2] = new Vector(3, (double[]){ 0, 0, 1 });
	}
	
	// Obviously destructor of Dekart System of Coordinates
	~Dekart_System() {
		delete base_dot;
		for (unsigned int i = 0; i < 3; i++) {
			delete basis[i];
		}
		delete[] basis;
	}

	// Print coords of base_dot and basis Vectors of current Dekart System of Coordinates
	void print() {
		cout << "Base_dot: \n";
		base_dot->print();
		
		cout << "Basis x: \n";
		basis[0]->print();
		cout << "Basis y: \n";
		basis[1]->print();
		cout << "Basis z: \n";
		basis[2]->print();
	}
	
	// Get copy of Base_dot
	Vector* getBaseDot() {
		return new Vector(*this->base_dot);
	}
	
	// Get Basis as Vector** massiv of Vectors
	Vector** getBasis() {
		
		Vector** result = new Vector*[3];
		for (unsigned int i = 0; i < 3; i++) {
			result[i] = new Vector(*this->basis[i]);
		}
		return result;
	}
	
	// Change base_dot to "new_base_dot"
	void changeBaseDot(Vector new_base_dot) {
		delete this->base_dot;
		this->base_dot = new Vector(new_base_dot);
	}
	
	// Change basis with "index", numeration from 0
	void changeBasis(unsigned int index, const Vector& needed_vector) {
		delete basis[index];
		basis[index] = new Vector(needed_vector);
	}
	
	// 
	// Get Basis Transformation Matrix
	// !! It gives capability to get OLD coords from NEW coords,
	// If you want to get more native Transformation Matrix, use "getTransformationMatrix_native()"
	// 
	Matrix getTransformationMatrix(Dekart_System* b) {
		
		// Matrixes that represent both Basis coords
		Matrix a_support_trans_matrix = Matrix(3, 3);
		Matrix b_support_trans_matrix = Matrix(3, 3);
		
		for (unsigned int i = 0; i < 3; i++) {
			for (unsigned int j = 0; j < 3; j++) {
				a_support_trans_matrix.changeElement(i, j, this->basis[j]->getElement(i, 0));
				b_support_trans_matrix.changeElement(i, j, b->basis[j]->getElement(i, 0));
			}
		}
		return Matrix::multiply(a_support_trans_matrix.getInverted(), b_support_trans_matrix);
		
	}
	
	// 
	// Get Basis Transformation Matrix
	// This one gives capability to get NEW coords from OLD coords, which native (I hope it is)
	// 
	Matrix getTransformationMatrix_native(Dekart_System* b) {
		return (this->getTransformationMatrix(b)).getInverted();
	}
	
	// Switch current Dekart System of Coordinates to "new_dk_sys" and change all needed Vectors
	void switchSystem(Dekart_System* new_dk_sys, Vector** needed_vectors, unsigned int length_needed_vectors) {
		
		Matrix needed_native_transform_matrix = this->getTransformationMatrix_native(new_dk_sys);
		
		// NEW_COORDS = TRANS_NATIVE * OLD_COORDS - NEW_BASE_DOT
		for (unsigned int i = 0; i < length_needed_vectors; i++) {
			
			// TRANS_NATIVE * OLD_COORDS
			Matrix tmp_needed_matrix = needed_vectors[i]->getMatrix();
			Matrix tmp_matrix = Matrix::multiply(needed_native_transform_matrix, tmp_needed_matrix);
			
			// (TMP) - NEW_BASE_DOT
			Matrix tmp_needed_matrix_2 = new_dk_sys->base_dot->getMatrix();
			Matrix tmp_matrix_2 = Matrix::subtract(tmp_matrix, tmp_needed_matrix_2);
			
			// (VECTOR)(NEW_COORDS = (TMP_2))
			delete needed_vectors[i];
			double* needed_elements = tmp_matrix_2.getElements();
			needed_vectors[i] = new Vector(3, needed_elements);
			
			delete[] needed_elements;
		}
		
		// Final switches
		delete base_dot;
		for (unsigned int i = 0; i < 3; i++) {
			delete basis[i];
		}
		
		this->base_dot = new Vector(*new_dk_sys->base_dot);
		this->basis[0] = new Vector(*new_dk_sys->basis[0]);
		this->basis[1] = new Vector(*new_dk_sys->basis[1]);
		this->basis[2] = new Vector(*new_dk_sys->basis[2]);
	}
	
};
