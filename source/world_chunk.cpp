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

void WorldChunk::addTileVertices(int start_x, int end_x, int start_z, int end_z, int offset_x, int offset_z, int side, WorldChunk* next_x, WorldChunk* next_z) {
    for (int y = 0; y < top; y++) {
        for (int x_counter = start_x; x_counter < end_x; x_counter++) {
            for (int z_counter = start_z; z_counter < end_z; z_counter++) {
                int z = abs(z_counter);
                int x = abs(x_counter);
                if (x == 16)
                    x = 15;

                if (z == 16)
                    z = 15;
                WorldTile& tile = tiles[x + z*16 + y*256];

                if (side == north) {
                    TileIndices ti;
                    ti.render_indices = vertices[side][0].size();
                    ti.tile_data_indices = vertices[side][1].size();
                    ti.chunk_data_indices = vertices[side][2].size();
                    tile_indices.push_back(ti);
                }

                if (tile.type != -1) {
                    float converted_tile_x = tile.pos_x;
                    float converted_tile_z = tile.pos_z;

                    switch (side) {
                        case east:
                            converted_tile_z = -tile.pos_z;
                            break;
                        case south:
                            converted_tile_z = -tile.pos_z;
                            converted_tile_x = -tile.pos_x;
                            break;
                        case west:
                            converted_tile_x = -tile.pos_x;
                            break;
                        default:
                            break;
                    }

                    float new_pos_x = (converted_tile_x - converted_tile_z) * tile_size / 2.0f + (16 * tile_size / 2.0f) + offset_x;
                    float new_pos_y = (converted_tile_x + converted_tile_z) * tile_size / 4.0f - tile.pos_y * tile_size / 2.0f + (16 * tile_size / 2.0f) + offset_z;

                    sf::Vector2f topMid = sf::Vector2f(new_pos_x + tile_size/2.0f, new_pos_y);
                    sf::Vector2f topRight = sf::Vector2f(new_pos_x + tile_size, new_pos_y + tile_size/4.0f);
                    sf::Vector2f mid = sf::Vector2f(new_pos_x + tile_size/2.0f, new_pos_y  + tile_size/2.0f);
                    sf::Vector2f topLeft = sf::Vector2f(new_pos_x, new_pos_y  + tile_size/4.0f);
                    sf::Vector2f bottomMid = sf::Vector2f(new_pos_x + tile_size/2.0f, new_pos_y  + tile_size);
                    sf::Vector2f bottomLeft = sf::Vector2f(new_pos_x, new_pos_y + 3.0f*(tile_size/4.0f));
                    sf::Vector2f bottomRight = sf::Vector2f(new_pos_x + tile_size, new_pos_y + 3.0f*(tile_size/4.0f));

                    if (tiles[x + z*16 + (y+1)*256].type == -1) {
                        vertices[side][0].push_back(sf::Vertex(topMid));
                        vertices[side][0].push_back(sf::Vertex(topRight));
                        vertices[side][0].push_back(sf::Vertex(mid));
                        vertices[side][0].push_back(sf::Vertex(topLeft));

                        setLast4Txt(tile.type, 0, side);

                        vertices[side][1].push_back(sf::Vertex(topMid));
                        vertices[side][1].push_back(sf::Vertex(topRight));
                        vertices[side][1].push_back(sf::Vertex(mid));
                        vertices[side][1].push_back(sf::Vertex(topLeft));

                        setLast4TileCoords(tile, side);

                        vertices[side][2].push_back(sf::Vertex(topMid));
                        vertices[side][2].push_back(sf::Vertex(topRight));
                        vertices[side][2].push_back(sf::Vertex(mid));
                        vertices[side][2].push_back(sf::Vertex(topLeft));

                        setLast4ChunkCoords(side, 3);
                    }

                    bool placeX = false;

                    if ((abs(start_z) == 0 && tile.pos_z < 15) || (abs(start_z) == 16 && tile.pos_z > 0)) {
                        if (tiles[tile.pos_x + (tile.pos_z + 1*getSign(start_z))*16 + tile.pos_y*256].type == -1) {
                            placeX = true;
                        }

                        /*if (next_z != nullptr) {
                            if (next_z->tiles[tile.pos_x + tile.pos_y*256].type != -1) {
                                placeX = false;
                            }
                        }*/
                    }

                    if (start_z == 0) {
                        if (tile.pos_z == 15)
                            placeX = true;
                    }

                    if (abs(start_z) == 16) {
                        if (tile.pos_z == 0)
                            placeX = true;
                    }

                    if (placeX) {
                        vertices[side][0].push_back(sf::Vertex(bottomMid));
                        vertices[side][0].push_back(sf::Vertex(bottomLeft));
                        vertices[side][0].push_back(sf::Vertex(topLeft));
                        vertices[side][0].push_back(sf::Vertex(mid));

                        if (tile.type == 0) {
                            setLast4Txt(3, 0, side);
                        }else{
                            setLast4Txt(tile.type, 0, side);
                        }

                        vertices[side][1].push_back(sf::Vertex(bottomMid));
                        vertices[side][1].push_back(sf::Vertex(bottomLeft));
                        vertices[side][1].push_back(sf::Vertex(topLeft));
                        vertices[side][1].push_back(sf::Vertex(mid));

                        setLast4TileCoords(tile, side);

                        vertices[side][2].push_back(sf::Vertex(bottomMid));
                        vertices[side][2].push_back(sf::Vertex(bottomLeft));
                        vertices[side][2].push_back(sf::Vertex(topLeft));
                        vertices[side][2].push_back(sf::Vertex(mid));

                        setLast4ChunkCoords(side, 1);
                    }

                    bool placeZ = false;

                    if ((abs(start_x) == 0 && tile.pos_x < 15) || (abs(start_x) == 16 && tile.pos_x > 0)) {
                        if (tiles[(tile.pos_x + 1*getSign(start_x)) + tile.pos_z*16 + tile.pos_y*16*16].type == -1) {
                            placeZ = true;
                        }

                        /*if (next_x != nullptr) {
                            if (next_x->tiles[tile.pos_z*16 + tile.pos_y*16*16].type != -1) {
                                placeZ = false;
                            }
                        }*/
                    }

                    if (start_x == 0) {
                        if (tile.pos_x == 15)
                            placeZ = true;
                    }

                    if (abs(start_x) == 16) {
                        if (tile.pos_x == 0)
                            placeZ = true;
                    }

                    if (placeZ) {
                        vertices[side][0].push_back(sf::Vertex(bottomRight));
                        vertices[side][0].push_back(sf::Vertex(bottomMid));
                        vertices[side][0].push_back(sf::Vertex(mid));
                        vertices[side][0].push_back(sf::Vertex(topRight));

                        if (tile.type == 0) {
                            setLast4Txt(3, 0, side);
                        }else{
                            setLast4Txt(tile.type, 0, side);
                        }

                        vertices[side][1].push_back(sf::Vertex(bottomRight));
                        vertices[side][1].push_back(sf::Vertex(bottomMid));
                        vertices[side][1].push_back(sf::Vertex(mid));
                        vertices[side][1].push_back(sf::Vertex(topRight));

                        setLast4TileCoords(tile, side);

                        vertices[side][2].push_back(sf::Vertex(bottomRight));
                        vertices[side][2].push_back(sf::Vertex(bottomMid));
                        vertices[side][2].push_back(sf::Vertex(mid));
                        vertices[side][2].push_back(sf::Vertex(topRight));

                        setLast4ChunkCoords(side, 2);
                    }
                }
            }
        }
    }
}

