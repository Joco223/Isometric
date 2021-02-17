#include "world_chunk.h"

float tile_size = 64;

void WorldChunk::setLast4Txt(int offsetX, int offsetY) {
    vertex_grid[vertex_grid.size()-1].texCoords = sf::Vector2f(0 + offsetX*16, 0 + offsetY*16);
    vertex_grid[vertex_grid.size()-2].texCoords = sf::Vector2f(16 + offsetX*16, 0 + offsetY*16);
    vertex_grid[vertex_grid.size()-3].texCoords = sf::Vector2f(16 + offsetX*16, 16 + offsetY*16);
    vertex_grid[vertex_grid.size()-4].texCoords = sf::Vector2f(0 + offsetX*16, 16 + offsetY*16);
}

void WorldChunk::regenerateVisible() {
    for (auto& tile : tiles) {
        tile.visible = false;
        if (tile.pos_y == 255) {
            tile.top = true;
        }else{
            if (tiles[tile.pos_x + tile.pos_z*16 + (tile.pos_y + 1)*16*16].type == -1) {
                tile.top = true;
            }
        }

        if (tile.top) {
            tile.visible = true;
            continue;
        }

        bool visibleZ = false;

        if (tile.pos_x == 15) {
            visibleZ = true;
        }else{
            if (tiles[(tile.pos_x + 1) + tile.pos_z*16 + tile.pos_y*16*16].type == -1) {
                visibleZ = true;
            }
        }

        if (visibleZ) {
            tile.visible = true;
            continue;
        }

        bool visibleX = false;

        if (tile.pos_z == 15) {
            visibleX = true;
        }else{
            if (tiles[tile.pos_x + (tile.pos_z + 1)*16 + tile.pos_y*16*16].type == -1) {
                visibleX = true;
            }
        }

        if (visibleX) {
            tile.visible = true;
            continue;
        }
    }
}

