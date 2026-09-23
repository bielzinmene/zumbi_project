#include "TileMap.h"
#include "GameObject.h"
#include <fstream>
#include <iostream>

TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet)
    : Component(associated), m_tileSet(tileSet), m_mapWidth(0), m_mapHeight(0), m_mapDepth(0) {
    Load(file);
}

TileMap::~TileMap() = default;

void TileMap::Load(const std::string& file) {
    std::ifstream mapFile(file);
    char comma;

    if (mapFile.is_open()) {
        // le as dimensoes do mapa ignorando as virgulas
        mapFile >> m_mapWidth >> comma >> m_mapHeight >> comma >> m_mapDepth >> comma;

        if (mapFile.fail()) {
            std::cerr << "[TileMap] Erro ao ler as dimensoes do mapa: " << file << std::endl;
            return;
        }

        m_tileMatrix.resize(m_mapWidth * m_mapHeight * m_mapDepth);
        m_parallax.assign(m_mapDepth, 1.0f);

        // preenche a matriz diretamente na ordem z, y, x
        for (int z = 0; z < m_mapDepth; ++z) {
            for (int y = 0; y < m_mapHeight; ++y) {
                for (int x = 0; x < m_mapWidth; ++x) {
                    int index;
                    char c;
                    mapFile >> index >> c;

                    if (mapFile.fail()) {
                        std::cerr << "[TileMap] Erro ao ler indice em (" << x << ", " << y << ", " << z << ")" << std::endl;
                        return;
                    }

                    m_tileMatrix[(z * m_mapHeight + y) * m_mapWidth + x] = index;
                }
            }
        }
        mapFile.close();
    } else {
        std::cerr << "[TileMap] Erro ao abrir o arquivo do mapa: " << file << std::endl;
    }
}

void TileMap::SetTileSet(TileSet* tileSet) {
    m_tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    int index = x + (y * m_mapWidth) + (z * m_mapWidth * m_mapHeight);
    return m_tileMatrix[index];
}

void TileMap::Render() {
    for (int i = 0; i < m_mapDepth; ++i) {
        RenderLayer(i);
    }
}

void TileMap::RenderLayer(int layer) {
    if (!m_tileSet || layer < 0 || layer >= m_mapDepth) return;

    int tileW = m_tileSet->GetTileWidth();
    int tileH = m_tileSet->GetTileHeight();

    for (int y = 0; y < m_mapHeight; ++y) {
        for (int x = 0; x < m_mapWidth; ++x) {
            int index = At(x, y, layer);

            // -1 representa tile vazio
            if (index != -1) {
                m_tileSet->RenderTile(
                    (unsigned)index,
                    associated.box.x + (float)(x * tileW),
                    associated.box.y + (float)(y * tileH),
                    m_parallax[layer]
                );
            }
        }
    }
}

void TileMap::Update(float dt) {
    (void)dt;
}

int TileMap::GetWidth() const {
    return m_mapWidth;
}

int TileMap::GetHeight() const {
    return m_mapHeight;
}

int TileMap::GetDepth() const {
    return m_mapDepth;
}

void TileMap::SetParallax(int layer, float factor) {
    if (layer >= 0 && layer < m_mapDepth && factor >= 0.0f) {
        m_parallax[layer] = factor;
    }
}
