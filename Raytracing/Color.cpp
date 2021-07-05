#include "Color.h"

Color::Color(float r, float g, float b)
{
	this->tab[0] = r;
	this->tab[1] = g;
	this->tab[2] = b;
}

Color Color::multiply(Color c)
{
	float r = this->tab[0] * c.tab[0];
	float g = this->tab[1] * c.tab[1];
	float b = this->tab[2] * c.tab[2];

	return Color(r,g,b);
}