void WorldChunk::generateVertexGrid() {
    vertex_grid.clear();
    vertex_tile_grid.clear();
    vertex_chunk_grid.clear();

    int offset_x = (pos_x - pos_z) * 16 * tile_size / 2.0f;
    int offset_y = (pos_x + pos_z) * 16 * tile_size / 4.0f;

    for (auto& tile : tiles) {
        if (tile.visible && tile.type != -1) {
            float new_pos_x = (tile.pos_x - tile.pos_z) * tile_size / 2.0f + (16 * tile_size / 2.0f) + offset_x;
            float new_pos_y = (tile.pos_x + tile.pos_z) * tile_size / 4.0f - tile.pos_y * tile_size / 2.0f + (16 * tile_size / 2.0f) + offset_y;

            sf::Vector2f topMid = sf::Vector2f(new_pos_x + tile_size/2.0f, new_pos_y);
            sf::Vector2f topRight = sf::Vector2f(new_pos_x + tile_size, new_pos_y + tile_size/4.0f);
            sf::Vector2f mid = sf::Vector2f(new_pos_x + tile_size/2.0f, new_pos_y  + tile_size/2.0f);
            sf::Vector2f topLeft = sf::Vector2f(new_pos_x, new_pos_y  + tile_size/4.0f);
            sf::Vector2f bottomMid = sf::Vector2f(new_pos_x + tile_size/2.0f, new_pos_y  + tile_size);
            sf::Vector2f bottomLeft = sf::Vector2f(new_pos_x, new_pos_y + 3.0f*(tile_size/4.0f));
            sf::Vector2f bottomRight = sf::Vector2f(new_pos_x + tile_size, new_pos_y + 3.0f*(tile_size/4.0f));

            if (tile.top) {
                vertex_grid.push_back(sf::Vertex(topMid));
                vertex_grid.push_back(sf::Vertex(topRight));
                vertex_grid.push_back(sf::Vertex(mid));
                vertex_grid.push_back(sf::Vertex(topLeft));


                //vertex_grid[vertex_grid.size()-1].color = sf::Color(255, 0, 0);
                //vertex_grid[vertex_grid.size()-2].color = sf::Color(255, 0, 0);
                //vertex_grid[vertex_grid.size()-3].color = sf::Color(255, 0, 0);
                //vertex_grid[vertex_grid.size()-4].color = sf::Color(255, 0, 0);

                setLast4Txt(tile.type, 0);

                vertex_tile_grid.push_back(sf::Vertex(topMid));
                vertex_tile_grid.push_back(sf::Vertex(topRight));
                vertex_tile_grid.push_back(sf::Vertex(mid));
                vertex_tile_grid.push_back(sf::Vertex(topLeft));

                vertex_tile_grid[vertex_tile_grid.size()-1].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
                vertex_tile_grid[vertex_tile_grid.size()-2].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
                vertex_tile_grid[vertex_tile_grid.size()-3].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
                vertex_tile_grid[vertex_tile_grid.size()-4].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);

                vertex_chunk_grid.push_back(sf::Vertex(topMid));
                vertex_chunk_grid.push_back(sf::Vertex(topRight));
                vertex_chunk_grid.push_back(sf::Vertex(mid));
                vertex_chunk_grid.push_back(sf::Vertex(topLeft));

                vertex_chunk_grid[vertex_chunk_grid.size()-1].color = sf::Color(pos_x, pos_z, 0);
                vertex_chunk_grid[vertex_chunk_grid.size()-2].color = sf::Color(pos_x, pos_z, 0);
                vertex_chunk_grid[vertex_chunk_grid.size()-3].color = sf::Color(pos_x, pos_z, 0);
                vertex_chunk_grid[vertex_chunk_grid.size()-4].color = sf::Color(pos_x, pos_z, 0);
            }

            bool placeX = false;

            if (tile.pos_z < 15) {
                if (tiles[tile.pos_x + (tile.pos_z + 1)*16 + tile.pos_y*16*16].type == -1) {
                    placeX = true;
                }
            }

            if (tile.pos_z == 15 || placeX) {
                vertex_grid.push_back(sf::Vertex(bottomMid));
                vertex_grid.push_back(sf::Vertex(bottomLeft));
                vertex_grid.push_back(sf::Vertex(topLeft));
                vertex_grid.push_back(sf::Vertex(mid));

                vertex_grid[vertex_grid.size()-1].color = sf::Color(230, 230, 230);
                vertex_grid[vertex_grid.size()-2.0f].color = sf::Color(230, 230, 230);
                vertex_grid[vertex_grid.size()-3].color = sf::Color(230, 230, 230);
                vertex_grid[vertex_grid.size()-4.0f].color = sf::Color(230, 230, 230);

                if (tile.type == 0) {
                    setLast4Txt(3, 0);
                }else{
                    setLast4Txt(tile.type, 0);
                }

                vertex_tile_grid.push_back(sf::Vertex(bottomMid));
                vertex_tile_grid.push_back(sf::Vertex(bottomLeft));
                vertex_tile_grid.push_back(sf::Vertex(topLeft));
                vertex_tile_grid.push_back(sf::Vertex(mid));

                vertex_tile_grid[vertex_tile_grid.size()-1].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
                vertex_tile_grid[vertex_tile_grid.size()-2].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
                vertex_tile_grid[vertex_tile_grid.size()-3].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
                vertex_tile_grid[vertex_tile_grid.size()-4].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);

                vertex_chunk_grid.push_back(sf::Vertex(bottomMid));
                vertex_chunk_grid.push_back(sf::Vertex(bottomLeft));
                vertex_chunk_grid.push_back(sf::Vertex(topLeft));
                vertex_chunk_grid.push_back(sf::Vertex(mid));

                vertex_chunk_grid[vertex_chunk_grid.size()-1].color = sf::Color(pos_x, pos_z, 0);
                vertex_chunk_grid[vertex_chunk_grid.size()-2].color = sf::Color(pos_x, pos_z, 0);
                vertex_chunk_grid[vertex_chunk_grid.size()-3].color = sf::Color(pos_x, pos_z, 0);
                vertex_chunk_grid[vertex_chunk_grid.size()-4].color = sf::Color(pos_x, pos_z, 0);
            }

            bool placeZ = false;

            if (tile.pos_x < 15) {
                if (tiles[(tile.pos_x + 1) + tile.pos_z*16 + tile.pos_y*16*16].type == -1) {
                    placeZ = true;
                }
            }

            if (tile.pos_x == 15 || placeZ) {
                vertex_grid.push_back(sf::Vertex(bottomRight));
                vertex_grid.push_back(sf::Vertex(bottomMid));
                vertex_grid.push_back(sf::Vertex(mid));
                vertex_grid.push_back(sf::Vertex(topRight));


                vertex_grid[vertex_grid.size()-1].color = sf::Color(150, 150, 150);
                vertex_grid[vertex_grid.size()-2.0f].color = sf::Color(150, 150, 150);
                vertex_grid[vertex_grid.size()-3].color = sf::Color(150, 150, 150);
                vertex_grid[vertex_grid.size()-4.0f].color = sf::Color(150, 150, 150);

                if (tile.type == 0) {
                    setLast4Txt(3, 0);
                }else{
                    setLast4Txt(tile.type, 0);
                }

                vertex_tile_grid.push_back(sf::Vertex(bottomRight));
                vertex_tile_grid.push_back(sf::Vertex(bottomMid));
                vertex_tile_grid.push_back(sf::Vertex(mid));
                vertex_tile_grid.push_back(sf::Vertex(topRight));

                vertex_tile_grid[vertex_tile_grid.size()-1].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
                vertex_tile_grid[vertex_tile_grid.size()-2].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
                vertex_tile_grid[vertex_tile_grid.size()-3].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
                vertex_tile_grid[vertex_tile_grid.size()-4].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);

                vertex_chunk_grid.push_back(sf::Vertex(bottomRight));
                vertex_chunk_grid.push_back(sf::Vertex(bottomMid));
                vertex_chunk_grid.push_back(sf::Vertex(mid));
                vertex_chunk_grid.push_back(sf::Vertex(topRight));

                vertex_chunk_grid[vertex_chunk_grid.size()-1].color = sf::Color(pos_x, pos_z, 0);
                vertex_chunk_grid[vertex_chunk_grid.size()-2].color = sf::Color(pos_x, pos_z, 0);
                vertex_chunk_grid[vertex_chunk_grid.size()-3].color = sf::Color(pos_x, pos_z, 0);
                vertex_chunk_grid[vertex_chunk_grid.size()-4].color = sf::Color(pos_x, pos_z, 0);
            }

        }
    }
}