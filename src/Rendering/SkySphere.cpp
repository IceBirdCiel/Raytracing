#include "SkySphere.h"

SkySphere::SkySphere(float scale, Material material, const Camera& camera)
: Sphere(camera.getPosition(), Vector(-90, 0, 0), Vector(scale, scale, scale), material){

}
