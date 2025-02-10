#include<iostream>
#include "demo_linal.h"

using std::cout;
using std::endl;


int main() {
	
	double coords[3] = { 0, 1, 2 };
	Vector* x = new Vector(3, coords);
	
	Vector* y = new Vector(3, (double[]){ 2, 3, 5 });
	
	x->print();
	y->print();
	
	Vector* z = Vector::sum(x, y);
	z->print();
	
	double c = Vector::scalar_multiply(x, y);
	Vector* d = Vector::vector_multiply(x, y);
	cout << "Scalar multiply: " << c << endl;
	cout << "Vector multiply: \n";
	d->print();
	
	Matrix* subj_1 = new Matrix(5, 7);
	subj_1->fill(3);
	subj_1->changeElement(2, 3, 5);
	subj_1->changeElement(1, 3, 9);
	subj_1->changeElement(3, 2, 8);
	subj_1->print();

	
	for (unsigned int i = 0; i < subj_1->getHeigth(); i++) {
		for (unsigned int j = 0; j < subj_1->getWidth(); j++) {
			cout << "Minor getting, i = " << i << " j = " << j << endl;
			Matrix* minor = subj_1->getMinorMatrix(i, j);
			minor->print();
			delete minor;
		}
	}
	
	
	Matrix* subj_2 = new Matrix(3, 3);
	subj_2->changeElement(0, 0, 1);
	subj_2->changeElement(1, 1, 2);
	subj_2->changeElement(2, 2, 7);
	subj_2->print();
	
	cout << " --- Determinant --- \n";
	cout << subj_2->getDeterminant() << endl;
	cout << " --- Adjugate ---\n";
	Matrix* adjug_subj_2 = subj_2->getAdjugateMatrix();
	adjug_subj_2->print();
	
	cout << " --- GETTING INVERTIBLE MATRIX ---\n";
	Matrix* invertible_subj_2 = subj_2->getInvertibleMatrix();
	invertible_subj_2->print();
	
	Matrix* invertible_invertible_subj_2 = invertible_subj_2->getInvertibleMatrix();
	invertible_invertible_subj_2->print();
	
	Vector** needed_basis_dk_sys1 = new Vector*[3];
	Vector** needed_basis_dk_sys2 = new Vector*[3];
	
	for (unsigned int i = 0; i < 3; i++) {
		needed_basis_dk_sys1[i] = new Vector(3);
		needed_basis_dk_sys2[i] = new Vector(3);
	}
	
	needed_basis_dk_sys1[0]->changeElement(0, 0, 1);
	needed_basis_dk_sys1[0]->changeElement(1, 0, 2);
	needed_basis_dk_sys1[0]->changeElement(2, 0, 1);
	
	needed_basis_dk_sys1[1]->changeElement(0, 0, 2);
	needed_basis_dk_sys1[1]->changeElement(1, 0, 3);
	needed_basis_dk_sys1[1]->changeElement(2, 0, 2);
	
	needed_basis_dk_sys1[2]->changeElement(0, 0, 1);
	needed_basis_dk_sys1[2]->changeElement(1, 0, -1);
	needed_basis_dk_sys1[2]->changeElement(2, 0, 2);
	
	
	needed_basis_dk_sys2[0]->changeElement(0, 0, 1);
	needed_basis_dk_sys2[0]->changeElement(1, 0, 3);
	needed_basis_dk_sys2[0]->changeElement(2, 0, 1);
	
	needed_basis_dk_sys2[1]->changeElement(0, 0, 1);
	needed_basis_dk_sys2[1]->changeElement(1, 0, -1);
	needed_basis_dk_sys2[1]->changeElement(2, 0, 3);
	
	needed_basis_dk_sys2[2]->changeElement(0, 0, 2);
	needed_basis_dk_sys2[2]->changeElement(1, 0, 2);
	needed_basis_dk_sys2[2]->changeElement(2, 0, 1);
	
	cout << "basis coord: \n";
	needed_basis_dk_sys1[0]->print();
	needed_basis_dk_sys1[1]->print();
	needed_basis_dk_sys1[2]->print();
	needed_basis_dk_sys2[0]->print();
	needed_basis_dk_sys2[1]->print();
	needed_basis_dk_sys2[2]->print();
	
	Dekart_System* dk_sys1 = new Dekart_System(needed_basis_dk_sys1);
	Dekart_System* dk_sys2 = new Dekart_System(needed_basis_dk_sys2);
	
	
	
	Matrix* transormer_subj_1 = Dekart_System::getTransformationMatrix(dk_sys1, dk_sys2);
	transormer_subj_1->print();
	
	Matrix* matrix_subj_1 = new Matrix(2, 2);
	matrix_subj_1->changeElement(0, 0, -5);
	matrix_subj_1->changeElement(1, 0, 5);
	matrix_subj_1->changeElement(0, 1, 2);
	matrix_subj_1->changeElement(1, 1, 5);
	
	matrix_subj_1->print();
	matrix_subj_1 = matrix_subj_1->getInvertibleMatrix();
	matrix_subj_1->print();
	
	delete x;
	delete y;
	delete z;
	delete d;
	delete subj_1;
	delete subj_2;
	delete adjug_subj_2;
	delete invertible_subj_2;
	delete invertible_invertible_subj_2;
	
	delete dk_sys1;
	delete dk_sys2;
	delete transormer_subj_1;

	delete matrix_subj_1;
	return 0;
}
