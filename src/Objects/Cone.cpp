#include "Cone.h"

Cone::Cone(const Vector& pos, const Vector& rot, const Vector& scale, Material mat) : Object(pos,rot,scale,mat) {}

Cone::Cone(): Object(){}

Ray Cone::getNormals(const Point& p, const Point& o)const {
    Point imp = globalToLocal(p);

    Ray ray;
    ray.origin = imp;
    ray.vector[0] = imp[0];
    ray.vector[1] = 0;
    ray.vector[2] = imp[2];

    ray = localToGlobal(ray);
    ray.vector = ray.vector.normalized();
    return ray;
}

bool Cone::intersect(const Ray& ray, Point& impact)const {
    Ray r = globalToLocal(ray);

    Vector down(0, -1, 0);

    float a = r.vector.dot(down) - cos(1);
    float b = 2 * (r.vector.dot(down)*r.origin.dot(Point(down[0], down[1], down[2]))) 
        - r.vector.dot(Vector(r.origin[0], r.origin[1], r.origin[2]))*pow(cos(1),2);
    //float c = r.origin[0] * r.origin[0] + r.origin[1] * r.origin[1] - (r.origin[2]-1) * (r.origin[2]-1);
    float c = pow(r.origin.dot(Point(down[0], down[1], down[2])),2)- r.origin.dot(r.origin * pow(cos(1),2));

    float delta = (b * b) - (4 * a * c);

    if (cos(1) < 0) {
        if (delta < 0)
        {
            return false;
        }

        else {
            float t1 = (-b - sqrt(delta)) / (2 * a);
            float t2 = (-b + sqrt(delta)) / (2 * a);
            float res = 0;
            if (t1 < 0) {
                res = t2;
            }
            if (t2 < 0) {
                res = t1;
            }
            if (t1 > 0.001 && t2 > 0.001)
            {
                res = (t1 < t2) ? t1 : t2;
            }
            if (res > 0.001) {

                float check = r.origin[0] + res * r.vector[1];

                if (check < r.origin[1]) {
                    float px = r.origin[0] + res * r.vector[0];
                    float py = r.origin[1] + res * r.vector[1];
                    float pz = r.origin[2] + res * r.vector[2];

                    Point i(px, py, pz);
                    if ((i - Point(0, 1, 0)).dot((Point(down[0], down[1], down[2]))) > 0) {
                        impact = i;
                        impact = localToGlobal(impact);
                        return true;
                    }
                }
            }
        }
        return false;
    }
}


Point Cone::getTextureCoordinates(const Point& p) const {
	return Point();
}