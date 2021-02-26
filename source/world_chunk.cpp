#include "world_chunk.h"

float tile_size = 64;

int getSign(int number) {
    if (number > 0)
        return 1;

    if (number < 0)
        return -1;

    return 1;
}

void WorldChunk::setLast4Txt(int offsetX, int offsetY, int side) {
    vertices[side][0][vertices[side][0].size()-1].texCoords = sf::Vector2f(0 + offsetX*16, 0 + offsetY*16);
    vertices[side][0][vertices[side][0].size()-2].texCoords = sf::Vector2f(16 + offsetX*16, 0 + offsetY*16);
    vertices[side][0][vertices[side][0].size()-3].texCoords = sf::Vector2f(16 + offsetX*16, 16 + offsetY*16);
    vertices[side][0][vertices[side][0].size()-4].texCoords = sf::Vector2f(0 + offsetX*16, 16 + offsetY*16);
}

void WorldChunk::setLast4TileCoords(WorldTile& tile, int side) {
    vertices[side][1][vertices[side][1].size()-1].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
    vertices[side][1][vertices[side][1].size()-2].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
    vertices[side][1][vertices[side][1].size()-3].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
    vertices[side][1][vertices[side][1].size()-4].color = sf::Color(tile.pos_x, tile.pos_y, tile.pos_z);
}

void WorldChunk::setLast4ChunkCoords(int side, int tile_side) {
    vertices[side][2][vertices[side][2].size()-1].color = sf::Color(pos_x, pos_z, tile_side);
    vertices[side][2][vertices[side][2].size()-2].color = sf::Color(pos_x, pos_z, tile_side);
    vertices[side][2][vertices[side][2].size()-3].color = sf::Color(pos_x, pos_z, tile_side);
    vertices[side][2][vertices[side][2].size()-4].color = sf::Color(pos_x, pos_z, tile_side);
}

void WorldChunk::setLast4Shade(int side, int amount) {
    vertices[side][0][vertices[side][0].size()-1].color = sf::Color(amount, amount, amount);
    vertices[side][0][vertices[side][0].size()-2].color = sf::Color(amount, amount, amount);
    vertices[side][0][vertices[side][0].size()-3].color = sf::Color(amount, amount, amount);
    vertices[side][0][vertices[side][0].size()-4].color = sf::Color(amount, amount, amount);
}

void WorldChunk::addTextureQuad(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4, int side, int tile_type, int side_texture) {
    vertices[side][0].push_back(sf::Vertex(p1));
    vertices[side][0].push_back(sf::Vertex(p2));
    vertices[side][0].push_back(sf::Vertex(p3));
    vertices[side][0].push_back(sf::Vertex(p4));

    if (side_texture != -1 && tile_type == 0) {
        setLast4Txt(side_texture, 0, side);
    }else{
        setLast4Txt(tile_type, 0, side);
    }
}

void WorldChunk::addTileDataQuad(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4, int side, WorldTile &tile) {
    vertices[side][1].push_back(sf::Vertex(p1));
    vertices[side][1].push_back(sf::Vertex(p2));
    vertices[side][1].push_back(sf::Vertex(p3));
    vertices[side][1].push_back(sf::Vertex(p4));

    setLast4TileCoords(tile, side);
}

void WorldChunk::addChunkDataQuad(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4, int side) {
    vertices[side][2].push_back(sf::Vertex(p1));
    vertices[side][2].push_back(sf::Vertex(p2));
    vertices[side][2].push_back(sf::Vertex(p3));
    vertices[side][2].push_back(sf::Vertex(p4));

    setLast4ChunkCoords(side, 3);
}

