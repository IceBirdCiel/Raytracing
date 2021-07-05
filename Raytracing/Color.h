#define __COLOR_CPP__
#ifdef __COLOR_CPP__

class Color
{
public:
	Color(float r, float g, float b);
	Color multiply(Color c);

private:
	float tab[3];
};

//C'EST PAS OPTI

#endif // __COLOR_CPP


