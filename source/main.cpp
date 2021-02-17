#include <iostream>

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <stdio.h>

#include "Rendering.h"
#include "world_chunk.h"
#include "SimplexNoise.h"

const int width = 1280;
const int height = 720;
const int fps = 60;
const int chunk_size = 16;

int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height, 32), "Isometric", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(fps);

    sf::View camera(sf::FloatRect(0, 0, 1280, 720));
    int scale = 1;

    sf::Event event;

    int stone_sprite = Rendering::loadSprite("../assets/sprites/stone.png", "stone");
    int dirt_sprite = Rendering::loadSprite("../assets/sprites/dirt.png", "dirt");
    int grass_sprite = Rendering::loadSprite("../assets/sprites/grass.png", "stone");
    int selected_sprite = Rendering::loadSprite("../assets/sprites/selected.png", "selected");

    std::vector<WorldChunk> chunks;
    Rendering::init(24*24);


    for (int cy = 0; cy < 1; cy++) {
        for (int cx = 0; cx < 1; cx++) {
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

                        if (cx == 0 && x == 15) {
                            newTile.visible = true;
                        }

                        if (cy == 0 && z == 15) {
                            newTile.visible = true;
                        }


                        if (16 + top > new_chunk.top)
                            new_chunk.top = top + 16;


                        new_chunk.tiles[x + z*16 + y*16*16] = newTile;
                    }
                }
            }
            //Rendering::renderChunk(new_chunk, 24);
            new_chunk.generateVertexGrid();
            chunks.push_back(new_chunk);
        }
    }

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool left_mouse = false;

    window.setView(camera);

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
                Rendering::getClickedTile(event.mouseButton.x, event.mouseButton.y, chunk_x, chunk_z, tile_x, tile_y, tile_z);

                int chunk_index = chunk_x + chunk_z;
                int tile_index = tile_x + tile_z*16 + tile_y*16*16;

                //printf("Chunk (%d, %d) in Tile (%d, %d, %d)\n", chunk_x, chunk_z, tile_x, tile_y, tile_z);

                chunks[chunk_index].tiles[tile_index].type = -1;
                chunks[chunk_index].regenerateVisible();
                chunks[chunk_index].generateVertexGrid();
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



        //Rendering::renderWorldChunks(window, chunks);
        //Rendering::renderWorldTilesSmart(window, chunks, camera);
        Rendering::renderVertexChunks(window, chunks, camera);

        //Rendering::debugRender(window);

        window.display();

        //sf::Time currentTime = clock.getElapsedTime();
        //std::cout << 1.0f / currentTime.asSeconds() << '\n';
        //clock.restart().asSeconds();

    }

    Rendering::deinit();

    return 0;
}
