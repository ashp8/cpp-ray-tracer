#ifndef RAYTRACING_LIGHTBASE_H
#define RAYTRACING_LIGHTBASE_H

#include <memory>
#include "../qbLinAlg/qbVector.h"
#include "./ray.h"
#include "./objectbase.h"

namespace qbRT{
    class LightBase{
    public:
        LightBase();
        virtual ~LightBase();

        // function to compute illumination contribution

        virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                         const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                         const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                         qbVector<double> &color, double &intensity);
    public:
        qbVector<double> m_color {3};
        qbVector<double> m_location {3};
        double m_intensity;
    };
};

#endif //RAYTRACING_LIGHTBASE_H
