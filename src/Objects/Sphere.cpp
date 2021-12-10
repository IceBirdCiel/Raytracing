#define _USE_MATH_DEFINES


#include <cmath>
#include "Sphere.h"
#include <xmmintrin.h>

Sphere::Sphere(const Vector&  pos, const Vector&  rot, const Vector& scale, const Material& mat): Object(pos,rot,scale,mat) {}
Sphere::Sphere(const Vector&  pos, const Vector&  rot, const Vector& scale, const Material& mat, const Material& mat2, int repeat): Object(pos,rot,scale,mat,mat2,repeat) {}

Sphere::Sphere(): Object(){}

Ray Sphere::getNormals(const Point& impact, const Point& observer) const {
	Point obs = globalToLocal(observer);
	Point imp = globalToLocal(impact);
	Vector v = sqrt(pow(obs[0], 2) + pow(obs[1], 2) + pow(obs[2], 2)) < 1 ? Vector(-imp[0], -imp[1], -imp[2]) : Vector(imp[0], imp[1], imp[2]);
	Ray r(imp, v.normalized());
	r = localToGlobal(r);
    r.vector = r.vector.normalized();
	return r;
}

__m128 _mm_hadd_ps(__m128 val) {
    /* val =              (1  2  3  4)
     * tmp = shuffle ->   (3  4  1  2)
     * tmp2 = addition -> (4  6  4  6)
     * tmp = shuffle ->   (6  4  6  4)
     * return addition -> (10 10 10 10)
     */
    __m128 tmp = _mm_shuffle_ps(val,val, _MM_SHUFFLE(1,0,3,2));
    __m128 tmp2 = _mm_add_ps(val,tmp);
    tmp = _mm_shuffle_ps(tmp2,tmp2, _MM_SHUFFLE(0, 1,0,1));
    return _mm_add_ps(tmp,tmp2);
}

