#include "TileSet.h"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, const std::string& file)
    : m_tileSet(file), m_tileWidth(tileWidth), m_tileHeight(tileHeight), m_tileCount(0) {

    if (!m_tileSet.IsOpen()) {
        std::cerr << "[TileSet] Erro: nao foi possivel carregar o tileset: " << file << std::endl;
        return;
    }

    int texWidth = m_tileSet.GetWidth();
    int texHeight = m_tileSet.GetHeight();

    int columns = texWidth / m_tileWidth;
    int rows = texHeight / m_tileHeight;
    m_tileCount = columns * rows;

    // define a grade de frames do sprite para corresponder exatamente aos tiles
    m_tileSet.SetFrameCount(columns, rows);
}

void TileSet::RenderTile(unsigned index, float x, float y, float parallax) {
    if (index < (unsigned)m_tileCount) {
        m_tileSet.SetFrame((int)index);
        m_tileSet.Render(x, y, parallax);
    } else {
        std::cerr << "[TileSet] Erro: indice invalido (" << index << ")" << std::endl;
    }
}

int TileSet::GetTileWidth() const {
    return m_tileWidth;
}

int TileSet::GetTileHeight() const {
    return m_tileHeight;
}