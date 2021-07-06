#include <iostream>
#include "Vector.h"

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
}