#ifndef RAYTRACING_OBJSPHERE_H
#define RAYTRACING_OBJSPHERE_H

#include "./objectbase.h"

namespace qbRT{
    class ObjSphere : public ObjectBase{
    public:
        /* The Default constructor
         * this will define a unit sphere at the origin
         * */
        ObjSphere();
        virtual ~ObjSphere() override;

        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

    private:

    };
};

#endif //RAYTRACING_OBJSPHERE_H
