#include<iostream>
using std::cout;
using std::endl;

#define DOUBLE_THRESHOLD 0.000001


class Matrix {

protected: 
	unsigned int width;
	unsigned int height;
	double** data;

public: 
	// Fill matrix with zeros
	void clear() {
		cout << "clearing...\n";
		this->data = new double*[this->height];
		for (unsigned int i = 0; i < this->height; i++) {
			this->data[i] = new double[this->width];
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] = 0;
			}
		}
		cout << "clearing Done.\n";
	}
	
	Matrix(unsigned int height, unsigned int width) {
		cout << "Matrix initialisation...\n";
		this->height = height;
		this->width = width;
		clear();
		cout << "Matrix initialisation Done.\n";
	}
	
	// Clone Matrix initialisation
	Matrix(Matrix* root_matrix) {
		cout << "Clone Matrix initialisation...\n";
		this->height = root_matrix->height;
		this->width = root_matrix->width;

		this->data = new double*[root_matrix->height];
		for (unsigned int i = 0; i < root_matrix->height; i++) {
			data[i] = new double[root_matrix->width];
			for (unsigned int j = 0; j < root_matrix->width; j++) {
				this->data[i][j] = root_matrix->data[i][j];
			}
		}
		cout << "Clone Matrix initialisation Done.\n";
	}
	
	~Matrix() {
		cout << "Matrix destructing...\n";
		for (unsigned int i = 0; i < height; i++) {
			delete[] data[i];
		}
		delete[] data;
		cout << "Matrix destructing Done.\n";
	}
	
	unsigned int getHeigth() {
		return this->height;
	}
	
	unsigned int getWidth() {
		return this->width;
	}
	
	// Print data in matrix
	void print() {
		cout << "Matrix printing...\n";
		for (unsigned int i = 0; i < height; i++) {
			std::cout << "||\t\t";
			for (unsigned int j = 0; j < width; j++) {
				std::cout << data[i][j] << "\t\t";
			}
			std::cout << "||\n";
		}
		cout << "Matrix printing Done.\n";
		
	}
	
	double getElement(unsigned int vertical_index, unsigned int horisontal_index) {
		return this->data[vertical_index][horisontal_index];
	}
	
	// Get elements of Matrix in double massive
	double* getElements() {
		cout << "getting elements of Matrix...\n";
		double* result = new double[this->height * this->width];
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				result[i * this->width + j] = this->data[i][j];
			}
		}
		cout << "getting elements of Matrix Done.\n";
		return result;
		
	}
	
	// Change needed element of matrix
	void changeElement(unsigned int vertical_index, unsigned int horisontal_index, double value) {
		cout << "changing element of Matrix...\n";
		this->data[vertical_index][horisontal_index] = value;
		cout << "changing element of Matrix Done.\n";
	}
	
	// Multiply matrix to a number
	void multiplyToNum(double value) {
		
		cout << "multiplying Matrix to number...\n";
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] *= value;
			}
		}
		cout << "multiplying Matrix to number Done.\n";
		
	}
	
	// Divide matrix to a number
	void divideToNum(double value) {
		
		cout << "dividing Matrix to number...\n";
		
		if (value == 0) {
			cout << "\tdividing impossible, ZERO, ZERO !!!!!!!!!!!!!!!!!!!!!!!!!!! (exiting)\n";
			return;
		}
		
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				this->data[i][j] /= value;
			}
		}
		cout << "dividing Matrix to number Done.\n";
		
	}
	
	// Fill Matrix with value
	void fill(double value) {
		cout << "Matrix filling...\n";
		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				data[i][j] = value;
			}
		}
		cout << "Matrix filling Done.\n";
	}
	
	// get transpositioned Matrix
	Matrix* getTranspositioned() {
		cout << "getting transpositioned Matrix...\n";
		
		// Creating model of transpositioned matrix by switching width and height
		Matrix* result = new Matrix(this->width, this->height);
		for (unsigned int i = 0; i < this->height; i++) {
			for (unsigned int j = 0; j < this->width; j++) {
				result->data[j][i] = this->data[i][j];
			}
		}
		cout << "getting transpositioned Matrix Done.\n";
		return result;
		
	}
	
	// Matrix transposition
	void transposition() {
		cout << "transpositioning Matrix...\n";
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
		cout << "transpositioning Matrix Done.\n";
	}

	// Sum two matrix
	static Matrix* sum(Matrix* a, Matrix* b) {
		
		cout << "summing two Matrix...\n";
		
		// Checks
		if (a->height != b->height || a->width != b->width) {
			cout << "\tsumming impossible, wrong sizes, leaving and returning NULL.\n";
			return NULL;
		}
		
		// Taking width and height of Matrix a
		Matrix* result = new Matrix(a->height, a->width);
		
		for (unsigned int i = 0; i < a->height; i++) {
			for (unsigned int j = 0; j < a->width; j++) {
				result->data[i][j] = a->data[i][j] + b->data[i][j];
			}
		}
		cout << "summing two Matrix Done.\n";
		return result;
		
	}
	
	// Subtract two matrix
	static Matrix* subtract(Matrix* a, Matrix* b) {
		
		cout << "subtracting two Matrix...\n";
		
		// Checks
		if (a->height != b->height || a->width != b->width) {
			cout << "\tsubtracting impossible, wrong sizes, leaving and returning NULL.\n";
			return NULL;
		}
		
		// Taking width and height of Matrix a
		Matrix* result = new Matrix(a->height, a->width);
		
		for (unsigned int i = 0; i < a->height; i++) {
			for (unsigned int j = 0; j < a->width; j++) {
				result->data[i][j] = a->data[i][j] - b->data[i][j];
			}
		}
		cout << "subtracting two Matrix Done.\n";
		return result;
		
	}
	
	// Multiplying two Matrix
	static Matrix* multiply(Matrix* a, Matrix* b) {
		cout << "multiplying two Matrix...\n";
		
		// Checks
		if (a->width != b->height) {
			cout << "\tmultiplying impossible, wrong sizes, leaving and returning NULL.\n";
			return NULL;
		}
		
		Matrix* result = new Matrix(a->height, b->width);
		
		double tmp_value;
		for (unsigned int i = 0; i < a->height; i++) {
			for (unsigned int j = 0; j < b->width; j++) {
				tmp_value = 0;
				for (unsigned int k = 0; k < a->width; k++) {
					tmp_value += a->data[i][k] * b->data[k][j];
				}
				result->data[i][j] = tmp_value;
			}
		}
		cout << "multiplying two Matrix Done.\n";
		return result;
		
	}
	
	// Get minor Matrix ( Matrix with excluded elements which vertical_index or horisontal_index matches with given )
	// !! WRITTEN WITH HALF OF CONSCIOUSNESS, BE AWARE OF BUGS AND ETC. !!
	Matrix* getMinorMatrix(unsigned int vertical_index, unsigned int horisontal_index) {
		cout << "getting minor Matrix...\n";
		Matrix* result = new Matrix(this->height - 1, this->width - 1);
		
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
				result->data[i - ki][j - kj] = this->data[i][j];
			}
			kj = 0;
		}
		cout << "getting minor Matrix Done.\n";
		return result;
		
	}
	
	// Get determinant of Matrix by first column and first "string" idc how it should be written honestly :|
	double getDeterminant() {
		cout << "getting determinant of Matrix...\n";
		if (this->height != this->width) {
			cout << "\tdeterminant doesn't exist, not square matrix, leaving and returning 42.";
			return 42;
		}
		
		// if there's only one element in Matrix
		if (this->height == 1) {
			return this->data[0][0];
		}
		
		double determinant = 0;
		double sign = 1;
		for (unsigned int j = 0; j < this->width; j++) {
			Matrix* needed_minor = getMinorMatrix(0, j);
			determinant += sign * (this->data[0][j] * needed_minor->getDeterminant());
			delete needed_minor;
			sign *= -1;
		}
		
		cout << "getting determinant of Matrix Done.\n";
		return determinant;
	}
	
	// Get adjugate Matrix
	Matrix* getAdjugateMatrix() {
		cout << "getting adjugate Matrix...\n";
		Matrix* result = new Matrix(this->height, this->width);
		Matrix* needed_matrix = this->getAdjugateMatrix();
		for (unsigned int i = 0; i < needed_matrix->height; i++) {
			for (unsigned int j = 0; j < needed_matrix->width; j++) {
				Matrix* needed_minor = needed_matrix->getMinorMatrix(i, j);
				if ((i + j) % 2 == 0) {
					result->data[i][j] = needed_minor->getDeterminant();
				}
				else {
					result->data[i][j] = -(needed_minor->getDeterminant());
				}
				delete needed_minor;
			}
		}
		cout << "getting adjugate Matrix Done.\n";
		return result;
		
	}
	
	// Get invertible Matrix
	Matrix* getInvertibleMatrix() {
		cout << "getting invertible Matrix of Matrix...\n";
		Matrix* result = this->getAdjugateMatrix();
		result->divideToNum(this->getDeterminant());
		result->transposition();
		cout << "getting invertible Matrix of Matrix Done.\n";
		return result;
	}
	
	// 
	// Gauss method in which left matrix is current basis, right matrix is needed basis
	// Method gives the result of elementary actions in which we get idendity matrix on the left, 
	// and result matrix on the right (it is transposition matrix)
	// 
	/*
	static Matrix* MadeGaussLeftRight(Matrix* leftMatrix, Matrix* rightMatrix) {
		cout << "making gauss method...\n";
		Matrix* operation_matrix = new Matrix(leftMatrix);
		Matrix* needed_matrix = new Matrix(rightMatrix);
		Matrix* whole_matrix = Matrix::sum(operation_matrix, needed_matrix);
		
		// First step of Gauss method
		unsigned int current_global_j = 0;
		unsigned int current_global_i = 0;
		bool flag_main = false;
		for (;;) {
			
			bool flag_iter = false; // Need to break 2 cycles in row
			// Check for the first non-zero element and change rows and columns neededly
			for (unsigned int i = current_global_i; i < operation_matrix->height; i++) {
				for (unsigned int j = current_global_j; j < operation_matrix->width; j++) {
					
					// We encountered non-zero element
					if (whole_matrix->data[i][j] < DOUBLE_THRESHOLD || whole_matrix->data[i][j] > DOUBLE_THRESHOLD) {
						
						// Changing encountered element to 1
						for (unsigned int needed_j = 0; needed_j < whole_matrix->height; needed_j++) {
							whole_matrix->data[i][needed_j] /= whole_matrix->data[i][j];
						}
						
						// Changing encountered element's column elements to zero, excluding encountered element itself
						for (unsigned int needed_i = 0; needed_i < whole_matrix->width; needed_i++) {
							if (needed_i == i) continue;
							double needed_decrement_value = whole_matrix->data[needed_i][j];
							for (unsigned int needed_j = 0; needed_j < whole_matrix->width; needed_j++) {
								whole_matrix->data[needed_i][needed_j] -= needed_decrement_value;
							}
						}
						current_global_i++;
						current_global_j++;
						if (current_global_i >= operation_matrix->height && current_global_j >= operation_matrix->width) {
							flag_main = true;
						}
						flag_iter = true;
					}
					if (flag_iter) break;
				}
				if (flag_iter) break;
			}
			if (flag_main) break;
		}
		
		// Second step of Gauss method
		for (;;) {
			
		}
		
		cout << "making gauss method Done.\n";
		return result_matrix;
	}
	*/

	
	
};

