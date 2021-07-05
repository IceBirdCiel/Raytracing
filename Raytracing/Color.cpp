#include "Color.h"

Color::Color(float r, float g, float b)
{
	this->tab[0] = r;
	this->tab[1] = g;
	this->tab[2] = b;

	tab[0] = (tab[0] > 1) ? tab[0] = 1 : tab[0] = 0;
	tab[1] = (tab[1] > 1) ? tab[1] = 1 : tab[1] = 0;
	tab[2] = (tab[2] > 1) ? tab[2] = 1 : tab[2] = 0;
}

Color Color::multiply(Color c)
{
	float r = this->tab[0] * c.tab[0];
	float g = this->tab[1] * c.tab[1];
	float b = this->tab[2] * c.tab[2];

	return Color(r,g,b);
}
