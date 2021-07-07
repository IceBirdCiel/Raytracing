#include <iostream>
#include "Vector.h"
#include "matrix.h"

int main(int argc, char** argv) {

	std::cout << "Hello World !" << std::endl;
	//-------- TEST VECTOR --------
	Vector v1(0, 1, 5);
	std::cout << "v1 " << v1 << std::endl;
	Vector v2(-2, 4, 3);
	std::cout << "v2 " << v2 << std::endl;

	std::cout << "v1+v2 = " << (v1 + v2) << std::endl;
	std::cout << "v1-v2 = " << (v1 - v2) << std::endl;
	std::cout << "v1*2 = " << (v1 * 2) << std::endl;
	std::cout << "v1*0.5f = " << (v1 * 0.5f) << std::endl;

	Matrix m1;
	Matrix m2;
	m1(0, 1) = m2(1, 0) = m1(0, 3) = m2(3, 0) = 2;
	std::cout << "m1 : " << std::endl << m1.toString();
	std::cout << "m2 : " << std::endl << m2.toString();
	Matrix m3 = m1 * m2;
	std::cout << "m3 = m1 * m2 : " << std::endl << m3.toString();
	std::cout << "m3 * v1 : " << std::endl << (m3 * v1);
}