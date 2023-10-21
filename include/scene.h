#ifndef RAYTRACING_SCENE_H
#define RAYTRACING_SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "./qbimage.h"
#include "./camera.h"
#include "./objsphere.h"
#include <memory>
#include "./pointlight.h"

namespace qbRT{
    class Scene{
    public:
        Scene();
        bool Render(qbImage &outputImage);

    private:
        // private functions

    private:
        // the camera
        qbRT::Camera m_camera;

        /*
         * List of objects in the scene.
         * */
        std::vector<std::shared_ptr<qbRT::ObjectBase>> m_objetList;

        // The list of lights in the scene
        std::vector<std::shared_ptr<qbRT::LightBase>> m_lightList;

    };
};

#endif //RAYTRACING_SCENE_H
