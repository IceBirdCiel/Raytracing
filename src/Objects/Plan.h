#pragma once
#include "../Math/Vector.h"
//#include "Object.h"
#include "../Math/Matrix.h"

class Plan // : public Object
{
public:
    Plan(float width, float height);



private:
    float width;
    float height;

    Vector position;
    Vector rotation;
    Vector size;
    Matrix trans;
    Matrix transInv;
};
