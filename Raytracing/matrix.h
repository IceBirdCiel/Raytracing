#pragma once

#include <array>
#include <iostream>
#include <sstream>
#include "Vector.h"
#include "Point.h"

// 4x4 transformation matrix
class Matrix
{
public:
	Matrix();
	Matrix(const Matrix& source);
	float& operator()(int i, int j);
	float operator()(int i, int j) const;
	Matrix inverse();
	std::string toString();
	Matrix operator*(const Matrix& m);
	Matrix operator*(const Vector& v);
	Matrix operator*(const Point& p);
	
private:
	std::array<std::array<float, 4>, 4> _tab;
};

