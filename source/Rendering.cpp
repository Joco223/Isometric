#include "Rendering.h"

namespace Rendering {

    sf::Sprite tile_sprite;
    sf::Texture tile_mask_txt;
    sf::Sprite tile_mask;

    sf::RenderTexture tileMapChunk;
    sf::RenderTexture tileMap;
    std::vector<sf::RenderTexture*> chunk_textures;
    std::vector<gameSprite> sprites;
    const int tile_size = 64;

    sf::Sprite tileMapChunkSprite;

    sf::Texture textureAtlas;

    void init(int chunk_count) {
        /*chunk_textures.resize(chunk_count);
        for (int i = 0; i < chunk_count; i++) {
            chunk_textures[i] = new sf::RenderTexture;
            chunk_textures[i]->create(17*tile_size, 24*tile_size);
        };*/
        tileMap.create(1280, 720);
        tileMapChunk.create(1280, 720);
        tile_mask_txt.loadFromFile("../assets/sprites/tile_mask.png");
        tile_mask.setTexture(tile_mask_txt);
        textureAtlas.loadFromFile("../assets/sprites/texture_atlas.png");
    }

    int loadSprite(const std::string& file_path, const std::string& name) {
        gameSprite newSprite;
        newSprite.path = file_path;
        newSprite.name = name;
        newSprite.sprite.loadFromFile(file_path);
        sprites.push_back(newSprite);
        return sprites.size() -1;
    }

    void renderWorldTiles(sf::RenderWindow& window, const std::vector<WorldChunk>& chunks) {
        for (auto& chunk : chunks) {
            int offset_x = (chunk.pos_x - chunk.pos_z) * 16 * tile_size / 2;
            int offset_y = (chunk.pos_x + chunk.pos_z) * 16 * tile_size / 4;
            for (auto& tile : chunk.tiles) {
                int new_pos_x = (tile.pos_x - tile.pos_z) * tile_size / 2 + offset_x;
                int new_pos_y = (tile.pos_x + tile.pos_z) * tile_size / 4 - tile.pos_y * tile_size / 2 + offset_y;
                tile_sprite.setTexture(sprites[tile.sprite_index].sprite);
                tile_sprite.setPosition(new_pos_x, new_pos_y);
                window.draw(tile_sprite);
            }
        }
    }

    void renderChunk(WorldChunk& chunk, int world_width) {
        int index = chunk.pos_x + chunk.pos_z * world_width;
        for (auto& tile : chunk.tiles) {
            int new_pos_x = (tile.pos_x - tile.pos_z) * tile_size / 2 + (16 * tile_size / 2);
            int new_pos_y = (tile.pos_x + tile.pos_z) * tile_size / 4 - tile.pos_y * tile_size / 2 + (16 * tile_size / 2);
            tile_sprite.setTexture(sprites[tile.sprite_index].sprite);
            tile_sprite.setPosition(new_pos_x, new_pos_y);
            chunk_textures[index]->draw(tile_sprite);
        }
        chunk.chunk_sprite.setTexture(chunk_textures[index]->getTexture());
        chunk.chunk_sprite.scale(1.0f, -1.0f);
    }

    void renderWorldChunks(sf::RenderWindow& window, std::vector<WorldChunk>& chunks) {
        for (auto& chunk : chunks) {
            int offset_x = (chunk.pos_x - chunk.pos_z) * 16 * tile_size / 2;
            int offset_y = (chunk.pos_x + chunk.pos_z) * 16 * tile_size / 4;
            chunk.chunk_sprite.setPosition(offset_x, offset_y);
            window.draw(chunk.chunk_sprite);
        }
    }

