#define _USE_MATH_DEFINES
#include <xmmintrin.h>
#include <cmath>
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

__m128 _mm_hadd_ps(__m128 val){
    __m128 tmp = _mm_shuffle_ps(val, val, _MM_SHUFFLE(1, 0, 3, 2));
    __m128 tmp2 = _mm_add_ps(val, tmp);
    tmp = _mm_shuffle_ps(tmp2, tmp2, _MM_SHUFFLE(0, 1, 0, 1));
    return _mm_add_ps(tmp, tmp2);
}

bool Sphere::intersect(const Ray & ray, Point& impact)const {
    Ray r = globalToLocal(ray);

    __m128 origin = {r.origin[0],r.origin[1],r.origin[2],0};
    __m128 vec = {r.vector[0], r.vector[1], r.vector[2], 0};

    __m128 tmpA = _mm_mul_ps(vec,vec);
    tmpA = _mm_hadd_ps(tmpA);

    __m128 tmpB = _mm_mul_ps(vec,origin);
    tmpB = _mm_hadd_ps(tmpB);
    tmpB = _mm_mul_ps(_mm_set_ss(2), tmpB);

    __m128 tmpC = _mm_mul_ps(origin, origin);
    tmpC = _mm_hadd_ps(tmpC);
    tmpC = _mm_sub_ps(tmpC, _mm_set_ss(1));

    __m128 tmpDelta = _mm_mul_ss(tmpB, tmpB);
    __m128 ac = _mm_mul_ss(tmpA,tmpC);
    ac = _mm_mul_ps(ac, _mm_set_ss(4));
    tmpDelta = _mm_sub_ps(tmpDelta, ac);

    __m128 inferior = _mm_cmplt_ss(tmpDelta, _mm_set_ss(0));
    float inf = _mm_cvtss_f32(inferior);
    __m128 equalTo = _mm_cmpeq_ss(tmpDelta, _mm_set_ss(0));
    float equal = _mm_cvtss_f32(equalTo);

	if (inf != 0) return false;
	else if (equal != 0) {
        __m128 t0 = _mm_div_ss(_mm_mul_ss(_mm_set_ss(-1), tmpB), _mm_mul_ss(_mm_set_ss(2), tmpA)); // bonne chance
		__m128 tsuperieur = _mm_cmpgt_ss(t0, _mm_set_ss(0));
        float tsup = _mm_cvtss_f32(tsuperieur);
        if (tsup != 0) {
            __m128 p = _mm_mul_ps(vec, t0);
            p = _mm_add_ps(origin, p);
            float* pres = new float(4);
            _mm_store_ps(pres, p);
            impact[0] = pres[0];
			impact[1] = pres[1];
			impact[2] = pres[2];
			return true;
		}
        return false;
	}

	else{
        __m128 tmpT1 =  _mm_div_ss(_mm_sub_ss(_mm_sub_ss(_mm_set_ss(0), tmpB), _mm_sqrt_ss(tmpDelta)), _mm_mul_ss(_mm_set_ss(2), tmpA));
        __m128 tmpT2 =  _mm_div_ss(_mm_add_ss(_mm_sub_ss(_mm_set_ss(0), tmpB), _mm_sqrt_ss(tmpDelta)), _mm_mul_ss(_mm_set_ss(2), tmpA));

        __m128 tmpRes = _mm_set_ss(0);

        __m128 t1inf = _mm_cmpge_ss(tmpT1, _mm_set_ss(0));
        __m128 t2inf = _mm_cmpge_ss(tmpT2, _mm_set_ss(0));
        float t1f = _mm_cvtss_f32(t1inf);
        float t2f = _mm_cvtss_f32(t2inf);

        if(t1f  == 0){
            tmpRes = tmpT2;
        }
        if(t2f == 0){
            tmpRes = tmpT1;
        }
        if(t1f != 0 && t2f != 0)
        {
            __m128 compareT1T2 = _mm_cmplt_ss(tmpT1 , tmpT2);
            float t1t2 = _mm_cvtss_f32(compareT1T2);
            if(t1t2 != 0){
                tmpRes = tmpT1;
            }
            else{
                tmpRes = tmpT2;
            }
        }
        __m128 tres = _mm_cmpgt_ss(tmpRes, _mm_set_ss(0));
        float result = _mm_cvtss_f32(tres);
        if(result != 0){
            float res = _mm_cvtss_f32(tmpRes);
            __m128 resVec = {res, res, res,res};
            __m128 p = _mm_mul_ps( vec, resVec);
            p = _mm_add_ps(origin, p);

            float* pres = new float[4];
            _mm_store_ps(pres, p);
            impact[0] = pres[0];
            impact[1] = pres[1];
            impact[2] = pres[2];
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