#include "../include/objsphere.h"
#include <cmath>

qbRT::ObjSphere::ObjSphere() {

}

qbRT::ObjSphere::~ObjSphere() {

}

bool qbRT::ObjSphere::TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint,
                                       qbVector<double> &localNormal, qbVector<double> &localColor) {
    // Compute the values of a, b and c.
    qbVector<double> vhat = castRay.m_lab;
    vhat.Normalize();

    /*Note that a is equal to the squared magnitude
     * of the direction of the cast ray. As this will
     * be a unit vector. we can conclude the value of
     * a will be 1
     * */
    // a = 1.0;
    double b = 2.0 * qbVector<double>::dot(castRay.m_point1, vhat);
    double c = qbVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

    // Test Whether we have the intersection
    double intTest = (b*b) - 4.0 * c;
    if(intTest > 0.0){
        double numSqrt = sqrtf(intTest);
        double t1 = (-b + numSqrt) / 2.0;
        double t2 = (-b - numSqrt) / 2.0;
        /* if either t1 or t2 are negative, then at least part of this object is behind the camera we will ignore it*/
        if((t1 < 0.0) || t2 < 0.0)
            return false;
        else{
            // Determine which point of intersection was closest to camera
            if(t1 < t2)
                intPoint = castRay.m_point1 + (vhat * t1);
            else
                intPoint = castRay.m_point1 + (vhat * t2);
        }
        // compute the local normal ()
        localNormal = intPoint;
        localNormal.Normalize();
        return true;
    }
    else return false;
}
