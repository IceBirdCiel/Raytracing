#include "Ray.h"

Ray::Ray(float ox, float oy, float oz, float vx, float vy, float vz) : origin(Point(ox, oy, oz)), vector(Vector(vx,vy,vz))
{
}

Ray::Ray(Point o, Vector v): origin(o), vector(v)
{
}
