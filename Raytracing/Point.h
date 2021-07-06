#define __POINT_CPP__
#ifdef  __POINT_CPP__
#include <iostream>

class Point
{
public:
	Point(float x, float y, float z);
	float dot(Point q);

	float operator[](int index)const;

	Point operator+(Point q)const;
	Point operator-(Point q)const;
	Point operator*(float r)const;
	Point operator/(float r)const;

	Point operator-()const;

private:
	float m_x;
	float m_y; 
	float m_z;
};

std::ostream& operator<<(std::ostream& os, const Point& p);

#endif // __POINT_CPP__