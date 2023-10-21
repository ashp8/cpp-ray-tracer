#ifndef RAYTRACING_OBJECTBASE_HPP
#define RAYTRACING_OBJECTBASE_HPP
#include "../qbLinAlg/qbVector.h"
#include "./ray.h"

namespace qbRT{
    class ObjectBase{
    public:
        ObjectBase();
        virtual ~ObjectBase();

        // Function to test for test for intersection
        virtual bool TestIntersection (const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

        // Function to test whether two floating point memebers are close to being equal.

        bool CloseEnough(const double f1, const double f2);

    public:
        // base color of the object
        qbVector<double> m_baseColor{3};
    };
};

#endif //RAYTRACING_OBJECTBASE_HPP
