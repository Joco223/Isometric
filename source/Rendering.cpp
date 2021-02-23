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
    const int width = 1024;
    const int height = 576;

    sf::Sprite tileMapChunkSprite;
    sf::Texture textureAtlas;

    void init(int chunk_count) {
        tileMap.create(width, height);
        tileMapChunk.create(width, height);
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

    void renderVertexChunks(sf::RenderWindow& window, const std::vector<WorldChunk>& chunks, const sf::View& camera, int side, int chunk_width, int prev_offset_x, int prev_offset_y) {
        tileMap.clear();
        tileMapChunk.clear();
        for (int x = 0; x < chunk_width; x++) {
            for (int z = 0; z < chunk_width; z++) {
                int corrected_x = x;
                int corrected_z = z;

                switch (side) {
                    case east:
                        corrected_z = (chunk_width - 1) - z;
                        break;
                    case south:
                        corrected_z = (chunk_width - 1) - z;
                        corrected_x = (chunk_width - 1) - x;
                        break;
                    case west:
                        corrected_x = (chunk_width - 1) - x;
                        break;
                }

                int offset_x = (x - z) * 16 * tile_size / 2.0f;
                int offset_z = (x + z) * 16 * tile_size / 4.0f;

                sf::Transform offset;
                offset.translate(offset_x - camera.getCenter().x, offset_z - camera.getCenter().y);
                sf::RenderStates states;
                states.transform = offset;
                states.texture = &textureAtlas;

                const WorldChunk& chunk = chunks[corrected_x + corrected_z*chunk_width];
                window.draw(chunk.vertices[side][0].data(), chunk.vertices[side][0].size(), sf::Quads, states);
                states.texture = nullptr;
                tileMap.setView(camera);
                tileMap.draw(chunk.vertices[side][1].data(), chunk.vertices[side][1].size(), sf::Quads, states);
                tileMapChunk.setView(camera);
                tileMapChunk.draw(chunk.vertices[side][2].data(), chunk.vertices[side][2].size(), sf::Quads, states);
            }
        }
        tileMap.display();
        tileMapChunk.display();
    }

    void getClickedTile(const int mouse_x, const int mouse_y, int& chunk_index_x, int& chunk_index_z, int& tile_index_x, int& tile_index_y, int& tile_index_z, int& tile_side) {
        auto tileMapImage = tileMap.getTexture().copyToImage();
        auto tileMapImageChunk = tileMapChunk.getTexture().copyToImage();

        auto tile = tileMapImage.getPixel(mouse_x, mouse_y);
        auto chunk = tileMapImageChunk.getPixel(mouse_x, mouse_y);

        chunk_index_x = chunk.r;
        chunk_index_z = chunk.g;
        tile_side = chunk.b;

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