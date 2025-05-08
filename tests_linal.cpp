#include "linal.h"

#include<cmath>
#include<iostream>
#include<vector>

#include <type_traits>

#include<string>

using std::cout;
using std::endl;
using std::string;

#define PI 3.1415926535897932384626433

int main() {
	std::cout << std::boolalpha;
	char tmp;

9	Matrix x = Matrix(3, 3);
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
	Matrix y(x);
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
	Matrix sum_xy = x.getSum(y);
	sum_xy.print();

	cout << "Get multiplication of x and y:\n";
	Matrix multiplication_xy = x.getMultiplication(y);
	multiplication_xy.print();

	cout << " --- Vector Part --- \n";
	Vector a(3);
	a.changeElement(0, 0, 0.5);
	a.changeElement(1, 0, 1.5);
	a.changeElement(2, 0, 2.5);

	cout << "Original a:\n";
	a.print();

	cout << "Clone of a, b:\n";
	Vector b = Vector(a);
	b.print();

	cout << "Sum a and b:\n";
	Vector sum_ab = a.getSum(b);
	sum_ab.print();

	cout << "Subtract a and b:\n";
	Vector subtract_ab = a.getSubtraction(b);
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
	double scalar_multiplication_ab = a.get_scalar_multiplication(b);
	cout << scalar_multiplication_ab << "\n";

	cout << "Vector multiplication of a and b:\n";
	Vector vector_multiplication_ab = b.get_vector_multiplication(b);
	vector_multiplication_ab.print();

	cout << "Get module of the Vector a:\n";
	double module_a = a.getModule();
	cout << "Module: " << module_a << "\n";

	cout << "Get rotated on pi Vector of Vector a:\n";
	cout << a.getRotated(PI) << '\n';

	cout << "Get rotated on pi / 2 by Z, and pi / 2 by Y:\n";
	cout << a.getRotated(PI / 2, PI / 2) << '\n';

	cout << "Check Vector initialisation through initialiser{}, Vector check_initialiser(3, (double[]){1, 2, 3}):\n";
	Vector<double> check_initialiser(3, (double[]){ 1, 2, 3 });
	cout << check_initialiser << '\n';

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
	cout << "\tx == x: " << (x == x);
	cout << "\tx == x * 2: " << (x == x * 2);

	cout << "Operator != overload check:\n";
	cout << "\tx != x: " << (x != x);
	cout << "\tx != x / 2: " << (x != x / 2);

	cout << "Operator << overload check, cout << x << \" GG \\n\":\n";
	cout << x  << " GG \n" << '\n';

	cout << "Operator [] overload check, cout << x[1][2] << \'\\n\':\n";
	cout << x[1][2];

	cout << "Operator [] overload check, x[1][2] = -0.54:\n";
	x[1][2] = -0.54;
	cout << x;

	std::cin >> tmp;

	cout << "Dinamic array of Matrix initialisation check:\n";
	unsigned int length_array_matrix = 1000;
	Matrix<double>** array_matrix = new Matrix<double>*[length_array_matrix];

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

	cout << "Operator [] overload check, cout << a[1] << \"\\n\":\n";
	cout << a[1] << "\n";

	cout << "Operator [] overload check, a[2] = 2.28:\n";
	a[2] = 2.28;
	cout << a << "\n";

	cout << "Operator << overload check, cout << a << \" GG \\n\":\n";
	cout << a << " GG \n";

	cout << "Operator >> overload check, cin >> new_vect (DIMENSION = 4):\n";
	Vector new_vect(4);
	std::cin >> new_vect;
	cout << new_vect << "\n";

	std::cin >> tmp;

	cout << "Dinamic array of Vectors initialisation check:\n";
	unsigned int length_array_vector = 1000;
	Vector<double>** array_vector = new Vector<double>*[length_array_vector];

	for (unsigned int i = 0; i < length_array_vector; i++) {
		cout << i << " ";
		array_vector[i] = new Vector(42, (double)3);
	}
	cout << "\n";

	for (unsigned int i = 0; i < length_array_vector; i++) {
		delete array_vector[i];
	}
	delete[] array_vector;

	cout << " --- Templates checking --- \n";
	cout << "Matrix<bool> initialisation:\n";
	cout << std::boolalpha;
	Matrix<bool> bool_matrix(3, 3);
	cout << bool_matrix;

	cout << "Matrix<char> initialisation:\n";
	Matrix<char> char_matrix(3, 3);
	cout << char_matrix;

	cout << "Matrix<bool>[i][i] = true:\n";
	for (unsigned int i = 0; i < bool_matrix.getHeight(); i++) {
		for (unsigned int j = 0; j < bool_matrix.getWidth(); j++) {
			if (i == j) {
				bool_matrix[i][j] = true;
			}
		}
	}
	cout << bool_matrix;

	cout << "Matrix<char> fill with \':\':\n";
	char_matrix.fill(':');
	cout << char_matrix;

	cout << "Matrix<char> + Matrix<bool>:\n";
	cout << char_matrix + bool_matrix;

	cout << "Matrix<bool> + Matrix<char>:\n";
	cout << bool_matrix + char_matrix;

	cout << "Matrix<char> * 5:\n";
	cout << char_matrix * 5 / 2;

	cout << "Matrix<char> * Matrix<bool>:\n";
	cout << char_matrix * bool_matrix;

	cout << "Get determinant of Matrix<bool>:\n";
	cout << bool_matrix.getDeterminant() << '\n';

	cout << "Get adjugated Matrix of Matrix<bool>:\n";
	cout << bool_matrix.getAdjugated();

	cout << "Matrix<short> filled with zeros:\n";
	Matrix<short> short_matrix(3, 3);
	cout << short_matrix;

	cout << "Matrix<bool> filled with zeros:\n";
	Matrix<bool> zeros_bool_matrix(3, 3);
	cout << zeros_bool_matrix;

	cout << "Matrix<short> == Matrix<bool> filled with zeros:\n";
	cout << (short_matrix == zeros_bool_matrix) << '\n';

	cout << "Matrix<short> == Matrix<char>:\n";
	cout << (short_matrix == char_matrix) << '\n';

	cout << "Matrix<string> initialisation:\n";
	Matrix<string> string_matrix(3, 3);
	cout << string_matrix;

	cout << "Matrix<string> fill with \"sigma\" and Matrix<string>[1][1] = \"fijma\":\n";
	string_matrix.fill("sigma");
	string_matrix[1][1] = "fijma";
	cout << string_matrix;

	cout << "Matrix<string> + Matrix<string> filled with \"gg wp\":\n";
	Matrix<string> ggwp_matrix(3, 3);
	ggwp_matrix.fill("gg wp");
	cout << string_matrix + ggwp_matrix;

	cout << "Matrix<unsigned int> filled with 228:\n";
	Matrix<unsigned int> unsignedInt_matrix(3, 3);
	unsignedInt_matrix.fill(228);
	cout << unsignedInt_matrix;

	cout << "Matrix<long long int> filled with 42:\n";
	Matrix<long long int> longLongInt_matrix(3, 3);
	longLongInt_matrix.fill(42);
	cout << longLongInt_matrix;

	cout << "Type conversion check: (Matrix<char>)Matrix<unsigned int>:\n";
	Matrix<char> result_of_conversion = (Matrix<char>)unsignedInt_matrix;
	cout << result_of_conversion;

	cout << "Matrix<unsigned int> == Matrix<long long int>:\n";
	cout << (unsignedInt_matrix == longLongInt_matrix) << '\n';

	cout << "Matrix<Matrix<double>> initialisation:\n";
	Matrix<Matrix<double>> matrix_matrix(4, 3, Matrix<double>(4, 3, -0.5));
	cout << matrix_matrix;

	cout << "Matrix<Matrix<Matrix<double>>> initialisation:\n";
	Matrix<Matrix<Matrix<double>>> giga_matrix(2, 2, Matrix<Matrix<double>>(4, 3, Matrix<double>(4, 3, -1)));
	cout << giga_matrix;

	cout << "Matrix<Vector<char>> initialisation:\n";
	Matrix<Vector<char>> vector_matrix(3, 4, Vector<char>(5, 'V'));
	cout << vector_matrix;

	cout << "Vector<char> initialisation:\n";
	Vector<char> char_vector(3);
	cout << char_vector << '\n';

	cout << "Vector<char> filled with \'=\'\n";
	char_vector.fill('=');
	cout << char_vector << '\n';

	cout << "Rotate Vector<char> by PI / 2:\n";
	cout << char_vector.getRotated(PI / 2) << '\n';

	cout << "Scalar multiplication of Vector<char> with Vector<bool> filled with true:\n";
	Vector<bool> true_vector(3);
	true_vector.fill(true);
	cout << char_vector.get_scalar_multiplication(true_vector) << '\n';

	cout << "Scalar multiplication of Vector<bool> filled with true with Vector<char>:\n";
	cout << true_vector.get_scalar_multiplication(char_vector) << '\n';

	cout << "vector multiplication of Vector<char> with Vector<bool> filled with true:\n";
	cout << char_vector.get_vector_multiplication(true_vector) << '\n';

	cout << "vector multiplication of Vector<bool> filled with true with Vector<char>:\n";
	cout << true_vector.get_vector_multiplication(char_vector) << '\n';

	cout << "Vector<Vector<char>> initialisation:\n";
	Vector<Vector<char>> vector_vector(3, Vector<char>(3, 'S'));
	cout << vector_vector << '\n';

	cout << "Vector<Vector<Vector<Vector<char>>>> initialisation:\n";
	Vector<Vector<Vector<Vector<char>>>> veryGiga_vector( 2, Vector<Vector<Vector<char>>>(3, Vector<Vector<char>>(3, Vector<char>(3, 'S'))) );
	cout << veryGiga_vector << '\n';

	cout << "Vector<Vector<string>> initialisation:\n";
	Vector<Vector<string>> string_vector_vector(3, Vector<string>(5, "fijma"));
	cout << string_vector_vector << '\n';

	/* ATTEMPT WAS SUCCESFUL, KEEP IN MIND, DON'T DO STAFF LIKE THIS, IDK HOW TO FIX IT NOW
	cout << "Attempt to destroy type safety, Vector<Vector<char>> corrupt_vector(3, Vector<int>(5, 1)):\n";
	Vector<Vector<char>> corrupt_vector(3, Vector<int>(5, 1));
	cout << corrupt_vector << '\n';
	*/


	return 0;
}
