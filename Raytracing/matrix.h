#pragma once

#include <array>
#include <iostream>
#include <sstream>

// 4x4 transformation matrix
class Matrix
{
public:
	Matrix();
	float& operator()(int i, int j);
	Matrix inverse();
	std::string toString();
	
private:
	std::array<std::array<float, 4>, 4> _tab;
};

