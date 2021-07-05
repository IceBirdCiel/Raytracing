#define __LIGHT_CPP__
#ifdef __LIGHT_CPP__

class Light: Entity
{
public:
	Light();
	Ray getRayToLight(const Point& p)const;
	Ray getRayFromLight(const Point& p)const;
	Vector getVectorToLight(const Point& p)const;
	Vector getVectorFromLight(const Point& p)const;

	Color id;
	Color is;

};

#endif



