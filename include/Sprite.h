#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include <string>

class Sprite {
public:
    Sprite();
    explicit Sprite(const std::string& file);

    ~Sprite();

    void Open(const std::string& file);

    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);

    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen() const;

private:
    SDL_Texture* m_texture; //textura carregadfa
    int m_width;
    int m_height;
    SDL_Rect m_clipRect; //retangulo do clipping
};

#endif