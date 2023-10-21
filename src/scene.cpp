#include "../include/scene.h"
#include "../qbLinAlg/qbVector.h"

qbRT::Scene::Scene() {
    // Configure the camera
    m_camera.SetPosition(qbVector<double>(std::vector<double>{0.0, -10.0, 0.0}));
    m_camera.SetLookAt(qbVector<double>(std::vector<double>{0.0, 0.0, 0.0}));
    m_camera.SetUp(qbVector<double>(std::vector<double>{0.0, 0.0, 1.0}));
    m_camera.SetHorizSize(0.25);
    m_camera.SetAspect(16.0 / 9.0);
    m_camera.UpdateCameraGeometry();

    // Construct a test sphere
    m_objetList.push_back(std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere()));

    // construct a test light
    m_lightList.push_back(std::make_shared<qbRT::PointLight>(qbRT::PointLight()));
    m_lightList.at(0)->m_location = qbVector<double>(std::vector<double>{5.0, -10.0, -5.0});
    m_lightList.at(0)->m_color = qbVector<double>(std::vector<double>{255.0, 255.0, 255.0});
}

bool qbRT::Scene::Render(qbImage &outputImage) {
    // Get the dimensions of the output image.
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    // Loop over each pixel in our image!
    qbRT::Ray cameraRay;
    qbVector<double> intPoint {3};
    qbVector<double> localNormal {3};
    qbVector<double> localColor {3};

    double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
    double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
    double minDist = 1e6;
    double maxDist = 0.0;
    for(int x = 0; x < xSize; ++x){
        for(int y = 0; y < ySize; ++y){
            // Normalize x, ,y coordinates
            double normX = (static_cast<double>(x) * xFact) - 1.0;
            double normY = (static_cast<double>(y) * yFact) - 1.0;

            // Generate the ray for the pixel.
            m_camera.GenerateRate(normX, normY, cameraRay);

            // Test for Intersections with all objects in the scene.
            for(auto currentObject : m_objetList){
                bool validInt = currentObject->TestIntersection(cameraRay, intPoint, localNormal, localColor);

                if(validInt){
                    // compute intensity of illumination
                    double intensity;
                    qbVector<double> color{3};
                    bool validIllum = false;
                    for(auto currentLight : m_lightList){
                        validIllum = currentLight->ComputeIllumination(intPoint, localNormal, m_objetList, currentObject, color, intensity);
                    }
                    // Compute the distance between the camera and the point of intersection
                    double dist = (intPoint - cameraRay.m_point1).norm();
                    if(dist > maxDist)
                        maxDist = dist;
                    if(dist < minDist)
                        minDist = dist;
                    //outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
                    if(validIllum){
                        outputImage.SetPixel(x, y, 255.0 * intensity, 0.0, 0.0);
                    }else{
                        outputImage.SetPixel(x, y, 0 * intensity, 0.0, 0.0);
                    }
                }else{
                    outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                }
            }

            // Test if we have a valid intersection
            //bool validInt = m_testSphere.TestIntersection(cameraRay, intPoint, localNormal, localColor);

            // if have valid intersection change color to red.

        }
    }

    return true;
}