class Vector : public Matrix {

private: 
	unsigned int dimension;

public: 
	Vector(unsigned int dimension) : Matrix(dimension, 1) {
		cout << "clear Vector initialising...\n";
		this->dimension = dimension;
		cout << "clear Vector initialising Done.\n";
	}
	
	Vector(unsigned int dimension, double* coords_values) : Matrix(dimension, 1) {
		cout << "Vector initialising...\n";
		this->dimension = dimension;
		for (unsigned int i = 0; i < dimension; i++) {
			this->data[i][0] = coords_values[i];
		}
		cout << "Vector initialising Done.\n";
	}
	
	~Vector() {
		cout << "destructing Vector...\n";
		cout << "destructing Vector Done.\n";
	}
	
	// Return Sum of two Vectors
	static Vector* sum(Vector* a, Vector* b) {
		cout << "getting summing result...\n";
		Matrix* needed_coords_matrix = Matrix::sum(a, b);
		double* needed_coords = needed_coords_matrix->getElements();
		Vector* result = new Vector(a->dimension, needed_coords);
		
		delete[] needed_coords;
		delete needed_coords_matrix;
		cout << "getting summing result Done.\n";
		return result;
		
	}
	
	// Return result of scalar multiplication of two Vectors
	static double scalar_multiply(Vector* a, Vector* b) {
		cout << "getting scalar multiplication result...\n";
		Matrix* a_coords_matrix_transpositioned = a->getTranspositioned();
		Matrix* needed_coords_matrix = Matrix::multiply(a_coords_matrix_transpositioned, b);
		double* needed_elements = needed_coords_matrix->getElements();
		double result = needed_elements[0];
		
		delete[] needed_elements;
		delete needed_coords_matrix;
		delete a_coords_matrix_transpositioned;
		cout << "getting scalar multiplication result Done.\n";
		return result;
	}
	
