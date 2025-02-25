#include<iostream>
#include<vector>
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
	
	unsigned int getSize() const {
		return this->height * this->width;
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
		if (this->getDeterminant() == 0) {
			throw std::invalid_argument("determinant 0, inverted matrix doesn't exist");
		}
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
			throw std::invalid_argument("multiplying matrix wrong sizes matrix");
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
	
	// 
	// Operator overloading
	// 
	Matrix& operator = (const Matrix& right) {
		
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
		this->height = right.height;
		this->width = right.width;
		
		this->data = new double*[right.height];
		for (unsigned int i = 0; i < right.height; i++) {
			data[i] = new double[right.width];
			
			for (unsigned int j = 0; j < right.width; j++) {
				this->data[i][j] = right.data[i][j];
			}
		}
		return *this;
	}
	
	Matrix& operator += (const Matrix& right) {
		
		// Basic checks
		if (this->height != right.height || this->width != right.width) {
			throw std::invalid_argument("+= wrong sizes matrix");
		}
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] += right.data[i][j];
			}
		}
		return *this;
	}
	Matrix& operator -= (const Matrix& right) {
		
		// Basic checks
		if (this->height != right.height || this->width != right.width) {
			throw std::invalid_argument("-= wrong sizes matrix");
		}
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] -= right.data[i][j];
			}
		}
		return *this;
	}
	
	Matrix operator + (const Matrix& right) {
		return Matrix::sum(*this, right);
	}
	Matrix operator - (const Matrix& right) {
		return Matrix::subtract(*this, right);
	}
	Matrix operator * (const Matrix& right) {
		return Matrix::multiply(*this, right); 
	}
	Matrix operator * (double value) {
		return Matrix::multiply(*this, value);
	}
	Matrix operator / (double value) {
		return Matrix::divide(*this, value);
	}
	
	bool operator == (const Matrix& right) const {
		
		if (this->height != right.height || this->width != right.width) {
			return false;
		}
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				if (this->data[i][j] < right.data[i][j] - DOUBLE_THRESHOLD || this->data[i][j] > right.data[i][j] + DOUBLE_THRESHOLD) {
					return false;
				}
			}
		}
		return true;
	}
	bool operator != (const Matrix& right) const {
		return !((*this) == right);
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
	
	// Initialisation of Vector with Matrix, that matches with given "needed_matrix"
	Vector(const Matrix& needed_matrix) : Matrix(needed_matrix) {
		this->dimension = needed_matrix.getSize();
	}
	
	// Initialisation of Vector with given coordinates as "coords_value" and dimension "dimension"
	Vector(unsigned int dimension, double const* const coords_value) : Matrix(dimension, 1) {
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
		
		double* needed_elements = (Matrix::sum(a, b)).getElements();
		Vector result = Vector(a.dimension, needed_elements);
		
		delete[] needed_elements;
		return result;
	}
	
	// Get subtract of two Vectors
	static Vector subtract(const Vector& a, const Vector& b) {
		
		double* needed_elements = (Matrix::subtract(a, b)).getElements();
		Vector result = Vector(a.dimension, needed_elements);
		
		delete[] needed_elements;
		return result;
	}
	
	// Get multiplication of Vector and scalar
	static Vector multiply(const Vector& a, double value) {
		
		double* needed_elements = (Matrix::multiply(a, value)).getElements();
		Vector result = Vector(a.dimension, needed_elements);
		
		delete[] needed_elements;
		return result;
	}
		
	// Get division of Vector and scalar
	static Vector divide(const Vector& a, double value) {
		
		double* needed_elements = (Matrix::divide(a, value)).getElements();
		Vector result = Vector(a.dimension, needed_elements);
		
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
	
	// 
	// Operators overloading
	// 
	Vector& operator = (const Vector& right) {
		
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
		this->dimension = right.dimension;
		this->height = right.height;
		this->width = right.width;
		
		this->data = new double*[right.height];
		for (unsigned int i = 0; i < right.height; i++) {
			data[i] = new double[right.width];
			
			for (unsigned int j = 0; j < right.width; j++) {
				this->data[i][j] = right.data[i][j];
			}
		}
		return *this;
	}
	
	Vector& operator += (const Vector& right) {
		
		// Basic checks
		if (this->height != right.height) {
			throw std::invalid_argument("+= wrong sizes vectors");
		}
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] += right.data[i][j];
			}
		}
		return *this;
	}
	
	Vector& operator -= (const Vector& right) {
		
		// Basic checks
		if (this->height != right.height) {
			throw std::invalid_argument("-= wrong sizes vectors");
		}
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] -= right.data[i][j];
			}
		}
		return *this;
	}
	
	Vector operator + (const Vector& right) {
		return Vector::sum(*this, right);
	}
	
	Vector operator - (const Vector& right) {
		return Vector::subtract(*this, right);
	}
	
	Vector operator * (double value) {
		return Vector::multiply(*this, value);
	}
	
	Vector operator / (double value) {
		return Vector::divide(*this, value);
	}
	
	bool operator == (const Vector& right) const {
		if (this->dimension != right.dimension || this->getMatrix() != right.getMatrix()) {
			return false;
		}
		return true;
	}
	bool operator != (const Vector& right) const {
		return !((*this) == right);
	}
	
	bool operator < (const Vector& right) const {
		if (this->getModule() < right.getModule() - DOUBLE_THRESHOLD) {
			return true;
		}
		return false;
	}
	bool operator > (const Vector& right) const {
		if (this->getModule() > right.getModule() + DOUBLE_THRESHOLD) {
			return true;
		}
		return false;
	}
	bool operator <= (const Vector& right) const {
		return !((*this) > right);
	}
	bool operator >= (const Vector& right) const {
		return !((*this) < right);
	}
	
};

