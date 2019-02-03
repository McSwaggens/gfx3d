#include "Matrix.h"
#include <iostream>

void MatrixTests()
{
	Matrix<2, 2> a =
	{
	//  X Y
		1, 3, // X
		2, -1 // Y
	};

	Matrix<2, 2> b =
	{
	//  X Y
		2, -4, // X
		3, 0   // Y
	};

	// std::cout << "a: " << a;
	// std::cout << "b: " << b;
	// std::cout << "a*b: " << (a * b);

	Matrix<4, 4> c =
	{
	//  X    Y    Z    W
		1,   0,  -1,   0,  // X
		0,   1,  -1,   0,  // Y
		0,   0,   1,   0,  // Z
		0,   0,   0,   1   // W
	};

	Vector d { 1, 1, 0.2, 1 };
	std::cout << "c: " << c;
	std::cout << "c*" << d << " = " << (c * d) << std::endl;

	Matrix<2, 2> e =
	{
	//  X Y
		0, 2, // X
		4, 0 // Y
	};

	// std::cout << "a*" << d << " = " << (a * d) << std::endl;
	// std::cout << "b*" << d << " = " << (b * d) << std::endl;
	// std::cout << std::endl << "e: " << e;
	// std::cout << "e*" << d << " = " << (e * d) << std::endl;
}
