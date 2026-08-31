#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "SDL_include.h"

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
    SDL_Texture* m_texture;
    int m_width;
    int m_height;
    SDL_Rect m_clipRect;
};

#endif // sprite_h