#ifndef TILEMAP_H
#define TILEMAP_H

#include "Component.h"
#include "TileSet.h"
#include <vector>
#include <string>
#include <memory>

class TileMap : public Component {
public:
    TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);
    ~TileMap();

    void Load(const std::string& file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);

    void RenderLayer(int layer);
    void Render() override;
    void Update(float dt) override;
    int GetWidth() const;
    int GetHeight() const;
    int GetDepth() const;

private:
    std::vector<int> m_tileMatrix;
    std::unique_ptr<TileSet> m_tileSet;
    int m_mapWidth;
    int m_mapHeight;
    int m_mapDepth;
};

#endif