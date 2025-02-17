#include<iostream>
#include "linal.h"

using std::cout;
using std::endl;


int main() {
	
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
	
	cout << "Operator * overload with scalar check, x * 5 * 2 * 42:\n";
	Matrix operator_multiply_x = x * 5 * 2 * 42;
	operator_multiply_x.print();
	
	cout << "Operator * overload with itself check, x * x * x:\n";
	Matrix operator_multiply_itself_x = x * x * x;
	operator_multiply_itself_x.print();
	
	cout << "Operator / overload with scalar check, x / 5 / 2 / 42:\n";
	Matrix operator_divide_x = x / 5 / 2 / 42;
	operator_divide_x.print();
	
	cout << " --- Dekart System Part --- \n";
	cout << "Dekart System init dek_sys_x check:\n";
	Dekart_System dek_sys_x = Dekart_System();
	dek_sys_x.print();
	
	cout << "Dekart System changeBaseDot() and changeBasis() check:\n";
	Dekart_System dek_sys_y = Dekart_System();
	
	dek_sys_y.changeBaseDot( Vector(3, (double[]){ 2, 2, 8 }));
	dek_sys_y.changeBasis(0, Vector(3, (double[]){ 0, 0, 1 }));
	dek_sys_y.changeBasis(1, Vector(3, (double[]){ 1, 0, 0 }));
	dek_sys_y.changeBasis(2, Vector(3, (double[]){ 0, 1, 0 }));
	
	dek_sys_y.print();
	
	return 0;
}
