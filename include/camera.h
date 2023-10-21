#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "../qbLinAlg/qbVector.h"
#include "./ray.h"

namespace qbRT{
    class Camera{
    public:
        Camera();

        void SetPosition(const qbVector<double> &newPosition);
        void SetLookAt(const qbVector<double> &newLookAt);
        void SetUp(const qbVector<double> &upVector);
        void SetLength(double newLength);
        void SetHorizSize(double newSize);
        void SetAspect(double newAspect);

        qbVector<double> GetPosition();
        qbVector<double> GetLookAt();
        qbVector<double> GetUp();
        qbVector<double> GetU();
        qbVector<double> GetV();
        qbVector<double> GetScreenCentre();
        double GetLength();
        double GetHorizSize();
        double GetAspect();

        // Function to generate Ray

        bool GenerateRate(float proScreenX, float proScreenY, qbRT::Ray &cameraRay);

        // Update The camera Geometry
        void UpdateCameraGeometry();

    private:
        qbVector<double> m_cameraPosition{3};
        qbVector<double> m_cameraLookAt {3};
        qbVector<double> m_cameraUp {3};
        double m_cameraLength;
        double m_cameraHorizSize;
        double m_cameraAspectRatio;

        qbVector<double> m_alignmentVector {3};
        qbVector<double> m_projectionScreenU {3};
        qbVector<double> m_projectionScreenV {3};
        qbVector<double> m_projectionCentre {3};
    };
}

#endif //RAYTRACING_CAMERA_H
