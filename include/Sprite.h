#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

class Sprite {
public:
    Sprite();
    explicit Sprite(const std::string& file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(const std::string& file);
    void SetClip(int x, int y, int w, int h);
    void Render(float x, float y, float parallax = 1.0f);
    bool cameraFollower;

    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen() const;

    // novas funcoes de animacao
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);

private:
    SDL_Texture* m_texture;
    int m_width;
    int m_height;
    SDL_Rect m_clipRect;

    // controle de matriz de frames
    int m_frameCountW;
    int m_frameCountH;
};

#endif