// 3-dimensional Decart Ortogonal System of Coordinates
class Dekart_System {

protected: 
	Vector* base_dot;
	Vector** basis;
	std::vector<Vector> vectors;

public: 
	// Check if vectors will make basis (non-linear dependent) or not (linear-dependent)
	static bool isBasis(Vector const* const* const needed_to_check) {
		
		Matrix tmp_matrix = Matrix(3, 3);
		for (unsigned int i = 0; i < 3; i++) {
			for (unsigned int j = 0; j < 3; j++) {
				tmp_matrix.changeElement(i, j, needed_to_check[j]->getElement(i, 0) );
			}
		}
		return (tmp_matrix.getDeterminant() != 0);
	}
	
	// Initialisation of default Dekart System of Coordinates
	Dekart_System() {
		base_dot = new Vector(3, (double[]){ 0, 0, 0 });
		basis = new Vector*[3];
		basis[0] = new Vector(3, (double[]){ 1, 0, 0 });
		basis[1] = new Vector(3, (double[]){ 0, 1, 0 });
		basis[2] = new Vector(3, (double[]){ 0, 0, 1 });
	}
	
	// Initialisation clone Dekart_System but without it's vectors
	Dekart_System(const Dekart_System& needed_dek_sys) {
		base_dot = new Vector(*needed_dek_sys.base_dot);
		basis = new Vector*[3];
		basis[0] = new Vector(*needed_dek_sys.basis[0]);
		basis[1] = new Vector(*needed_dek_sys.basis[1]);
		basis[2] = new Vector(*needed_dek_sys.basis[2]);
	}
	
	// Initialisation of Dekart_System with given base_dot and basis
	Dekart_System(const Vector& needed_base_dot, Vector const* const* const needed_basis) {
		
		if (not Dekart_System::isBasis(needed_basis)) {
			throw std::invalid_argument("Attempt to make linear-dependent basis, terminating...");
		}
		
		base_dot = new Vector(needed_base_dot);
		basis = new Vector*[3];
		basis[0] = new Vector(*needed_basis[0]);
		basis[1] = new Vector(*needed_basis[1]);
		basis[2] = new Vector(*needed_basis[2]);
	}
	
	// Obviously destructor of Dekart System of Coordinates
	~Dekart_System() {
		delete base_dot;
		for (unsigned int i = 0; i < 3; i++) {
			delete basis[i];
		}
		delete[] basis;
	}
	
