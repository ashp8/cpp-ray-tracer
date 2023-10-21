#include "../include/objectbase.h"
#include <math.h>

#define EPSILON 1e-21f

qbRT::ObjectBase::ObjectBase() {

}

qbRT::ObjectBase::~ObjectBase(){

}

bool qbRT::ObjectBase::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) {

    return false;
}

// Function to test two floating point number are close to being equal.
bool qbRT::ObjectBase::CloseEnough(const double f1, const double f2) {
    return fabs(f1 - f2) < EPSILON;
}

void qbRT::ObjectBase::SetTransformMatrix(const qbRT::GTform &transformMatrix){
    m_transformMatrix = transformMatrix;
};
