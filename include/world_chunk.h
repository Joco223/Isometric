#ifndef ISOMETRIC_WORLD_CHUNK_H
#define ISOMETRIC_WORLD_CHUNK_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "world_tile.h"

enum directions {
    north,
    east,
    south,
    west
};

struct TileIndices {
    int render_indices;
    int tile_data_indices;
    int chunk_data_indices;
};

class WorldChunk {
private:
    void addTileVertices(int start_x, int end_x, int start_z, int end_z, int offset_x, int offset_y, int side, WorldChunk* next_x, WorldChunk* next_z);
    void setLast4Txt(int offsetX, int offsetY, int side);
    void setLast4TileCoords(WorldTile& tile, int side);
    void setLast4ChunkCoords(int side, int tile_side);
public:
    int pos_x, pos_z, top;
    std::vector<WorldTile> tiles;
    std::vector<std::vector<std::vector<sf::Vertex>>> vertices;

    std::vector<TileIndices> tile_indices;

    sf::Sprite chunk_sprite;


    void generateVertexGrid(WorldChunk* next_x, WorldChunk* next_z);
};

#endif