void WorldChunk::generateVertexGrid(WorldChunk* next_x, WorldChunk* next_z) {
    vertices.clear();
    vertices.resize(4);
    vertices[0].resize(3);
    vertices[1].resize(3);
    vertices[2].resize(3);
    vertices[3].resize(3);
    for (int side = north; side <= west; side++) {
        int offset_x = 0;
        int offset_z = 0;

        int converted_chunk_x = offset_x;
        int converted_chunk_z = offset_z;

        switch (side) {
            case east:
                converted_chunk_z = -offset_z;
                break;
            case south:
                converted_chunk_z = -offset_z;
                converted_chunk_x = -offset_x;
                break;
            case west:
                converted_chunk_x = -offset_x;
                break;
            default:
                break;
        }

        switch (side) {
            case north:
                addTileVertices(0, 16, 0, 16, converted_chunk_x, converted_chunk_z, side, next_x, next_z);
                break;
            case east:
                addTileVertices(0, 16, -16, 1, converted_chunk_x, converted_chunk_z, side, next_x, next_z);
                break;
            case south:
                addTileVertices(-16, 1, -16, 1, converted_chunk_x, converted_chunk_z, side, next_x, next_z);
                break;
            case west:
                addTileVertices(-16, 1, 0, 16, converted_chunk_x, converted_chunk_z, west, next_x, next_z);
                break;
        }
    }
}