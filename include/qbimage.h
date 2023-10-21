#ifndef RAYTRACING_QBIMAGE_H
#define RAYTRACING_QBIMAGE_H
#include <string>
#include <vector>
#include <SDL2/SDL.h>

class qbImage{
public:
    qbImage();
    ~qbImage();

    void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer);
    void SetPixel(const int x, const int y, const double red, const double green, const double blue);

    void Display();
    /*Get Dimensions of the image!*/
    int GetXSize();
    int GetYSize();

private:
    Uint32 ConvertColor(const double red, const double green, const double blue);
    void InitTexture();

private:
    /*Arrays to store the image data!*/
    std::vector<std::vector<double>> m_rChannel;
    std::vector<std::vector<double>> m_gChannel;
    std::vector<std::vector<double>> m_bChannel;
    int m_xSize, m_ySize;
    SDL_Texture *m_pTexture;
    SDL_Renderer *m_pRenderer;

};

#endif //RAYTRACING_QBIMAGE_H