	// Return result of vector multiplication of two Vectors, !WORKS ONLY ON 3-dimensional VECTORS!
	static Vector* vector_multiply(Vector* a, Vector* b) {
		cout << "getting vector multiplication result...\n";
		double* a_coords = a->getElements();
		double* b_coords = b->getElements();
		
		double* result_coords = new double[3];
		result_coords[0] = a_coords[1] * b_coords[2] - b_coords[1] * a_coords[2];
		result_coords[1] = -(a_coords[0] * b_coords[2] - b_coords[0] * a_coords[2]);
		result_coords[2] = a_coords[0] * b_coords[1] - b_coords[0] * a_coords[1];
		
		Vector* result = new Vector(3, result_coords);
		
		delete[] a_coords;
		delete[] b_coords;
		delete[] result_coords;
		cout << "getting vector multiplication result Done.\n";
		return result;
		
	}

};

// 3-dimensional decart ortogonal system of coordinates
class Dekart_System {

private: 
	Vector* Base_Dot;
	Vector** Basis;

public: 
	Dekart_System() {
		cout << "new dekart system initialisationing...\n";
		Base_Dot = new Vector(3, (double[]){ 0, 0, 0 });
		Basis = new Vector*[3];
		Basis[0] = new Vector(3, (double[]){ 1, 0, 0 });
		Basis[1] = new Vector(3, (double[]){ 0, 1, 0 });
		Basis[2] = new Vector(3, (double[]){ 0, 0, 1 });
		cout << "new dekart system initialisationing Done.\n";
	}
	