void WorldChunk::rotateMatrix(int x, int y, int rotate_count, int& new_x, int& new_y, int matrix_size) {
    int tmp_x = x;
    int tmp_y = y;

    for (int i = 0; i < rotate_count; i++) {
        int old_x = tmp_x;
        tmp_x = matrix_size - 1 - tmp_y;
        tmp_y = old_x;
    }

    new_x = tmp_x;
    new_y = tmp_y;
}
void WorldChunk::addTileVertices(int side, int offset_x, int offset_z, WorldChunk *next_x, WorldChunk *next_z) {
    for (int y = 0; y < top; y++) {
        for (int x = 0; x < 16; x++) {
            for (int z = 0; z < 16; z++) {

                //std::cout << x + z*16 << ' ' << tile_rotations[side][x + z*16] + y*256 << '\n';

                WorldTile& current_tile = tiles[tile_rotations[side][x + z*16] + y*256];

                if (current_tile.type != -1) {
                    float new_pos_x = (x - z) * tile_size / 2.0f + (16 * tile_size / 2.0f) + offset_x;
                    float new_pos_y = (x + z) * tile_size / 4.0f - current_tile.pos_y * tile_size / 2.0f + (16 * tile_size / 2.0f) + offset_z;

                    sf::Vector2f topMid = sf::Vector2f(new_pos_x + tile_size/2.0f, new_pos_y);
                    sf::Vector2f topRight = sf::Vector2f(new_pos_x + tile_size, new_pos_y + tile_size/4.0f);
                    sf::Vector2f mid = sf::Vector2f(new_pos_x + tile_size/2.0f, new_pos_y  + tile_size/2.0f);
                    sf::Vector2f topLeft = sf::Vector2f(new_pos_x, new_pos_y  + tile_size/4.0f);
                    sf::Vector2f bottomMid = sf::Vector2f(new_pos_x + tile_size/2.0f, new_pos_y  + tile_size);
                    sf::Vector2f bottomLeft = sf::Vector2f(new_pos_x, new_pos_y + 3.0f*(tile_size/4.0f));
                    sf::Vector2f bottomRight = sf::Vector2f(new_pos_x + tile_size, new_pos_y + 3.0f*(tile_size/4.0f));

                    if (tiles[tile_rotations[side][x + z*16] + (y+1)*256].type == -1 || tiles[tile_rotations[side][x + z*16] + (y+1)*256].transparent) {
                        addTextureQuad(topMid, topRight, mid, topLeft, side, current_tile.type, -1);
                        addTileDataQuad(topMid, topRight, mid, topLeft, side, current_tile);
                        addChunkDataQuad(topMid, topRight, mid, topLeft, side);
                    }

                    bool place_z = false;

                    if (z < 15) {
                        if (tiles[tile_rotations[side][x + (z + 1)*16] + y*256].type == -1) {
                            place_z = true;
                        }
                    }else{
                        place_z = true;

                        if (next_z != nullptr) {
                            if (next_z->tiles[tile_rotations[side][x] + y*256].type != -1) {
                                place_z = false;
                            }
                        }
                    }

                    if (place_z) {
                        addTextureQuad(bottomMid, bottomLeft, topLeft, mid, side, current_tile.type, 4);
                        setLast4Shade(side, 200);
                        addTileDataQuad(bottomMid, bottomLeft, topLeft, mid, side, current_tile);
                        addChunkDataQuad(bottomMid, bottomLeft, topLeft, mid, side);
                    }

                    bool place_x = false;

                    if (x < 15) {
                        if (tiles[tile_rotations[side][x + 1 + z*16] + y*256].type == -1) {
                            place_x = true;
                        }
                    }else{
                        place_x = true;

                        if (next_x != nullptr) {
                            if (next_x->tiles[tile_rotations[side][z*16] + y*256].type != -1) {
                                place_x = false;
                            }
                        }
                    }

                    if (place_x) {
                        addTextureQuad(bottomMid, bottomRight, topRight, mid, side, current_tile.type, 4);
                        setLast4Shade(side, 150);
                        addTileDataQuad(bottomMid, bottomRight, topRight, mid, side, current_tile);
                        addChunkDataQuad(bottomMid, bottomRight, topRight, mid, side);
                    }
                }
            }
        }
    }
}

void WorldChunk::generateVertexMesh(int x, int z, int chunk_width, std::vector<WorldChunk> &chunks) {
    vertices.clear();
    vertices.resize(4);
    vertices[0].resize(3);
    vertices[1].resize(3);
    vertices[2].resize(3);
    vertices[3].resize(3);

    for (int side = north; side <= west; side++) {
        WorldChunk* next_x = nullptr;
        WorldChunk* next_z = nullptr;

        //todo work out this thing
        /*int rotated_x_x = 0;
        int rotated_y_x = 0;

        rotateMatrix(x + 1, z, side, rotated_x_x, rotated_y_x, chunk_width);

        int rotated_x_z = 0;
        int rotated_y_z = 0;

        rotateMatrix(x, z + 1, side, rotated_x_z, rotated_y_z, chunk_width);

        //std::cout << rotated_x_x << ' ' << rotated_y_x << ' ' << rotated_x_z << ' ' << rotated_y_z << '\n';

        int next_x_index = rotated_x_x + rotated_y_x*chunk_width;
        int next_y_index = rotated_x_z + rotated_y_z*chunk_width;

        if (next_x_index < chunk_width && next_x_index > 0)
            next_x = &chunks[rotated_x_x + rotated_y_x*chunk_width];

        if (next_y_index < chunk_width && next_y_index > 0)
            next_z = &chunks[rotated_x_z + rotated_y_z*chunk_width];*/

        addTileVertices(side, 0, 0, next_x, next_z);
    }
}