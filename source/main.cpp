#include <iostream>

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <stdio.h>

#include "Rendering.h"
#include "world_chunk.h"
#include "SimplexNoise.h"

const int width = 1024;
const int height = 576;
const int chunk_width = 3;
const int fps = 60;
const int chunk_size = 16;

int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height, 32), "Isometric", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(fps);

    sf::View camera(sf::FloatRect(0, 0, width, height));
    int scale = 1;
    int side = north;

    sf::Event event;

    int stone_sprite = Rendering::loadSprite("../assets/sprites/stone.png", "stone");
    int dirt_sprite = Rendering::loadSprite("../assets/sprites/dirt.png", "dirt");
    int grass_sprite = Rendering::loadSprite("../assets/sprites/grass.png", "stone");
    int selected_sprite = Rendering::loadSprite("../assets/sprites/selected.png", "selected");

    std::vector<WorldChunk> chunks;
    Rendering::init(24*24);

    for (int cy = 0; cy < chunk_width; cy++) {
        for (int cx = 0; cx < chunk_width; cx++) {
            WorldChunk new_chunk;
            new_chunk.pos_x = cx;
            new_chunk.pos_z = cy;
            new_chunk.top = 0;
            new_chunk.tiles.resize(16*16*256);
            for (int x = 0; x < 16; x++) {
                for (int z = 0; z < 16; z++) {
                    int top = (int)((SimplexNoise::noise((cx * 16 + x)/200.0f, (cy * 16 + z)/200.0f) + 1) * 10);
                    WorldTile newTile;
                    for (int y = 0; y < 16 + top; y++) {
                        if (y == 15 + top) {
                            newTile = WorldTile(x, y, z, grass_sprite, true, false, true, 0);
                        }else if (y > 12 + top) {
                            newTile = WorldTile(x, y, z, dirt_sprite, false, false, false, 1);
                        }else {
                            newTile = WorldTile(x, y, z, stone_sprite, false, false, false, 2);
                        }

                        newTile.visible = true;

                        if (16 + top > new_chunk.top)
                            new_chunk.top = top + 16;

                        new_chunk.tiles[x + z*16 + y*16*16] = newTile;
                    }
                }
            }
            new_chunk.vertices.resize(4);
            new_chunk.vertices[0].resize(3);
            new_chunk.vertices[1].resize(3);
            new_chunk.vertices[2].resize(3);
            new_chunk.vertices[3].resize(3);
            chunks.push_back(new_chunk);
        }
    }

    for (int cy = 0; cy < chunk_width; cy++) {
        for (int cx = 0; cx < chunk_width; cx++) {
            WorldChunk* next_x = nullptr;
            WorldChunk* next_z = nullptr;

            if (cx != chunk_width-1) {
                next_x = &chunks[(cx + 1) + cy*chunk_width];
            }

            if (cy != chunk_width-1) {
                next_z = &chunks[cx + (cy+1)*chunk_width];
            }

            chunks[cx + cy*chunk_width].generateVertexGrid(next_x, next_z);
        }
    }

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool left_mouse = false;

    window.setView(camera);

    int prev_offset_x = 0;
    int prev_offset_y = 0;

    sf::Clock clock;

    while (window.isOpen()) {
        window.clear();

        window.setView(camera);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::W:
                        up = true;
                        break;
                    case sf::Keyboard::A:
                        left = true;
                        break;
                    case sf::Keyboard::S:
                        down = true;
                        break;
                    case sf::Keyboard::D:
                        right = true;
                        break;
                    case sf::Keyboard::Q:
                        if (scale < 4) {
                            camera.zoom(2);
                            scale++;
                        }
                        break;
                    case sf::Keyboard::E:
                        if (scale > 1) {
                            camera.zoom(0.5);
                            scale--;
                        }
                        break;
                    case sf::Keyboard::Z:
                        side++;
                        side = side % 4;
                        break;
                    case sf::Keyboard::C:
                        side--;
                        if (side == -1)
                            side = 3;
                        side = side % 4;
                        break;
                    default:
                        break;
                }
            }else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::W:
                        up = false;
                        break;
                    case sf::Keyboard::A:
                        left = false;
                        break;
                    case sf::Keyboard::S:
                        down = false;
                        break;
                    case sf::Keyboard::D:
                        right = false;
                        break;
                    default:
                        break;
                }
            }else if (event.type == sf::Event::MouseButtonPressed) {
                int chunk_x = 0;
                int chunk_y = 0;
                int chunk_z = 0;
                int tile_x = 0;
                int tile_y = 0;
                int tile_z = 0;
                int tile_side = 0;
                Rendering::getClickedTile(event.mouseButton.x, event.mouseButton.y, chunk_x, chunk_z, tile_x, tile_y, tile_z, tile_side);

                int chunk_index = chunk_x + chunk_z*chunk_width;
                int tile_index = tile_x + tile_z*16 + tile_y*16*16;

                //printf("Chunk (%d, %d) in Tile (%d, %d, %d)\n", chunk_x, chunk_z, tile_x, tile_y, tile_z);

                if (event.mouseButton.button == sf::Mouse::Left) {
                    chunks[chunk_index].tiles[tile_index].type = -1;
                }else{
                    WorldTile new_tile;
                    new_tile.pos_x = tile_x;
                    new_tile.pos_y = tile_y;
                    new_tile.pos_z = tile_z;
                    new_tile.visible = true;
                    new_tile.type = 2;
                    new_tile.sprite_index = stone_sprite;
                    switch (tile_side) {
                        case 3: {
                            int target_y = tile_y + 1;
                            if (target_y > 255) {
                                break;
                            }else{
                                new_tile.pos_y = target_y;
                                new_tile.top = true;
                                chunks[chunk_index].tiles[tile_x + tile_z*16 + target_y*256] = new_tile;
                                chunks[chunk_index].top++;
                            }
                            break; }
                        case 1: {
                            if (side == north || side == west) {
                                int target_z = tile_z + 1;
                                if (target_z > 15) {
                                    int target_chunk_z = chunk_z + 1;
                                    if (target_chunk_z < 0) {
                                        break;
                                    }else{
                                        new_tile.pos_z = 0;
                                        chunks[chunk_x + target_chunk_z*chunk_width].tiles[tile_x + tile_y*256] = new_tile;
                                    }
                                }else{
                                    new_tile.pos_z = target_z;
                                    chunks[chunk_index].tiles[tile_x + target_z*16 + tile_y*256] = new_tile;
                                }
                            }else{
                                int target_z = tile_z - 1;
                                if (target_z < 0) {
                                    int target_chunk_z = chunk_z - 1;
                                    if (target_chunk_z < 0) {
                                        break;
                                    }else{
                                        new_tile.pos_z = 15;
                                        chunks[chunk_x + target_chunk_z*chunk_width].tiles[tile_x + target_z*16 + tile_y*256] = new_tile;
                                    }
                                }else{
                                    new_tile.pos_z = target_z;
                                    chunks[chunk_index].tiles[tile_x + target_z*16 + tile_y*256] = new_tile;
                                }
                            }
                            break; }
                        case 2: {
                            if (side == north || side == east) {
                                int target_x = tile_x + 1;
                                if (target_x > 15) {
                                    int target_chunk_x = chunk_x + 1;
                                    if (target_chunk_x >= chunk_width) {
                                        break;
                                    }else{
                                        new_tile.pos_x = 0;
                                        chunks[target_chunk_x + chunk_z*chunk_width].tiles[tile_z*16 + tile_y*256] = new_tile;
                                    }
                                }else{
                                    new_tile.pos_x = target_x;
                                    chunks[chunk_index].tiles[target_x + tile_z*16 + tile_y*256] = new_tile;
                                }
                            }else{
                                int target_x = tile_x - 1;
                                if (target_x < 0) {
                                    int target_chunk_x = chunk_x - 1;
                                    if (target_chunk_x < 0) {
                                        break;
                                    }else{
                                        new_tile.pos_x = 15;
                                        chunks[target_chunk_x + chunk_z*chunk_width].tiles[target_x + tile_z*16 + tile_y*256] = new_tile;
                                    }
                                }else{
                                    new_tile.pos_x = target_x;
                                    chunks[chunk_index].tiles[target_x + tile_z*16 + tile_y*256] = new_tile;
                                }
                            }
                            break; }
                        default:
                            break;
                    }
                }


                WorldChunk* next_x = nullptr;
                WorldChunk* next_z = nullptr;

                if (chunk_x != chunk_width-1) {
                    next_x = &chunks[(chunk_x + 1) + chunk_z*chunk_width];
                }

                if (chunk_z != chunk_width-1) {
                    next_z = &chunks[chunk_x + (chunk_z + 1)*chunk_width];
                }

                chunks[chunk_index].generateVertexGrid(nullptr, nullptr);
            }else if (event.type == sf::Event::MouseButtonReleased) {
                left_mouse = false;
            }
        }

        if (up)
            camera.move(0, -10 * scale);

        if (down)
            camera.move(0, 10 * scale);

        if (left)
            camera.move(-10 * scale, 0);

        if (right)
            camera.move(10 * scale, 0);

        Rendering::renderVertexChunks(window, chunks, camera, side, chunk_width);

        //Rendering::debugRender(window);

        window.display();

        //sf::Time currentTime = clock.getElapsedTime();
        //std::cout << 1.0f / currentTime.asSeconds() << '\n';
        //clock.restart().asSeconds();

    }

    Rendering::deinit();

    return 0;
}
