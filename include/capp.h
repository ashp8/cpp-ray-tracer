#ifndef RAYTRACING_CAPP_H
#define RAYTRACING_CAPP_H

#include <SDL2/SDL.h>
#include "./qbimage.h"
#include "./scene.h"
#include "./camera.h"

class CApp{
public:
    CApp();

    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event *event);
    void OnRender();
    void OnExit();
    void OnLoop();

private:
    void PrintVector(const qbVector<double> &inputVector);
private:
    bool isRunning;
    qbImage m_image;
    qbRT::Scene m_scene;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
};


#endif //RAYTRACING_CAPP_H