bool Sphere::intersect(const Ray & ray, Point& impact)const {
    Ray r = globalToLocal(ray);

    __m128 zero = {0,0,0,0};
    __m128 one = {1,1,1,1};
    __m128 minusOne = {-1,-1,-1,-1};
    __m128 two = {2,2,2,2};
    __m128 four = {4,4,4,4};
    //Conversion de r en m128
    __m128 rVector = {r.vector[0],r.vector[1],r.vector[2],0};
    __m128 rOrigin = {r.origin[0],r.origin[1],r.origin[2],0};

    __m128 tmp = _mm_mul_ps(rVector,rVector);
    __m128 a = _mm_hadd_ps(tmp);// vec[0]² + vec[1]² + vec[2]²


    tmp = _mm_mul_ps(rOrigin,rVector);
    tmp = _mm_mul_ps(two,tmp);// 2*(or[0]*vec[0] + or[1]*vec[1] + or[2]*vec[2])
    __m128 b = _mm_hadd_ps(tmp);

    tmp = _mm_mul_ps(rOrigin,rOrigin);
    tmp = _mm_hadd_ps(tmp);//(or[0]² + or[1]² + or[2]²) -1
    __m128 c = _mm_sub_ps(tmp,one);


    __m128 tmp2 = _mm_mul_ps(b,b); //b²
    tmp = _mm_mul_ps(four,a); //4a
    tmp = _mm_mul_ps(tmp,c);//4ac
    __m128 del = _mm_sub_ps(tmp2,tmp); //b² - 4ac

    __m128 condition = _mm_cmplt_ss(del,zero);
    if(((float*)(&condition))[0]  != 0 ) return false; //DELTA < 0
    else{
        condition = _mm_cmpeq_ss(del,zero);
        if(((float*)(&condition))[0] != 0){ // DELTA  == 0
            tmp = _mm_mul_ps(two,a);
            tmp2 = _mm_mul_ps(minusOne, b);
            __m128 t = _mm_div_ps(tmp2,tmp);
            condition = _mm_cmpgt_ss(t,zero);
            if(((float*)(&condition))[0]  != 0 ){
                __m128 imp = _mm_mul_ps(t,rVector);
                imp = _mm_add_ps(imp,rOrigin);
                float* floatImp = ((float*)(&imp));
                impact = {floatImp[0],floatImp[1], floatImp[2]};
                return true;
            }else{
                return false;
            }
        }else{ // DELTA > 0
            __m128 res = zero;
            tmp = _mm_mul_ps(minusOne, b);// -b
            tmp2 = tmp;// -b
            __m128 tmp3 = _mm_sqrt_ps(del);//sqrt(delta)
            tmp = _mm_sub_ps(tmp,tmp3);// -b - sqrt(delta)
            tmp2 = _mm_add_ps(tmp2,tmp3);// -b + sqrt(delta)
            tmp3 = _mm_mul_ps(two,a);//2*a

            tmp = _mm_div_ps(tmp,tmp3);// (-b - sqrt(delta))/2*a
            tmp2 = _mm_div_ps(tmp2,tmp3);// (-b + sqrt(delta))/2*a

            condition = _mm_cmplt_ss(tmp,zero);
            if(((float*)(&condition))[0]  != 0 ) {// if(t1 < 0)
                res = tmp2;
            }
            condition = _mm_cmplt_ss(tmp2,zero);
            if(((float*)(&condition))[0]  != 0 ) {// if(t2 < 0)
                res = tmp;
            }
            condition = _mm_cmplt_ss(tmp2,zero);
            if(((float*)(&condition))[0]  != 0 ) {// if(t1 < 0)
                res = tmp;
            }
            // if(t1 > 0 && t2 > 0)
            //en multipliant les deux conditions, condition ne peur etre à 1 1 1 1 que si les deux sont a 1 1 1 1
            condition = _mm_mul_ps(_mm_cmpgt_ss(tmp,zero),_mm_cmpgt_ss(tmp,zero));
            if(((float*)(&condition))[0]  != 0 ) {// if(t1 < 0)

                //miam la condition ternaire qui devient dégueu
                condition = _mm_cmplt_ss(tmp,tmp2);
                if(((float*)(&condition))[0]  != 0 ) {//if(t1 < t2)
                    res = tmp;
                }else{
                    res = tmp2;
                }
            }

            condition = _mm_cmpgt_ps(res,zero);
            if(((float*)(&condition))[0]  != 0 ) {// if(res > 0)

                __m128 imp = _mm_mul_ps(res,rVector);
                imp = _mm_add_ps(rOrigin,imp);
                float* floatImp = ((float*)(&imp));
                impact = {floatImp[0],floatImp[1], floatImp[2]};
                impact = localToGlobal(impact);
                return true;
            }else {
                return false;
            }
        }
    }
    //calcul de a

    /*float a2 = r.vector[0] * r.vector[0] + r.vector[1] * r.vector[1] + r.vector[2] * r.vector[2];
    float b2 = 2 * (r.origin[0] * r.vector[0] + r.origin[1] * r.vector[1] + r.origin[2] * r.vector[2]);
    float c2 = r.origin[0] * r.origin[0] + r.origin[1] * r.origin[1] + r.origin[2] * r.origin[2] - 1;

    float delta2 = (b * b) - (4 * a * c);

    if (delta2 < 0) return false;
    else if (delta2 == 0) {
        float t2 = -b / (2 * a);
        if (t2 > 0) {
            float px = r.origin[0] + r.vector[0] * t2;
            float py = r.origin[1] + r.vector[1] * t2;
            float pz = r.origin[2] + r.vector[2] * t2;
            impact[0] = px;
            impact[1] = py;
            impact[2] = pz;
            return true;
        }
        else return false;
    }

    else{
        float t12 = (-b2 - sqrt(delta2))/(2*a2);
        float t22 = (-b2 + sqrt(delta2))/(2*a2);
        float res2 = 0;
        if(t1 < 0){
            res2 = t22;
        }
        if(t2 < 0){
            res2 = t12;
        }
        if(t12 > 0 && t22 > 0)
        {
            res2 = (t12 < t22)? t12:t22;
        }
        if(res2 > 0){
            float px = r.origin[0] + r.vector[0]*res;
            float py = r.origin[1] + r.vector[1]*res;
            float pz = r.origin[2] + r.vector[2]*res;
            impact[0] = px;
            impact[1] = py;
            impact[2] = pz;
            impact = localToGlobal(impact);
            return true;
        }
        else{
            return false;
        }
    }*/
}


Point Sphere::getTextureCoordinates(const Point &p) const {
    Point lp = globalToLocal(p);
    float rho = std::sqrt(lp.dot(lp));
    float theta = std::atan2(lp[1], lp[0]);
    float sigma = std::acos(lp[2]/rho);
    float x = -theta/(2*M_PI)+0.5f;
    float y = sigma/M_PI;
    return Point(x, y, 0);
}
Material Sphere::getMaterial(const Point& p) const {
    //return m_mat;
    if(!m_duo)return m_mat;
    //std::cout << "IBIDIBABIDIBOU ! m_duo " << m_duo << "\n";
    Point coordinates = getTextureCoordinates(p);
    float x = fmod(coordinates[0]*2*m_repeat, 2);
    float y = fmod(coordinates[1]*m_repeat, 2);
    if(y < 1.f){
        x = 2-x;
    }
    if( x < 1.f){
        return m_mat;
    }else{
        return m_mat2;
    }
}