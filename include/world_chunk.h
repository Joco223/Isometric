#ifndef ISOMETRIC_WORLD_CHUNK_H
#define ISOMETRIC_WORLD_CHUNK_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "world_tile.h"

class WorldChunk {
public:
    int pos_x, pos_z, top;
    std::vector<WorldTile> tiles;
    std::vector<sf::Vertex> vertex_grid;
    std::vector<sf::Vertex> vertex_tile_grid;
    std::vector<sf::Vertex> vertex_chunk_grid;
    sf::Sprite chunk_sprite;

    void regenerateVisible();
    void generateVertexGrid();
    void setLast4Txt(int offsetX, int offsetY);
};

#endif
