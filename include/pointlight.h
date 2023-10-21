#ifndef RAYTRACING_POINTLIGHT_H
#define RAYTRACING_POINTLIGHT_H
#include "./lightbase.h"

namespace qbRT {
    class PointLight : public LightBase {
    public:
        PointLight();

        // Override the destruction
        virtual ~PointLight() override;

        virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                         const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                         const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                         qbVector<double> &color, double &intensity) override;

    };
}
#endif //RAYTRACING_POINTLIGHT_H
