#include "../include/camera.h"
#include "../include/ray.h"
#include "../qbLinAlg/qbVector.h"
#include <math.h>

qbRT::Camera::Camera() {
    m_cameraPosition = qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}};
    m_cameraLookAt = qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}};
    m_cameraUp = qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}};
    m_cameraLength = 1.0;
    m_cameraHorizSize = 1.0;
    m_cameraAspectRatio = 1.0;
}

void qbRT::Camera::SetPosition(const qbVector<double> &newPosition) {
    m_cameraPosition = newPosition;
}

void qbRT::Camera::SetLookAt(const qbVector<double> &newLookAt) {
    m_cameraLookAt = newLookAt;
}

void qbRT::Camera::SetUp(const qbVector<double> &upVector) {
    m_cameraUp = upVector;
}

void qbRT::Camera::SetLength(double newLength) {
    m_cameraLength = newLength;
}

void qbRT::Camera::SetHorizSize(double newSize) {
    m_cameraHorizSize = newSize;
}

void qbRT::Camera::SetAspect(double newAspect) {
    m_cameraAspectRatio = newAspect;
}

qbVector<double> qbRT::Camera::GetPosition() {
    return m_cameraPosition;
}

qbVector<double> qbRT::Camera::GetLookAt() {
    return m_cameraLookAt;
}

qbVector<double> qbRT::Camera::GetUp() {
    return m_cameraUp;
}

double qbRT::Camera::GetLength() {
    return m_cameraLength;
}

double qbRT::Camera::GetHorizSize() {
    return m_cameraHorizSize;
}

double qbRT::Camera::GetAspect() {
    return m_cameraAspectRatio;
}
qbVector<double> qbRT::Camera::GetU()  {
    return m_projectionScreenU;
}
qbVector<double> qbRT::Camera::GetV(){
    return m_projectionScreenV;
}

qbVector<double> qbRT::Camera::GetScreenCentre() {
    return m_projectionCentre;
}

// Function to compute camera geometry

void qbRT::Camera::UpdateCameraGeometry() {
    // Fist Compute the vector from the came position to the LookAt position
    m_alignmentVector = m_cameraLookAt - m_cameraPosition;
    m_alignmentVector.Normalize();

    // Second compute the u and v vector!
    m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
    m_projectionScreenU.Normalize();

    m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
    m_projectionScreenV.Normalize();

    // Thirdly compute the position of the point of the screen.
    m_projectionCentre = m_cameraPosition + (m_cameraLength * m_alignmentVector);

    // Modify the U and V vectors to match the size of the aspect ratio
    m_projectionScreenU = m_projectionScreenU * m_cameraHorizSize;
    m_projectionScreenV = m_projectionScreenV * (m_cameraHorizSize / m_cameraAspectRatio);
}

bool qbRT::Camera::GenerateRate(float proScreenX, float proScreenY, qbRT::Ray &cameraRay) {
    // Compute the location of the screen point coordinates
    qbVector<double> screenWorldPart1 = m_projectionCentre + (m_projectionScreenU * proScreenX);
    qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);


    cameraRay.m_point1 = m_cameraPosition;
    cameraRay.m_point2 = screenWorldCoordinate;
    cameraRay.m_lab = screenWorldCoordinate - m_cameraPosition;

    return true;

    // use this point along with the camera position to compute the ray

}
