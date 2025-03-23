#include<iostream>
#include<vector>
#include<cmath>

using std::cout;
using std::endl;

#include "linal.h"


int main() {
	std::cout << std::boolalpha;
	char tmp;
	
	Matrix x = Matrix(3, 3);
	x.changeElement(0, 0, 42);
	x.changeElement(0, 1, 42);
	x.changeElement(0, 2, 42);
	x.changeElement(1, 0, 42);
	x.changeElement(1, 1, 42);
	x.changeElement(1, 2, 42);
	x.changeElement(2, 0, 42);
	x.changeElement(2, 1, 42);
	x.changeElement(2, 2, 42);
	x.print();
	
	cout << "Clone: \n";
	Matrix y = Matrix(x);
	y.print();
	
	cout << "Original: \n";
	x.print();
	
	cout << "Transpositioned x:\n";
	Matrix trans_x = x.getTranspositioned();
	trans_x.print();
	
	cout << "Get minor (1, 1) of x:\n";
	Matrix minor_x = x.getMinor(1, 1);
	minor_x.print();
	
	cout << "Get adjugated x:\n";
	Matrix adjugated_x = x.getAdjugated();
	adjugated_x.print();
	
	cout << "Get sum of x and y:\n";
	Matrix sum_xy = Matrix::sum(x, y);
	sum_xy.print();
	
	cout << "Get multiplication of x and y:\n";
	Matrix multiplication_xy = Matrix::multiply(x, y);
	multiplication_xy.print();
	
	cout << " --- Vector Part --- \n";
	Vector a = Vector(3);
	a.changeElement(0, 0, 0.5);
	a.changeElement(1, 0, 1.5);
	a.changeElement(2, 0, 2.5);
	
	cout << "Original a:\n";
	a.print();
	
	cout << "Clone of a, b:\n";
	Vector b = Vector(a);
	b.print();
	
	cout << "Sum a and b:\n";
	Vector sum_ab = Vector::sum(a, b);
	sum_ab.print();
	
	cout << "Subtract a and b:\n";
	Vector subtract_ab = Vector::subtract(a, b);
	subtract_ab.print();
	
	cout << "Multiply a to 228:\n";
	Vector multiply_a = a * 228;
	multiply_a.print();
	
	cout << "Multiply a to 228 from left:\n";
	Vector multiply_a_from_left = 228 * a;
	multiply_a_from_left.print();

	cout << "Divide a to 1.5:\n";
	Vector divide_a = a / 1.5;
	divide_a.print();

	cout << "Scalar multiplication of a and b:\n";
	double scalar_multiplication_ab = Vector::scalar_multiply(a, b);
	cout << scalar_multiplication_ab << "\n";
	
	cout << "Vector multiplication of a and b:\n";
	Vector vector_multiplication_ab = Vector::vector_multiply(a, b);
	vector_multiplication_ab.print();
	
	cout << "Get module of the Vector a:\n";
	double module_a = a.getModule();
	cout << "Module: " << module_a << "\n";
	
	cout << " --- Advanced Matrix Part --- \n";
	cout << "Operator + overload with matrix check, x + y + y:\n";
	Matrix operator_sum_xy = x + y + y;
	operator_sum_xy.print();
	
	cout << "Operator - overload with matrix check, x - y - x - x - x:\n";
	Matrix operator_subtract_xy = x - y - x - x - x;
	operator_subtract_xy.print();
	
	cout << "Operator * overload with matrix check, x * y * y:\n";
	Matrix operator_multiply_xy = x * y * y;
	operator_multiply_xy.print();
	
	cout << "Operator * overload with scalar check, 5 * x * 2 * 42:\n";
	Matrix operator_multiply_x = x * 5 * 2 * 42;
	operator_multiply_x.print();
	
	cout << "Operator * overload with itself check, x * x * x:\n";
	Matrix operator_multiply_itself_x = x * x * x;
	operator_multiply_itself_x.print();
	
	cout << "Operator / overload with scalar check, x / 5 / 2 / 42:\n";
	Matrix operator_divide_x = x / 5 / 2 / 42;
	operator_divide_x.print();
	
	cout << "Operator = overload check, x = x * 3 * x / 2 = x * 2 * x / 2:\n";
	x = x * 3 * x / 2 = x * 2 * x / 2;
	x.print();
	
	cout << "Operator += overload check, x += x * 2:\n";
	x += x * 2;
	x.print();
	
	cout << "Operator -= overload check, x -= x * 2:\n";
	x -= x * 2;
	x.print();
	
	cout << "Operator == overload check:\n";
	cout << "\tx == x: " << (x == x) << "\n";
	cout << "\tx == x * 2: " << (x == x * 2) << "\n";
	
	cout << "Operator != overload check:\n";
	cout << "\tx != x: " << (x != x) << "\n";
	cout << "\tx != x / 2: " << (x != x / 2) << "\n";
	
	cout << "Operator << overload check, cout << x << \" GG \\n\":\n";
	cout << x  << " GG \n"<< "\n";
	
	std::cin >> tmp;
	
	cout << "Dinamic array of Matrix initialisation check:\n";
	unsigned int length_array_matrix = 100000;
	Matrix** array_matrix = new Matrix*[length_array_matrix];
	
	for (unsigned int i = 0; i < length_array_matrix; i++) {
		cout << i << " ";
		array_matrix[i] = new Matrix(20, 20);
	}
	cout << "\n";
	
	for (unsigned int i = 0; i < length_array_matrix; i++) {
		delete array_matrix[i];
	}
	delete[] array_matrix;
	
	cout << " --- Advanced Vector Part --- \n";
	cout << "Operator = overload check, a = a * 3 / 2 = b * 3 * 5:\n";
	a = a * 3 / 2 = b * 3 * 5;
	a.print();
	
	cout << "Operator += overload check, a += a * 2:\n";
	a += a * 2;
	a.print();
	
	cout << "Operator -= overload check, a -= a * 2:\n";
	a -= a * 2;
	a.print();
	
	cout << "Operator == overload check:\n";
	cout << "\ta == a: " << (a == a) << "\n";
	cout << "\ta == a * 2: " << (a == a * 2) << "\n";
	
	cout << "Operator != overload check:\n";
	cout << "\ta != a: " << (a != a) << "\n";
	cout << "\ta != a / 2: " << (a != a / 2) << "\n";
	
	cout << "Operator < overload check:\n";
	cout << "\ta < a: " << (a < a) << "\n";
	cout << "\ta < a * 2: " << (a < a * 2) << "\n";
	cout << "\ta < a / 2: " << (a < a / 2) << "\n";
	
	cout << "Operator > overload check:\n";
	cout << "\ta > a: " << (a > a) << "\n";
	cout << "\ta > a / 2: " << (a > a / 2) << "\n";
	cout << "\ta > a * 2: " << (a > a * 2) << "\n";
	
	cout << "Operator <= overload check:\n";
	cout << "\ta <= a: " << (a <= a) << "\n";
	cout << "\ta <= a * 2: " << (a <= a * 2) << "\n";
	cout << "\ta <= a / 2: " << (a <= a / 2) << "\n";
	
	cout << "Operator >= overload check:\n";
	cout << "\ta >= a: " << (a >= a) << "\n";
	cout << "\ta >= a / 2: " << (a >= a / 2) << "\n";
	cout << "\ta >= a * 2: " << (a >= a * 2) << "\n";
	
	cout << "Operator << overload check, cout << a << \" GG \\n\":\n";
	cout << a << " GG \n";
	
	cout << "Operator >> overload check, cin >> new_vect (DIMENSION = 4):\n";
	Vector new_vect(4);
	std::cin >> new_vect;
	cout << new_vect << "\n";
	
	std::cin >> tmp;
	
	cout << "Dinamic array of Vectors initialisation check:\n";
	unsigned int length_array_vector = 100000;
	Vector** array_vector = new Vector*[length_array_vector];
	
	for (unsigned int i = 0; i < length_array_vector; i++) {
		cout << i << " ";
		array_vector[i] = new Vector(42, (double[]){ 3, 3, 3, 3, 3, 3, 3,
													 3, 3, 3, 3, 3, 3, 3,
													 3, 3, 3, 3, 3, 3, 3,
													 3, 3, 3, 3, 3, 3, 3,
													 3, 3, 3, 3, 3, 3, 3,
													 3, 3, 3, 3, 3, 3, 3});
	}
	cout << "\n";
	
	for (unsigned int i = 0; i < length_array_vector; i++) {
		delete array_vector[i];
	}
	delete[] array_vector;
	
	return 0;
}
