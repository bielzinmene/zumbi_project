#ifndef TEXT_H
#define TEXT_H

#include "Component.h"
#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include <memory>
#include <string>

class Text : public Component {
public:
    enum class TextStyle { SOLID, SHADED, BLENDED };

    Text(GameObject& associated, const std::string& fontFile, int fontSize,
         TextStyle style, const std::string& text, SDL_Color color);
    ~Text() override;

    void Update(float dt) override;
    void Render() override;
    void SetText(const std::string& text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(const std::string& file);
    void SetFontSize(int size);

private:
    void RemakeTexture();

    std::shared_ptr<TTF_Font> m_font;
    SDL_Texture* m_texture;
    std::string m_text;
    TextStyle m_style;
    std::string m_fontFile;
    int m_fontSize;
    SDL_Color m_color;
};

#endif