    void renderWorldTilesSmart(sf::RenderWindow& window, const std::vector<WorldChunk>& chunks, const sf::View& camera) {
        tileMapChunk.clear();
        tileMap.clear();

        for (auto& chunk : chunks) {
            int offset_x = (chunk.pos_x - chunk.pos_z) * 16 * tile_size / 2;
            int offset_y = (chunk.pos_x + chunk.pos_z) * 16 * tile_size / 4;
            sf::Vector2i new_chunk_pos = window.mapCoordsToPixel(sf::Vector2f(offset_x, offset_y), camera);
            if (new_chunk_pos.x > 0 - 17*tile_size && new_chunk_pos.x < 1280 + 17*tile_size) {
                if (new_chunk_pos.y > 0 - 24*tile_size && new_chunk_pos.y < 720 + 24*tile_size) {
                    for (auto& tile : chunk.tiles) {
                        if (tile.visible) {
                            int new_pos_x = (tile.pos_x - tile.pos_z) * tile_size / 2 + (16 * tile_size / 2) + offset_x;
                            int new_pos_y = (tile.pos_x + tile.pos_z) * tile_size / 4 - tile.pos_y * tile_size / 2 + (16 * tile_size / 2) + offset_y;
                            sf::Vector2i new_pos = window.mapCoordsToPixel(sf::Vector2f(new_pos_x, new_pos_y), camera);
                            if (new_pos.x > 0 - tile_size && new_pos.x < 1280 + tile_size) {
                                if (new_pos.y > 0 - tile_size && new_pos.y < 720 + tile_size) {
                                    tile_sprite.setTexture(sprites[tile.sprite_index].sprite);
                                    tile_sprite.setPosition(new_pos_x, new_pos_y);
                                    window.draw(tile_sprite);
                                    if (tile.selected) {
                                        tile_sprite.setTexture(sprites[3].sprite);
                                        window.draw(tile_sprite);
                                    }
                                    tile_mask.setPosition(new_pos_x, new_pos_y);
                                    tile_mask.setColor(sf::Color(tile.pos_x, tile.pos_y, tile.pos_z));
                                    tileMap.setView(camera);
                                    tileMap.draw(tile_mask);

                                    tile_mask.setColor(sf::Color(chunk.pos_x, 0, chunk.pos_z));
                                    tileMapChunk.setView(camera);
                                    tileMapChunk.draw(tile_mask);
                                }
                            }
                        }
                    }
                }
            }
        }
        tileMap.display();
        tileMapChunk.display();
    }

    void renderVertexChunks(sf::RenderWindow& window, const std::vector<WorldChunk>& chunks, const sf::View& camera) {
        for (auto& chunk : chunks) {
            window.draw(chunk.vertex_grid.data(), chunk.vertex_grid.size(), sf::Quads, &textureAtlas);
            tileMap.setView(camera);
            tileMap.draw(chunk.vertex_tile_grid.data(), chunk.vertex_tile_grid.size(), sf::Quads);
            tileMapChunk.setView(camera);
            tileMapChunk.draw(chunk.vertex_chunk_grid.data(), chunk.vertex_chunk_grid.size(), sf::Quads);
        }
        tileMap.display();
        tileMapChunk.display();
    }

    void getClickedTile(const int mouse_x, const int mouse_y, int& chunk_index_x, int& chunk_index_z, int& tile_index_x, int& tile_index_y, int& tile_index_z) {
        auto tileMapImage = tileMap.getTexture().copyToImage();
        auto tileMapImageChunk = tileMapChunk.getTexture().copyToImage();

        auto tile = tileMapImage.getPixel(mouse_x, mouse_y);
        auto chunk = tileMapImageChunk.getPixel(mouse_x, mouse_y);

        chunk_index_x = chunk.r;
        chunk_index_z = chunk.g;

        tile_index_x = tile.r;
        tile_index_y = tile.g;
        tile_index_z = tile.b;
    }

    void debugRender(sf::RenderWindow& window) {
        tileMapChunkSprite.setTexture(tileMap.getTexture());
        window.draw(tileMapChunkSprite);
    }

    void deinit() {
        for (int i = 0; i < chunk_textures.size(); i++) {
            delete chunk_textures[i];
        }
    }
}