#define _USE_MATH_DEFINES
#include <cmath>
#include <xmmintrin.h>
#include "Sphere.h"

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
    __m128 rOrigin = {r.origin[0], r.origin[1], r.origin[2], 0};
    __m128 rVector = {r.vector[0], r.vector[1], r.vector[2], 0};

    float aF = r.vector[0] * r.vector[0] + r.vector[1] * r.vector[1] + r.vector[2] * r.vector[2];
    __m128 a = _mm_hadd_ps(_mm_mul_ps(rVector, rVector));
    float bF = 2 * (r.origin[0] * r.vector[0] + r.origin[1] * r.vector[1] + r.origin[2] * r.vector[2]);
    __m128 two = {2,2,2,2};
    __m128 b = _mm_mul_ps(two, _mm_hadd_ps(_mm_mul_ps(rOrigin, rVector)));
    float cF = r.origin[0] * r.origin[0] + r.origin[1] * r.origin[1] + r.origin[2] * r.origin[2] - 1;
    __m128 one = {1,1,1,1};
    __m128 c = _mm_sub_ps(_mm_hadd_ps(_mm_mul_ps(rOrigin, rOrigin)), one);

    float deltaF = (bF * bF) - (4 * aF * cF);
    __m128 four = {4,4,4,4};
    __m128 delta = _mm_sub_ps(_mm_mul_ps(b, b), _mm_mul_ps(_mm_mul_ps(four, a), c));

    __m128 zero = {0,0,0,0};
    float ltZero = _mm_cvtss_f32(_mm_cmplt_ss(delta, zero));
    float eqZero = _mm_cvtss_f32(_mm_cmpeq_ss(delta, zero));
    if(ltZero != 0) return false;   //if (delta < 0) return false;
    else if(eqZero != 0) {  //else if (delta == 0) {
        float tF = -bF / (2 * aF);
        __m128 t = _mm_div_ss(_mm_sub_ss(zero, b), _mm_mul_ss(two, a));
        float gtZero = _mm_cvtss_f32(_mm_cmpgt_ss(t, zero));

        //if (t > 0) {
        if(gtZero != 0) {
            //float px = r.origin[0] + r.vector[0] * t;
			//float py = r.origin[1] + r.vector[1] * t;
			//float pz = r.origin[2] + r.vector[2] * t;
            float tFloat = _mm_cvtss_f32(t);
            __m128 tVec = {tFloat,tFloat,tFloat,tFloat};
            __m128 p = _mm_add_ps(rOrigin, _mm_mul_ps(rVector, tVec));

            float* pVec = new float[4];
            _mm_store_ps(pVec, p);

			impact[0] = pVec[0];
			impact[1] = pVec[1];
			impact[2] = pVec[2];

            delete [] pVec;
			return true;
		} else return false;
	} else {
        //float t1 = (-b - sqrt(delta))/(2*a);
        __m128 t1 = _mm_div_ss(_mm_sub_ss(_mm_sub_ss(zero, b), _mm_sqrt_ss(delta)), _mm_mul_ps(two, a));
        //float t2 = (-b + sqrt(delta))/(2*a);
        __m128 t2 = _mm_div_ss(_mm_add_ss(_mm_sub_ss(zero, b), _mm_sqrt_ss(delta)), _mm_mul_ps(two, a));

        float t1GeZero = _mm_cvtss_f32(_mm_cmpge_ss(t1, zero));
        float t2GeZero = _mm_cvtss_f32(_mm_cmpge_ss(t2, zero));
        //float res = 0;
        __m128 res = {0,0,0,0};
        //if(t1 < 0){
        if(t1GeZero == 0) {
            res = t2;
        }
        //if(t2 < 0){
        if(t2GeZero == 0) {
            res = t1;
        }
        //if(t1 > 0 && t2 > 0)
        if(t1GeZero != 0 && t2GeZero != 0)
        {
            float t1LtT2 = _mm_cvtss_f32(_mm_cmplt_ss(t1, t2));
            //res = (t1 < t2)? t1:t2;
            res = (t1LtT2 != 0)? t1:t2;
        }
        float resGtZero = _mm_cvtss_f32(_mm_cmpgt_ss(res, zero));
        //if(res > 0){
        if(resGtZero != 0) {
            /*float px = r.origin[0] + r.vector[0]*res;
            float py = r.origin[1] + r.vector[1]*res;
            float pz = r.origin[2] + r.vector[2]*res;*/
            float resFloat = _mm_cvtss_f32(res);
            __m128 resVec = {resFloat, resFloat, resFloat, resFloat};
            __m128 p = _mm_add_ps(rOrigin, _mm_mul_ps(rVector, resVec));

            float* pVec = new float[4];
            _mm_store_ps(pVec, p);

            impact[0] = pVec[0];
            impact[1] = pVec[1];
            impact[2] = pVec[2];

            delete [] pVec;

            impact = localToGlobal(impact);
            return true;
        }  		 		   		  	 		 
        else{
			return false;
		}
	}
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