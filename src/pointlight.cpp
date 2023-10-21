#include "../include/pointlight.h"

qbRT::PointLight::PointLight(){
    m_color = qbVector<double> (std::vector<double>{1.0, 1.0, 1.0});
    m_intensity = 1.0;
}

qbRT::PointLight::~PointLight() {

}

bool qbRT::PointLight::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                           const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                           const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                           qbVector<double> &color, double &intensity) {
    // Construct a vector pointing from the intersection point to the light
    qbVector<double> lightDir = (m_location - intPoint).Normalized();

    // compute a starting point;
    qbVector<double> startPoint = intPoint;

    // compute the angle between the local normal and the light ray.
    // Note that we assume the localNormal is a unit vector
    double angle = acos(qbVector<double>::dot(localNormal, lightDir));

    //if the normal is pointing away from the normal there is no illumination
    if(angle > 1.5708){
        color = m_color;
        intensity = 0.0;
        return false;
    }else{
        color = m_color;
        intensity = m_intensity * (1.0 - (angle / 1.5708));
        return true;
    }

}
