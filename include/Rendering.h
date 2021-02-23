#ifndef ISOMETRIC_RENDERING_H
#define ISOMETRIC_RENDERING_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#include "world_chunk.h"

namespace Rendering {
    struct gameSprite {
        std::string name;
        std::string path;
        sf::Texture sprite;
    };

    void init(int chunk_count);
    int loadSprite(const std::string& file_path, const std::string& name);
    void renderVertexChunks(sf::RenderWindow& window, const std::vector<WorldChunk>& chunks, sf::View& camera, int side, int chunk_width);
    void getClickedTile(const int mouse_x, const int mouse_y, int& chunk_index_x, int& chunk_index_z, int& tile_index_x, int& tile_index_y, int& tile_index_z, int& tile_side);
    void debugRender(sf::RenderWindow& window);
    void deinit();
}

#endif
