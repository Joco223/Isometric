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
    void renderChunk(WorldChunk& chunk, int world_width);
    void renderWorldTiles(sf::RenderWindow& window, const std::vector<WorldChunk>& chunks);
    void renderWorldTilesSmart(sf::RenderWindow& window, const std::vector<WorldChunk>& chunks, const sf::View& camera);
    void renderVertexChunks(sf::RenderWindow& window, const std::vector<WorldChunk>& chunks, const sf::View& camera);
    void getClickedTile(const int mouse_x, const int mouse_y, int& chunk_index_x, int& chunk_index_z, int& tile_index_x, int& tile_index_y, int& tile_index_z);
    void debugRender(sf::RenderWindow& window);
    void renderWorldChunks(sf::RenderWindow& window, std::vector<WorldChunk>& chunks);
    void deinit();
}

#endif
