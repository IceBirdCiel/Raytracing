#pragma once			    	 			 	 	  
#include <iostream>			   

class Vector
{
public:
	Vector(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {

	}

	float norm() const;
	Vector normalized() const;
	float dot(Vector v) const;

	float operator [](int index) const;
	float& operator [](int index);
	Vector operator +(Vector v) const;   // value = vector1+vector2
	Vector operator -(Vector v) const;   // value = vector1-vector2
	Vector operator -() const;           // value = -vector
	Vector operator /(float value) const;// value = vector/float
	Vector operator *(float value) const;// value = vector*float 


private:
	float m_x;
	float m_y;
	float m_z;
};
std::ostream& operator<<(std::ostream& os, const Vector& v);