	// Print all Vectors in Dekart_System
	void printVectors() const {
		for (unsigned int i = 0; i < vectors.size(); i++) {
			cout << "Vector " << i << ":\n";
			vectors[i].print();
		}
	}
	
	// Print coords of base_dot and basis Vectors of current Dekart System of Coordinates
	void print() const {
		cout << "Base_dot: \n";
		base_dot->print();
		
		cout << "Basis x: \n";
		basis[0]->print();
		cout << "Basis y: \n";
		basis[1]->print();
		cout << "Basis z: \n";
		basis[2]->print();
		printVectors();
	}
	
	// Get copy of Base_dot
	Vector getBaseDot() const {
		return Vector(*this->base_dot);
	}
	
	// Get Basis as Vector** massiv of Vectors
	Vector** getBasis() const {
		Vector** result = new Vector*[3];
		for (unsigned int i = 0; i < 3; i++) {
			result[i] = new Vector(*this->basis[i]);
		}
		return result;
	}
	
	// Add Vector to Dekart_System
	void addVector(const Vector& newVector) {
		vectors.push_back(newVector);
	}
	
	// Change Vector to needed in "vectors"
	void changeVector(unsigned int index, const Vector& needed_vector) {
		vectors[index] = needed_vector;
	}
	
	// 
	// Get Basis Transformation Matrix
	// !! It gives capability to get OLD coords from NEW coords !!
	// If you want to get more native Transformation Matrix, use "getTransformationMatrix_native()"
	// 
	Matrix getTransformationMatrix(const Dekart_System& b) const {
		
		// Matrixes that represent both Basis coords
		Matrix a_support_trans_matrix = Matrix(3, 3);
		Matrix b_support_trans_matrix = Matrix(3, 3);
		
		for (unsigned int i = 0; i < 3; i++) {
			for (unsigned int j = 0; j < 3; j++) {
				a_support_trans_matrix.changeElement(i, j, this->basis[j]->getElement(i, 0));
				b_support_trans_matrix.changeElement(i, j, b.basis[j]->getElement(i, 0));
			}
		}
		return Matrix::multiply(a_support_trans_matrix.getInverted(), b_support_trans_matrix);
	}
	
	// 
	// Get Basis Transformation Matrix
	// This one gives capability to get NEW coords from OLD coords, which native (I hope it is)
	// 
	Matrix getTransformationMatrix_native(const Dekart_System& b) const {
		return (this->getTransformationMatrix(b)).getInverted();
	}
	
	// Switch current Dekart System of Coordinates to "new_dk_sys" and change all Vectors in "vectors"
	void switchSystem(const Dekart_System& new_dk_sys) {
		
		Matrix needed_native_transform_matrix = this->getTransformationMatrix_native(new_dk_sys);
		// vectors[i] = TRANS_NATIVE * (OLD_COORDS - NEW_BASE_DOT)
		for (unsigned int i = 0; i < vectors.size(); i++) {
			vectors[i] = Vector( needed_native_transform_matrix * ((vectors[i] - (*new_dk_sys.base_dot)).getMatrix()) );
		}
		// Final switches
		delete base_dot;
		for (unsigned int i = 0; i < 3; i++) {
			delete basis[i];
		}
		
		this->base_dot = new Vector(*new_dk_sys.base_dot);
		this->basis[0] = new Vector(*new_dk_sys.basis[0]);
		this->basis[1] = new Vector(*new_dk_sys.basis[1]);
		this->basis[2] = new Vector(*new_dk_sys.basis[2]);
	}
	
	// Change base_dot to "new_base_dot"
	void changeBaseDot(const Vector& new_base_dot) {
		
		Dekart_System tmp_dek_sys = Dekart_System(*this);
		delete tmp_dek_sys.base_dot;
		tmp_dek_sys.base_dot = new Vector(new_base_dot);
		
		this->switchSystem(tmp_dek_sys);
	}
	
	// Change basis with given
	void changeBasis(Vector const* const* const new_basis) {
		
		Dekart_System tmp_dek_sys = Dekart_System( Vector(3, (double[]){0, 0, 0}), new_basis);
		this->switchSystem(tmp_dek_sys);
	}
	
};