	Dekart_System(Vector** needed_basis) {
		cout << "new dekart system initialisationing...\n";
		Base_Dot = new Vector(3, (double[]){ 0, 0, 0 });
		Basis = new Vector*[3];
		Basis[0] = needed_basis[0];
		Basis[1] = needed_basis[1];
		Basis[2] = needed_basis[2];
		cout << "new dekart system initialisationing Done.\n";
	}
	
	~Dekart_System() {
		cout << "dekart system destructing...\n";
		delete Base_Dot;
		for (unsigned int i = 0; i < 3; i++) {
			delete Basis[i];
		}
		delete Basis;
		cout << "dekart system destructing Done.\n";
	}
	
	void print() {
		cout << "Base_dot: \n";
		Base_Dot->print();
		
		cout << "Basis x: \n";
		Basis[0]->print();
		cout << "Basis y: \n";
		Basis[1]->print();
		cout << "Basis z: \n";
		Basis[2]->print();
	}
	
	// 
	// Get basis Transformation Matrix
	// !! It gives capability to get OLD coords from NEW coords,
	// If you want to get more related Transformation Matrix, use "getTransformationMatrix_native()"
	// 
	static Matrix* getTransformationMatrix(Dekart_System* a, Dekart_System* b) {
		cout << "getting transformation matrix from one dk system to another...\n";
		Matrix* a_support_trans_matrix = new Matrix(3, 3);
		Matrix* b_support_trans_matrix = new Matrix(3, 3);
		
		for (unsigned int i = 0; i < 3; i++) {
			for (unsigned int j = 0; j < 3; j++) {
				cout << "\tsupport_trans_matrix changing element i = " << i << " j = " << j << "...\n";
				a_support_trans_matrix->changeElement(i, j, a->Basis[j]->getElement(i, 0));
				b_support_trans_matrix->changeElement(i, j, b->Basis[j]->getElement(i, 0));
				cout << "\tsupport_trans_matrix changing element i = " << i << " j = " << j << " Done.\n";
			}
		}

		Matrix* a_invertible = a_support_trans_matrix->getInvertibleMatrix();
		
		cout << "printing a_support_trans_matrix...\n";
		a_support_trans_matrix->print();
		cout << "printing a_support_trans_matrix Done.\n";
		cout << "printing b_support_trans_matrix...\n";
		b_support_trans_matrix->print();
		cout << "printing b_support_trans_matrix Done.\n";
		
		cout << "printing a_invertible...\n";
		a_invertible->print();
		cout << "printing a_invertible Done.\n";
		
		Matrix* result = Matrix::multiply(a_invertible, b_support_trans_matrix);

		delete a_invertible;
		delete a_support_trans_matrix;
		delete b_support_trans_matrix;
		cout << "getting transformation matrix from one dk system to another Done.\n";
		return result;
		
	}

	static Matrix* getTransformationMatrix_native(Dekart_System* a, Dekart_System* b) {
		cout << "getting native transformation matrix from one dk system to another...\n";
		Matrix* result = Dekart_System::getTransformationMatrix(a, b);
		result->transposition();
		cout << "getting native transformation matrix from one dk system to another Done.\n";
		return result;
	}
	

};
