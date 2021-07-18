#include <iostream>
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Rendering/Image.h"

int main(int argc, char** argv) {

    std::cout << "Hello World !" << std::endl;
    //-------- TEST VECTOR --------
    Vector v1(0, 1, 5);
    std::cout << "v1 " << v1 << std::endl;
    Vector v2(-2, 4, 3);
    std::cout << "v2 " << v2 << std::endl;

    std::cout << "v1+v2 = " << (v1 + v2) << std::endl;
    std::cout << "v1-v2 = " << (v1 - v2) << std::endl;
    std::cout << "v1*2 = " << (v1 * 2) << std::endl;
    std::cout << "v1*0.5f = " << (v1 * 0.5f) << std::endl;

    Matrix m1;
    Matrix m2;
    m1(0, 1) = m2(1, 0) = m1(0, 3) = m2(3, 0) = 2;
    std::cout << "m1 : " << std::endl << m1.toString();
    std::cout << "m2 : " << std::endl << m2.toString();
    Matrix m3 = m1 * m2;
    std::cout << "m3 = m1 * m2 : " << std::endl << m3.toString() << std::endl;;
    std::cout << "m3 * v1 : " << std::endl << (m3 * v1) << std::endl;;

    Image img(500,200,Color(1.0,0.6,0.8));

    Color black(0,0,0);
    Color white(1,1,1);
    for(int y = 0; y < img.getHeight(); ++y){
        for(int x = 0; x < img.getWidth(); ++x){
            if((int)(y/10.0f)%2 == 0 && (int)(x/10.0f)%2 == 0){
                img.setColor(x,y,black);
            }else{
                img.setColor(x,y,white);
            }
        }
    }
    img.getColor(0,0);
    img.save("checkerboard");

    int x = 0;
    int y = 0;
    Color c = img.getColor(x,y);
    std::cout << "pixel at (" << x << ", " << y << ") = (" << c.r << " " << c.g << " " << c.b << ")";

}